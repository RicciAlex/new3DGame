//=============================================================================
//
// spikeTrap.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "stalkingBot.h"
#include "player.h"
#include "application.h"
#include "game.h"


//=============================================================================
//								静的変数の初期化
//=============================================================================
const float		  CStalkingBot::DEFAULT_APPROACHING_SPEED = 10.0f;				//ディフォルトの追いかける速度
const float		  CStalkingBot::DEFAULT_ANGLE_SPEED = D3DX_PI * 0.01f;			//ディフォルトの回転速度
const float		  CStalkingBot::DEFAULT_FIRST_COEFF = 5.0f;						//ディフォルトの最初のパラメータ(パラメトリック方程式用)
const float		  CStalkingBot::DEFAULT_SECOND_COEFF = 3.0f;					//ディフォルトの二番目のパラメータ(パラメトリック方程式用)
const float		  CStalkingBot::DEFAULT_AMPLITUDE = 30.0f;						//ディフォルトの拡大率
const float		  CStalkingBot::DEFAULT_ACTIVATION_DISTANCE = 1000.0f;			//ディフォルトのアクティブ状態になる距離
const float	      CStalkingBot::DEFAULT_CIRCLE_RANGE = 200.0f;					//ディフォルトの円形の半径
const float		  CStalkingBot::DEFAULT_MAX_STAR_ANGLE = D3DX_PI * 12.0f;		//ディフォルトの最大角度(この角度を超えたら、逃げる状態になる)
const float		  CStalkingBot::DEFAULT_RUN_DISTANCE = 3000.0f;					//ディフォルトの逃げる距離
const D3DXVECTOR3 CStalkingBot::DEFAULT_RELATIVE_POS = {0.0f, 50.0f, 0.0f};		//ディフォルトの相対位置


//コンストラクタ
CStalkingBot::CStalkingBot()
{
	//メンバー変数をクリアする
	m_center = Vec3Null;
	m_move = Vec3Null;
	m_fPresentAngle = 0.0f;
	m_fStarRange = 0.0f;

	m_state = (State)0;
}

//デストラクタ
CStalkingBot::~CStalkingBot()
{

}

//初期化処理
HRESULT CStalkingBot::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CFogbot::Init()))
	{
		return -1;
	}
	
	//メンバー変数を初期化する
	m_center = Vec3Null;
	m_move = Vec3Null;
	m_fPresentAngle = 0.0f;
	m_fStarRange = DEFAULT_CIRCLE_RANGE / DEFAULT_FIRST_COEFF;

	m_state = (State)0;

	return S_OK;
}

//終了処理
void CStalkingBot::Uninit(void)
{
	//基本クラスの終了処理
	CFogbot::Uninit();
}

//更新処理
void CStalkingBot::Update(void)
{
	//基本クラスの更新処理
	CFogbot::Update();

	//状態によっての更新処理
	StateUpdate();
}



//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CStalkingBot* CStalkingBot::Create(const D3DXVECTOR3 pos, const float fShadowHeight)
{
	CStalkingBot* pBot = new CStalkingBot;			//インスタンスを生成する

	//初期化処理
	if (FAILED(pBot->Init()))
	{
		return nullptr;
	}

	pBot->CreateDefaultBot();				//ディフォルトのボットの生成処理

	pBot->SetPos(pos);						//位置の設定
	pBot->SetShadowHeight(fShadowHeight);	//影のY座標の設定

	return pBot;							//生成したインスタンスを返す
}

CStalkingBot* CStalkingBot::Create(const D3DXVECTOR3 pos, const float fShadowHeight, const float fStartAngle)
{
	CStalkingBot* pBot = new CStalkingBot;			//インスタンスを生成する

													//初期化処理
	if (FAILED(pBot->Init()))
	{
		return nullptr;
	}

	pBot->CreateDefaultBot();				//ディフォルトのボットの生成処理

	pBot->SetPos(pos);						//位置の設定
	pBot->SetShadowHeight(fShadowHeight);	//影のY座標の設定


	return pBot;							//生成したインスタンスを返す
}



//=============================================================================
//
//								プライベート関数
//
//=============================================================================




//状態によっての更新処理
void CStalkingBot::StateUpdate(void)
{
	switch (m_state)
	{

	case CStalkingBot::STATE_WAIT:

	{
		Activate();				//アクティブ状態になったかどうかの判定の処理
	}

		break;

	case CStalkingBot::STATE_FOLLOW:

	{
		FollowPlayer();			//プレイヤーを追いかける
	}

		break;

	case CStalkingBot::STATE_CIRCLE:

	{
		CirclePlayer();			//プレイヤーを中心にして、公転する
	}

		break;

	case CStalkingBot::STATE_STAR:

	{
		StarCircling();			//星の形に動かす
	}

		break;

	case CStalkingBot::STATE_RUN:

	{
		RunAway();				//逃げる処理
	}

		break;
	
	default:
		break;
	}
}

//アクティブ状態になったかどうかの判定の処理
bool CStalkingBot::Activate(void)
{
	D3DXVECTOR3 playerPos = CApplication::GetGame()->GetPlayer()->GetPos();		//プレイヤーの位置の取得
	D3DXVECTOR3 distance = playerPos - GetPos();								//プレイヤーとの距離を計算する

	if (D3DXVec3Length(&distance) <= DEFAULT_ACTIVATION_DISTANCE)
	{
		D3DXVECTOR3 move = Vec3Null;			//速度

		m_state = STATE_FOLLOW;					//追いかける状態にする

		//速度の計算と設定
		D3DXVec3Normalize(&move, &distance);
		move.x *= DEFAULT_APPROACHING_SPEED;
		move.y *= DEFAULT_APPROACHING_SPEED;
		move.z *= DEFAULT_APPROACHING_SPEED;

		m_move = move;

		return true;
	}

	return false;
}

