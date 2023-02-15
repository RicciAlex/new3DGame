//=============================================================================
//
// ShurikenTrap.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "ShurikenTrap.h"
#include "shuriken.h"
#include "button.h"
#include "CylinderHitbox.h"
#include "application.h"
#include "sound.h"

//コンストラクタ
CShurikenTrap::CShurikenTrap()
{
	//メンバー変数をクリアする
	m_spawnPos = Vec3Null;
	m_rot = Vec3Null;
	m_nDelay = 0;

	m_pButton = nullptr;
	m_pHitbox = nullptr;
}

//デストラクタ
CShurikenTrap::~CShurikenTrap()
{

}

//初期化処理
HRESULT CShurikenTrap::Init(void)
{
	//メンバー変数を初期化する
	m_spawnPos = Vec3Null;
	m_rot = Vec3Null;
	m_nDelay = 60;

	m_pButton = nullptr;
	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CShurikenTrap::Uninit(void)
{
	//ボタンの破棄処理
	if (m_pButton)
	{//nullチェック
		m_pButton->Release();		//メモリを解放する
		m_pButton = nullptr;		//ポインタをnullにする
	}

	//ヒットボックスの破棄処理
	if (m_pHitbox)
	{//nullチェック
		m_pHitbox->Release();		//メモリを解放する
		m_pHitbox = nullptr;		//ポインタをnullにする
	}
}

//更新処理
void CShurikenTrap::Update(void)
{
	if (m_nDelay > 0)
	{
		m_nDelay--;
	}

	if (m_pButton)
	{
		if (m_pButton->GetTrigger())
		{
			if (m_nDelay <= 0)
			{
				D3DXVECTOR3 speed = m_pButton->GetPos() - m_spawnPos;
				speed.y = 0.0f;
				D3DXVec3Normalize(&speed, &speed);
				speed.x *= 10.0f;
				speed.z *= 10.0f;

				CShuriken::Create(m_spawnPos, speed);

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SLASH);

				m_nDelay = 15;
			}
		}
	}
}

//描画処理
void CShurikenTrap::Draw(void)
{

}

//位置の設定処理
void CShurikenTrap::SetPos(const D3DXVECTOR3 pos)
{
	
}

//位置の取得処理
const D3DXVECTOR3 CShurikenTrap::GetPos(void)
{
	return Vec3Null;
}



//=============================================================================
//
//								静的関数
//
//=============================================================================


//生成処理
CShurikenTrap* CShurikenTrap::Create(const D3DXVECTOR3 pos, const float Yrot, const float fDistance)
{
	CShurikenTrap* pTrap = new CShurikenTrap;

	if (FAILED(pTrap->Init()))
	{
		return nullptr;
	}

	pTrap->m_pButton = CButton::Create(pos);

	if (!pTrap->m_pButton)
	{
		return nullptr;
	}

	D3DXVECTOR3 sPos = Vec3Null, unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXMATRIX mtxOut, mtxRot;

	D3DXMatrixIdentity(&mtxOut);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Yrot, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxRot);

	D3DXVec3TransformCoord(&unit, &unit, &mtxOut);
	unit.x *= fDistance;
	unit.z *= fDistance;

	CModel* pModel = CModel::Create(CModel::MODEL_TRAP_PILLAR, pos + unit);
	pModel->SetRot(D3DXVECTOR3(0.0f, -Yrot, 0.0f));
	pModel->SetScale(1.5f);

	pTrap->m_pHitbox = CCylinderHitbox::Create(pos + unit, Vec3Null, D3DXVECTOR3(15.0f, 130.0f, 15.0f), CHitbox::TYPE_NEUTRAL, pTrap);

	unit.y += 100.0f;

	pTrap->m_spawnPos = pos + unit;

	return pTrap;
}

//生成処理
CShurikenTrap* CShurikenTrap::Create(const D3DXVECTOR3 pos, const float Yrot, const float fDistance,
								     const D3DXCOLOR buttonCol, const D3DXCOLOR triggeredCol)
{
	CShurikenTrap* pTrap = new CShurikenTrap;

	if (FAILED(pTrap->Init()))
	{
		return nullptr;
	}

	pTrap->m_pButton = CButton::Create(pos, buttonCol, triggeredCol);

	if (!pTrap->m_pButton)
	{
		return nullptr;
	}

	D3DXVECTOR3 sPos = Vec3Null, unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXMATRIX mtxOut, mtxRot;

	D3DXMatrixIdentity(&mtxOut);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Yrot, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxRot);

	D3DXVec3TransformCoord(&unit, &unit, &mtxOut);
	unit.x *= fDistance;
	unit.z *= fDistance;

	CModel* pModel = CModel::Create(CModel::MODEL_TRAP_PILLAR, pos + unit);
	pModel->SetRot(D3DXVECTOR3(0.0f, -Yrot + D3DX_PI * 0.5f, 0.0f));
	pModel->SetScale(1.5f);

	pTrap->m_pHitbox = CCylinderHitbox::Create(pos + unit, Vec3Null, D3DXVECTOR3(15.0f, 130.0f, 15.0f), CHitbox::TYPE_NEUTRAL, pTrap);

	unit.y += 100.0f;

	pTrap->m_spawnPos = pos + unit;

	return pTrap;
}