//=============================================================================
//
// shuriken.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "shuriken.h"
#include "BoxHitbox.h"

//コンストラクタ
CShuriken::CShuriken()
{
	//メンバー変数をクリアする
	m_move = Vec3Null;
	m_nLife = 0;

	m_pHitbox = nullptr;
}

//デストラクタ
CShuriken::~CShuriken()
{

}

//初期化処理
HRESULT CShuriken::Init(void)
{
	if (FAILED(CModel::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	//メンバー変数を初期化する
	m_move = Vec3Null;
	m_nLife = 120;

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CShuriken::Uninit(void)
{
	if (m_pHitbox)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}
}

//更新処理
void CShuriken::Update(void)
{
	CModel::Update();

	D3DXVECTOR3 pos = GetPos() + m_move;
	SetPos(pos);

	if (m_pHitbox)
	{
		m_pHitbox->SetPos(GetPos());

		if (m_pHitbox->GetCollisionState())
		{
			m_pHitbox->SetCollisionState(false);
		}
	}
	
	m_nLife--;

	if (m_nLife <= 0)
	{
		Release();
	}
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CShuriken* CShuriken::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 speed)
{
	CShuriken* pShuriken = new CShuriken;

	if (FAILED(pShuriken->Init()))
	{
		return nullptr;
	}

	pShuriken->SetPos(pos);
	pShuriken->m_move = speed;
	pShuriken->SetModel(CModel::MODEL_SHURIKEN);
	pShuriken->SetShadowDraw(false);
	pShuriken->StartRotation(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.1f));

	pShuriken->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(17.0f, 20.0f, 17.0f), CHitbox::TYPE_OBSTACLE, pShuriken, -1, CHitbox::EFFECT_DAMAGE);

	return pShuriken;
}

CShuriken* CShuriken::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 speed, const float fShadowHeight)
{
	CShuriken* pShuriken = new CShuriken;

	if (FAILED(pShuriken->Init()))
	{
		return nullptr;
	}

	pShuriken->SetPos(pos);
	pShuriken->m_move = speed;
	pShuriken->SetModel(CModel::MODEL_SHURIKEN);
	pShuriken->SetShadowHeight(fShadowHeight);
	pShuriken->StartRotation(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.1f));

	pShuriken->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(17.0f, 20.0f, 17.0f), CHitbox::TYPE_OBSTACLE, pShuriken, -1, CHitbox::EFFECT_DAMAGE);

	return pShuriken;
}