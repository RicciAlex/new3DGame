//=============================================================================
//
// menu.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "menu.h"
#include "object2D.h"


//コンストラクタ
CMenu::CMenu()
{
	//メンバー変数をクリアする
	m_pos = Vec3Null;

	m_pBg = nullptr;
}

//デストラクタ
CMenu::~CMenu()
{

}

//初期化処理
HRESULT CMenu::Init(void)
{
	//メンバー変数を初期化する

	m_pos = Vec3Null;

	m_pBg = nullptr;

	return S_OK;
}

//終了処理
void CMenu::Uninit(void)
{
	//背景の破棄処理
	if (m_pBg)
	{//nullチェック

		m_pBg->Release();		//メモリを解放する
		m_pBg = nullptr;		//ポインタをnullにする
	}
}

//更新処理
void CMenu::Update(void)
{
	if (m_pBg)
	{
		m_pBg->Update();
	}
}

//描画処理
void CMenu::Draw(void)
{
	
}

//位置の設定処理
void CMenu::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;

	if (m_pBg)
	{
		m_pBg->SetPos(pos);
	}
}

//位置の取得処理
const D3DXVECTOR3 CMenu::GetPos(void)
{
	return m_pos;
}

//背景生成処理
void CMenu::CreateBg(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, CObject::TextType texture)
{
	if (!m_pBg)
	{//nullチェック

		m_pBg = CObject_2D::Create();			//背景を生成する

		if (m_pBg)
		{//生成出来たら、必要なパラメータを設定する

			m_pBg->SetPos(pos);
			m_pBg->SetSize(size);
			m_pBg->SetTexture(texture);
			m_pBg->SetPriority(5);
		}
	}
}

//背景の取得処理
const CObject_2D * CMenu::GetBg(void)
{
	return m_pBg;
}
