//=============================================================================
//
// button.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "button.h"
#include "CylinderHitbox.h"

//コンストラクタ
CButton::CButton()
{
	m_bTriggered = false;
	m_pHitbox = nullptr;
}

//デストラクタ
CButton::~CButton()
{

}


//初期化処理
HRESULT CButton::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	m_bTriggered = false;
	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CButton::Uninit(void)
{
	if (m_pHitbox)
	{
		m_pHitbox->Release();
		m_pHitbox = false;
	}
}

//更新処理
void CButton::Update(void)
{

}

//押されたかどうかの取得処理
bool CButton::GetTrigger(void)
{
	return false;
}




//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CButton* CButton::Create(const D3DXVECTOR3 pos)
{
	return nullptr;
}

//生成処理
CButton* CButton::Create(const D3DXVECTOR3 pos, const D3DXCOLOR normalCol, const D3DXCOLOR pressedCol)
{
	return nullptr;
}