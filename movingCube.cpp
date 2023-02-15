//=============================================================================
//
// movingCube.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "movingCube.h"
#include "BoxHitbox.h"
#include "application.h"
#include "rendering.h"
#include "phongShading.h"
#include "camera.h"
#include "directionalLight.h"
#include "game.h"
#include "player.h"

//=============================================================================
//							静的変数の初期化
//=============================================================================
const D3DXVECTOR3 CMovingCube::m_metalBoxSize = D3DXVECTOR3(100.0f, 20.0f, 100.0f);				//メタルボックスのサイズ


//コンストラクタ
CMovingCube::CMovingCube()
{
	//メンバー変数をクリアする
	m_OriginalPos = Vec3Null;
	m_size = Vec3Null;
	m_move = Vec3Null;
	m_fRange = 0.0f;

	m_pHitbox = nullptr;
}

//デストラクタ
CMovingCube::~CMovingCube()
{

}


//初期化処理
HRESULT CMovingCube::Init(void)
{
	if (FAILED(CModel::Init()))
	{//基本クラスの初期化処理

		return -1;
	}

	//メンバー変数を初期化する
	m_OriginalPos = Vec3Null;
	m_size = Vec3Null;
	m_move = Vec3Null;
	m_fRange = 0.0f;

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CMovingCube::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//ポインタをnullにする
	}

	//基本クラスの終了処理
	CModel::Uninit();
}

//更新処理
void CMovingCube::Update(void)
{
	SetPos(GetPos() + m_move);			//位置の更新

	//ヒットボックスの更新
	if (m_pHitbox)
	{//nullチェック

		m_pHitbox->SetPos(GetPos());	//ヒットボックスの位置の更新

		PushOut();
	}

	ClampPos();							//位置を制限する処理
}

//描画処理
void CMovingCube::Draw(void)
{
	CPhongShading* pPhong = CApplication::GetRenderer()->GetPhongEffect();			//シェーダーエフェクトの取得処理

	if (pPhong)
	{//nullチェック

		//視点を取得して、Vector4に変換する
		D3DXVECTOR3 posV = CApplication::GetCamera()->GetPos();		
		D3DXVECTOR4 cameraPos = {};									

		cameraPos.x = posV.x;
		cameraPos.y = posV.y;
		cameraPos.z = posV.z;
		cameraPos.w = 1.0f;

		//ライトの方向を取得して、Vector4に変換する
		D3DXVECTOR3 l = CDirectionalLight::GetPrincipalLightDir();
		D3DXVec3Normalize(&l, &l);
		D3DXVECTOR4 light = D3DXVECTOR4(posV.x - l.x, posV.y - l.y, posV.z - l.z, 0.0f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light, (D3DXVECTOR3*)&light);

		pPhong->Begin();											//エフェクトの開始処理
		pPhong->SetAmbient(0.20f);									//環境光の設定
		pPhong->SetSpecular(20.0f);									//スペキュラーの範囲の設定
		pPhong->SetSpecularPower(1.0f);							//スペキュラーの強度の設定
		pPhong->SetMatrix(GetWorldMatrix(), &cameraPos, &light);	//ワールドマトリックスの設定
		pPhong->BeginPass();										//パスの開始処理
	}

	CModel::Draw();				//基本クラスの描画処理

	if (pPhong)
	{//nullチェック
		pPhong->EndPass();		//パスの終了処理
		pPhong->End();			//シェーダーエフェクトの終了処理
	}
}

//位置の設定処理
void CMovingCube::SetPos(const D3DXVECTOR3 pos)
{
	CModel::SetPos(pos);
}

//元の位置の設定処理
void CMovingCube::SetOriginalPos(const D3DXVECTOR3 oPos)
{
	m_OriginalPos = oPos;
}

//速度の設定処理
void CMovingCube::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;				//速度の設定

	//ヒットボックスの速度の設定
	if (m_pHitbox)
	{//nullチェック
		m_pHitbox->SetMove(m_move);
	}
}