//プレイヤーを追いかける処理
void CStalkingBot::FollowPlayer(void)
{
	SetPos(GetPos() + m_move);					//位置の更新と設定

	D3DXVECTOR3 playerPos = CApplication::GetGame()->GetPlayer()->GetPos();		//プレイヤーの位置の取得
	D3DXVECTOR3 distance = GetPos() - playerPos;								//プレイヤーとの距離を計算する

	if (D3DXVec3Length(&distance) <= DEFAULT_CIRCLE_RANGE)
	{
		D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);		//単位ベクトル
		D3DXVECTOR3 N = Vec3Null;								//正規化した距離
		float fAngle = 0.0f;									//はじめの時の角度

		m_move = Vec3Null;								//速度を0にする
		m_state = STATE_CIRCLE;							//状態を更新する
		m_center = playerPos + DEFAULT_RELATIVE_POS;	//中心点を設定する

		distance.y = 0.0f;
		D3DXVec3Normalize(&N, &distance);				//正規化した距離
		float fDot = D3DXVec3Dot(&unit, &N);
		fAngle = acosf(fDot);			//単位ベクトルと敵からプレイヤーまでのベクトルの間の角度を計算する

		if (playerPos.z > GetPos().z)
		{//必要だったら、正規化する

			fAngle *= -1.0f;
		}

		m_fPresentAngle = fAngle;

		ForceActivation();		//パーティクルをアクティブ状態にする
	}
	else
	{
		D3DXVECTOR3 move = Vec3Null;			//速度

		m_state = STATE_FOLLOW;					//追いかける状態にする

		//速度の計算と設定
		D3DXVec3Normalize(&move, &distance);
		move.x *= -DEFAULT_APPROACHING_SPEED;
		move.y = 0.0f;
		move.z *= -DEFAULT_APPROACHING_SPEED;

		m_move = move;
	}
}

//プレイヤーを中心にして、公転する
void CStalkingBot::CirclePlayer(void)
{
	D3DXVECTOR3 pos = GetPos();					//位置の取得
	D3DXVECTOR3 playerPos = CApplication::GetGame()->GetPlayer()->GetPos();		//プレイヤーの位置の取得

	m_center = playerPos + DEFAULT_RELATIVE_POS;	//中心点の更新

	m_fPresentAngle += DEFAULT_ANGLE_SPEED;			//現在の角度の更新

	//位置の更新と設定
	pos.x = m_center.x + (DEFAULT_CIRCLE_RANGE) * cosf(m_fPresentAngle);
	pos.z = m_center.z + (DEFAULT_CIRCLE_RANGE) * sinf(m_fPresentAngle);

	if (D3DX_PI * 2.0f - m_fPresentAngle < DEFAULT_ANGLE_SPEED)
	{//決まったところについたら

		m_fPresentAngle = 0.0f;	//現在の角度を0に戻す
		m_state = STATE_STAR;	//状態を更新する
	}

	SetPos(pos);
	
}

//星の形に動かす
void CStalkingBot::StarCircling(void)
{
	D3DXVECTOR3 pos = GetPos();					//位置の取得
	D3DXVECTOR3 playerPos = CApplication::GetGame()->GetPlayer()->GetPos();		//プレイヤーの位置の取得

	m_center = playerPos + DEFAULT_RELATIVE_POS;	//中心点の更新

	m_fPresentAngle += 2.0f * DEFAULT_ANGLE_SPEED;			//現在の角度の更新

	float a = DEFAULT_FIRST_COEFF;		//パラメトリック方程式用の係数の設定(ディフォルト値)
	float b = DEFAULT_SECOND_COEFF;		//パラメトリック方程式用の係数の設定(ディフォルト値)

	float x = ((a - b) * cosf(m_fPresentAngle)) + (b * cosf(((a - b) / b) * m_fPresentAngle));
	float y = ((a - b) * sinf(m_fPresentAngle)) - (b * sinf(((a - b) / b) * m_fPresentAngle));

	//位置の更新と設定
	pos.x = m_center.x + (m_fStarRange) * x;
	pos.z = m_center.z + (m_fStarRange) * y;

	SetPos(pos);

	if (m_fPresentAngle >= DEFAULT_MAX_STAR_ANGLE)
	{//最大角度を超えたら

		m_fPresentAngle = 0;			//現在の角度を0に戻す
		m_state = STATE_RUN;			//状態の更新
		
		//速度の計算と設定
		D3DXVECTOR3 move = pos - playerPos;
		D3DXVec3Normalize(&move, &move);
		move.x *= DEFAULT_APPROACHING_SPEED;
		move.z *= DEFAULT_APPROACHING_SPEED;

		m_move = move;

		Deactivate();					//パーティクルをアクティブではない状態にする
	}
}

//逃げる処理
void CStalkingBot::RunAway(void)
{
	D3DXVECTOR3 pos = GetPos();					//位置の取得
	D3DXVECTOR3 playerPos = CApplication::GetGame()->GetPlayer()->GetPos();		//プレイヤーの位置の取得

	pos += m_move;				//位置の更新

	D3DXVECTOR3 distance = playerPos - pos;			//プレイヤーとの距離の計算

	if (D3DXVec3Length(&distance) >= DEFAULT_RUN_DISTANCE)
	{
		Release();				//インスタンスを破棄する
		return;
	}

	SetPos(pos);
}
