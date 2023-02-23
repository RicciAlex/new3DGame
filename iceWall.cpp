//=============================================================================
//
// iceWall.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "iceWall.h"
#include "modelPart.h"
#include "BoxHitbox.h"
#include "application.h"
#include "sound.h"


//=============================================================================
//							静的変数の初期化
//=============================================================================

const D3DXVECTOR3 CIceWall::HITBOX_SIZE = { 100.0f, 325.0f, 50.0f };		//ディフォルトのサイズ

const D3DXVECTOR3 CIceWall::RELATIVE_PARTS_POS[CIceWall::PART_NUMBER] =
{
	{ -41.0f,  50.0f, 0.0f },
	{  39.0f,  40.0f, 0.0f },
	{  39.0f, 160.0f, 0.0f },
	{ -40.0f, 159.0f, 0.0f },
	{   0.0f, 267.0f, 0.0f }
};	//パーツの相対位置


//コンストラクタ
CIceWall::CIceWall()
{
	//メンバー変数をクリアする
	m_pos = Vec3Null;
	m_rot = Vec3Null;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nCntDeath = 0;
	m_bBroken = false;
	
	for (int nCnt = 0; nCnt < CIceWall::PART_NUMBER; nCnt++)
	{
		m_move[nCnt] = Vec3Null;
		m_partsRot[nCnt] = Vec3Null;
		m_pPart[nCnt] = nullptr;
	}

	m_pHitbox = nullptr;
}

//デストラクタ
CIceWall::~CIceWall()
{

}

//初期化処理
HRESULT CIceWall::Init(void)
{
	//メンバー変数を初期化する
	m_nCntDeath = 90;

	return S_OK;
}

//終了処理
void CIceWall::Uninit(void)
{
	for (int nCnt = 0; nCnt < CIceWall::PART_NUMBER; nCnt++)
	{
		if (m_pPart[nCnt])
		{
			m_pPart[nCnt]->Uninit();
			delete m_pPart[nCnt];
			m_pPart[nCnt] = nullptr;
		}
	}

	//ヒットボックスの破棄処理
	if (m_pHitbox)
	{//nullチェック

		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//ポインタをnullにする
	}
}

//更新処理
void CIceWall::Update(void)
{
	if (!m_bBroken)
	{
		if (m_pHitbox)
		{
			m_pHitbox->Update();

			if (m_pHitbox->GetEffect() == CHitbox::EFFECT_DAMAGE)
			{
				m_pHitbox->Release();
				m_pHitbox = nullptr;

				m_bBroken = true;

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ICE_BROKEN);
			}
		}
	}
	else
	{
		m_nCntDeath--;

		if (m_nCntDeath <= 0)
		{
			Release();
			return;
		}

		for (int nCnt = 0; nCnt < CIceWall::PART_NUMBER; nCnt++)
		{
			m_move[nCnt].y += -0.8f;

			if (m_pPart[nCnt])
			{
				m_pPart[nCnt]->SetPos(m_pPart[nCnt]->GetPos() + m_move[nCnt]);
				m_pPart[nCnt]->SetRot(m_pPart[nCnt]->GetRot() + m_partsRot[nCnt]);
			}
		}
	}
}

//描画処理
void CIceWall::Draw(void)
{
	D3DXMATRIX mtxTrans, mtxRot;		//計算用のマトリックス

	D3DXMatrixIdentity(&m_mtxWorld);	//マトリックスの初期化

	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	for (int nCnt = 0; nCnt < CIceWall::PART_NUMBER; nCnt++)
	{
		if (m_pPart[nCnt])
		{
			m_pPart[nCnt]->Draw(m_mtxWorld);
		}
	}
}

//位置の設定処理
void CIceWall::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//位置の取得処理
const D3DXVECTOR3 CIceWall::GetPos(void)
{
	return m_pos;
}



//=============================================================================
//
//									静的関数
//
//=============================================================================




//生成処理
CIceWall* CIceWall::Create(const D3DXVECTOR3 pos, const bool bRotate)
{
	CIceWall* pWall = new CIceWall;			//インスタンスを生成する

	if (FAILED(pWall->Init()))
	{//初期化処理
		return nullptr;
	}

	pWall->m_pos = pos;									//位置の設定
	pWall->m_rot = Vec3Null;

	D3DXVECTOR3 size = HITBOX_SIZE;						//サイズの設定

	if (bRotate)
	{
		pWall->m_rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);		//回転角度の設定
		size = D3DXVECTOR3(HITBOX_SIZE.z, HITBOX_SIZE.y, HITBOX_SIZE.x);	//サイズの調整
	}

	for (int nCnt = 0; nCnt < CIceWall::PART_NUMBER; nCnt++)
	{
		pWall->m_pPart[nCnt] = CModelPart::Create((CModel::ModelType)((int)CModel::MODEL_ICE_FRAGMENT_1 + nCnt), RELATIVE_PARTS_POS[nCnt], Vec3Null);
	
		if (pWall->m_pPart[nCnt])
		{
			pWall->m_pPart[nCnt]->SetShadowHeight(-5000.0f);
		}
	}

	pWall->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, size, CHitbox::TYPE_NEUTRAL, pWall);

	if (pWall->m_pHitbox)
	{
		pWall->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_OBSTACLE, CHitbox::RESPONSE_OVERLAP);
	}

	pWall->SetMove();

	return pWall;				//生成したインスタンスを返す
}



//=============================================================================
//
//								プライベート関数
//
//=============================================================================



//速度の設定処理
void CIceWall::SetMove(void)
{
	D3DXMATRIX mtxRot;

	D3DXMatrixIdentity(&mtxRot);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	m_move[0] = D3DXVECTOR3(random(-500, -100) * 0.01f, random(100, 500) * 0.01f, 0.0f);
	m_move[1] = D3DXVECTOR3(random( 100,  500) * 0.01f, random(100, 500) * 0.01f, 0.0f);
	m_move[2] = D3DXVECTOR3(random( 100,  500) * 0.01f, random(200, 600) * 0.01f, 0.0f);
	m_move[3] = D3DXVECTOR3(random(-500, -100) * 0.01f, random(200, 600) * 0.01f, 0.0f);
	m_move[4] = D3DXVECTOR3(random(-500,  500) * 0.01f, random(300, 650) * 0.01f, 0.0f);

	for (int nCnt = 0; nCnt < CIceWall::PART_NUMBER; nCnt++)
	{
		D3DXVec3TransformCoord(&m_move[nCnt], &m_move[nCnt], &mtxRot);

		m_partsRot[nCnt] = D3DXVECTOR3(0.0f, random(-100, 100) * D3DX_PI * 0.001f, random(-100, 100) * D3DX_PI * 0.001f);
		D3DXVec3TransformCoord(&m_partsRot[nCnt], &m_partsRot[nCnt], &mtxRot);
	}
}
