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
	//メンバー変数をクリアする
	m_originalPos = Vec3Null;
	m_normalCol = ColorNull;
	m_triggeredCol = ColorNull;
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

	m_originalPos = Vec3Null;
	m_normalCol = ColorRed;
	m_triggeredCol = ColorGreen;
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
	if (m_pHitbox)
	{
		if (m_pHitbox->GetCollisionState())
		{
			m_pHitbox->SetCollisionState(false);

			m_bTriggered = true;
			SetModelColor(0, m_triggeredCol);
			SetPos(m_originalPos + D3DXVECTOR3(0.0f, -9.0f, 0.0f));
		}
		else
		{
			m_bTriggered = false;
			SetModelColor(0, m_normalCol);
			SetPos(m_originalPos);
		}
	}
}

//押されたかどうかの取得処理
bool CButton::GetTrigger(void)
{
	return m_bTriggered;
}




//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CButton* CButton::Create(const D3DXVECTOR3 pos)
{
	CButton* pButton = new CButton;					//インスタンスを生成する

	if (FAILED(pButton->Init()))
	{//初期化処理
		return nullptr;
	}

	pButton->SetPos(pos);							//位置の設定
	pButton->m_originalPos = pos;					//元の位置の設定
	pButton->SetModel(CModel::MODEL_BUTTON);		//モデルの設定
	pButton->m_normalCol = ColorRed;				//普通の色の設定
	pButton->m_triggeredCol = ColorGreen;			//押された後の色の設定
	pButton->SetShadowDraw(false);					//影を描画しないようにする

	//ヒットボックスの生成
	pButton->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(50.0f, 10.0f, 50.0f), CHitbox::TYPE_BUTTON, pButton);
	pButton->m_pHitbox->IgnoreAllCollision();
	pButton->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);

	return pButton;									//生成したインスタンスを返す
}	

//生成処理
CButton* CButton::Create(const D3DXVECTOR3 pos, const D3DXCOLOR normalCol, const D3DXCOLOR pressedCol)
{
	CButton* pButton = new CButton;					//インスタンスを生成する

	if (FAILED(pButton->Init()))
	{//初期化処理
		return nullptr;
	}

	pButton->SetPos(pos);							//位置の設定
	pButton->m_originalPos = pos;					//元の位置の設定
	pButton->SetModel(CModel::MODEL_BUTTON);		//モデルの設定
	pButton->SetModelColor(0, normalCol);			//色の設定
	pButton->m_normalCol = normalCol;				//普通の色の設定
	pButton->m_triggeredCol = pressedCol;			//押された後の色の設定
	pButton->SetShadowDraw(false);					//影を描画しないようにする

	//ヒットボックスの生成
	pButton->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(50.0f, 10.0f, 50.0f), CHitbox::TYPE_BUTTON, pButton);
	pButton->m_pHitbox->IgnoreAllCollision();
	pButton->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);

	return pButton;									//生成したインスタンスを返す
}