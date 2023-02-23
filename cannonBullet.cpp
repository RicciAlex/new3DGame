//=============================================================================
//
// cannonBullet.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "cannonBullet.h"
#include "boss.h"
#include "explosion.h"
#include "application.h"
#include "sound.h"


//=============================================================================
//								静的変数の初期化
//=============================================================================
const float CCannonBullet::GRAVITY_ACCELERATION = -1.0f;		//重力加速度
const int CCannonBullet::DEFAULT_LIFE = 60;					//ディフォルトのライフ


//コンストラクタ
CCannonBullet::CCannonBullet()
{
	//メンバー変数をクリアする
	m_nLife = 0;
	m_move = Vec3Null;

	m_pBoss = nullptr;
}

//デストラクタ
CCannonBullet::~CCannonBullet()
{

}

//初期化処理
HRESULT CCannonBullet::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	SetModel(CModel::MODEL_CANNON_BULLET);	//モデルの設定
	m_nLife = DEFAULT_LIFE;					//ライフの設定
	SetDrawDistance(5000.0f);

	return S_OK;
}

//終了処理
void CCannonBullet::Uninit(void)
{
	if (m_pBoss)
	{
		m_pBoss = nullptr;
	}

	//基本クラスの終了処理
	CModel::Uninit();
}

//更新処理
void CCannonBullet::Update(void)
{
	m_nLife--;		//ライフの更新

	if (m_nLife <= 0)
	{//ライフが0になったら、消す

		if (m_pBoss)
		{//nullチェック

			m_pBoss->DealDamage();		//ダメージを与える
		}

		CExplosion::Create(GetPos());	//爆発を生成する

		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CANNONBALL);

		Release();		//メモリを解放する
		return;
	}

	D3DXVECTOR3 pos = GetPos() + m_move;		//位置の更新

	m_move.y += GRAVITY_ACCELERATION;			//重力をかける

	SetPos(pos);			//位置の設定

	//基本クラスの更新処理
	CModel::Update();
}



//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CCannonBullet* CCannonBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 target)
{
	CCannonBullet* pBullet = new CCannonBullet;		//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理

		return nullptr;
	}

	pBullet->SetPos(pos);		//位置の設定
	pBullet->SetShadowHeight(pos.y + 0.1f);		//影の位置の設定
	pBullet->SetSpeed(target);	//速度の設定処理

	return pBullet;				//生成したインスタンスを返す
}

CCannonBullet * CCannonBullet::Create(const D3DXVECTOR3 pos, CBoss * pBoss)
{
	CCannonBullet* pBullet = new CCannonBullet;		//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理

		return nullptr;
	}

	pBullet->SetPos(pos);		//位置の設定
	pBullet->SetShadowHeight(pos.y + 0.1f);		//影の位置の設定
	pBullet->m_pBoss = pBoss;	//ボスへのポインタの設定

	D3DXVECTOR3 target = pBoss->GetPos();

	pBullet->SetSpeed(target);	//速度の設定処理

	return pBullet;				//生成したインスタンスを返す
}



//=============================================================================
//	
//								プライベート関数
//
//=============================================================================



//速度の設定処理
void CCannonBullet::SetSpeed(const D3DXVECTOR3 target)
{
	D3DXVECTOR3 pos = GetPos(), move = target - pos;		//位置の取得

	//速度を計算する
	if (DEFAULT_LIFE != 0)
	{
		move.x /= DEFAULT_LIFE;
		move.z /= DEFAULT_LIFE;
	}

	move.y = -GRAVITY_ACCELERATION * ((float)DEFAULT_LIFE * 0.5f);

	m_move = move;				//速度の設定
}