void CMovingCube::SetMove(const D3DXVECTOR3 move, const float fRange)
{
	m_move = move;				//速度の設定
	m_fRange = fRange;			//移動の限界の設定

	//ヒットボックスの速度の設定
	if (m_pHitbox)
	{//nullチェック
		m_pHitbox->SetMove(m_move);
	}
}




//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CMovingCube* CMovingCube::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fRange)
{
	CMovingCube* pCube = new CMovingCube;			//インスタンスを生成する

	if (FAILED(pCube->Init()))
	{//初期化処理

		return nullptr;
	}

	pCube->SetModel(CModel::MODEL_METAL_CUBE);			//モデルの設定
	pCube->SetPos(pos);				//位置の設定
	pCube->m_OriginalPos = pos;		//元の位置の設定
	pCube->m_size = m_metalBoxSize;	//サイズの設定
	pCube->m_move = move;			//速度の設定
	pCube->m_fRange = fRange;		//移動の限界の設定

	//ヒットボックスの生成
	pCube->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, -m_metalBoxSize.y * 0.5f, 0.0f), 
		D3DXVECTOR3(m_metalBoxSize.x * 0.5f, m_metalBoxSize.y, m_metalBoxSize.z * 0.5f), CHitbox::TYPE_NEUTRAL, pCube);

	if (pCube->m_pHitbox)
	{
		pCube->m_pHitbox->SetMove(move);
	}

	return pCube;					//生成したインスタンスを返す
}



//=============================================================================
//
//								プライベート関数
//
//=============================================================================



//移動を制限する処理
void CMovingCube::ClampPos(void)
{
	D3DXVECTOR3 pos = GetPos();				//位置の取得

	//全部の座標を確認して、限界を超えたら、戻して、速度を逆にする
	if (pos.x <= m_OriginalPos.x - m_fRange)
	{
		pos.x = m_OriginalPos.x - m_fRange;
		m_move.x *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.x *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}
	if (pos.y <= m_OriginalPos.y - m_fRange)
	{
		pos.y = m_OriginalPos.y - m_fRange;
		m_move.y *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.y *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}
	if (pos.z <= m_OriginalPos.z - m_fRange)
	{
		pos.z = m_OriginalPos.z - m_fRange;
		m_move.z *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.z *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}

	if (pos.x >= m_OriginalPos.x + m_fRange)
	{
		pos.x = m_OriginalPos.x + m_fRange;
		m_move.x *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.x *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}
	if (pos.y >= m_OriginalPos.y + m_fRange)
	{
		pos.y = m_OriginalPos.y + m_fRange;
		m_move.y *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.y *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}
	if (pos.z >= m_OriginalPos.z + m_fRange)
	{
		pos.z = m_OriginalPos.z + m_fRange;
		m_move.z *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.z *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}
}

//プレイヤーの押し出す処理
void CMovingCube::PushOut(void)
{
	CPlayer* pPlayer = CApplication::GetGame()->GetPlayer();			//プレイヤー情報の取得

	D3DXVECTOR3 playerPos = pPlayer->GetPos();							//プレイヤーの位置の取得
	D3DXVECTOR3 pos = GetPos();											//位置の取得
	D3DXVECTOR3 distance = playerPos - pos;

	if (D3DXVec3Length(&distance) <= 200.0f)
	{
		if (playerPos.x >= pos.x - m_size.x * 0.5f && playerPos.x <= pos.x + m_size.x * 0.5f &&
			playerPos.z >= pos.z - m_size.z * 0.5f && playerPos.z <= pos.z + m_size.z * 0.5f &&
			playerPos.y < pos.y + m_size.y * 0.5f && pPlayer->GetLastPos().y >= pos.y - m_move.y + m_size.y * 0.5f)
		{
			playerPos.y = pos.y + m_size.y * 0.5f;
			pPlayer->SetPos(playerPos);
			pPlayer->SetLanded();
			pPlayer->SetFriction(1.0f);
		}
	}
}
