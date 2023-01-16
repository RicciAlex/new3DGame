//=============================================================================
//
// starUI.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "starUI.h"
#include "object2D.h"
#include "UIString.h"
#include <string>

#include "inputKeyboard.h"


//コンストラクタ
CStarUI::CStarUI()
{
	//メンバー変数をクリアする
	m_nStarNumber = 0;
	m_nTargetStar = 0;
	m_bDone = false;

	m_pStar = nullptr;
	m_pString = nullptr;
}

//デストラクタ
CStarUI::~CStarUI()
{

}

//初期化処理
HRESULT CStarUI::Init(void)
{
	//メンバー変数を初期化する
	m_nStarNumber = 0;
	m_nTargetStar = 0;
	m_bDone = false;

	m_pStar = nullptr;
	m_pString = nullptr;

	return S_OK;
}

//終了処理
void CStarUI::Uninit(void)
{
	//2Dオブジェクトの破棄処理
	if (m_pStar)
	{//nullチェック

		m_pStar->Release();			//メモリを解放する
		m_pStar = nullptr;			//ポインタをnullにする
	}

	//文字の破棄処理
	if (m_pString)
	{//nullチェック

		m_pString->Release();			//メモリを解放する
		m_pString = nullptr;			//ポインタをnullにする
	}
}

//更新処理
void CStarUI::Update(void)
{
	
}

//描画処理
void CStarUI::Draw(void)
{

}

//星数1つを加算する処理
void CStarUI::AddStar(void)
{
	if (!m_bDone)
	{
		m_nStarNumber++;

		if (m_pString)
		{
			if (m_nStarNumber < 10)
			{
				std::string str = "0" + std::to_string(m_nStarNumber) + "/" + std::to_string(m_nTargetStar);
				m_pString->ChangeString(str.c_str());
			}
			else
			{
				std::string str = std::to_string(m_nStarNumber) + "/" + std::to_string(m_nTargetStar);
				m_pString->ChangeString(str.c_str());
			}
		}

		if (m_nStarNumber == m_nTargetStar)
		{
			m_pString->ChangeString("DONE!");
			m_bDone = true;
		}
	}
}


//位置の設定処理
void CStarUI::SetPos(const D3DXVECTOR3 pos)
{

}

//目的の星数の設定処理
void CStarUI::SetTargetStar(const int target)
{
	m_nTargetStar = target;
}

//位置の取得処理
const D3DXVECTOR3 CStarUI::GetPos(void)
{
	return Vec3Null;
}



//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CStarUI* CStarUI::Create(const int nMaxStar)
{
	CStarUI* pUI = new CStarUI;			//インスタンスを生成する

	if (FAILED(pUI->Init()))
	{//初期化処理
		return nullptr;
	}

	pUI->m_nTargetStar = nMaxStar;		//目的の星数の設定

	//2Dオブジェクトの生成
	pUI->m_pStar = CObject_2D::Create();

	if (pUI->m_pStar)
	{//生成出来たら、必要なパラメータを設定する

		pUI->m_pStar->SetPos(D3DXVECTOR3(150.0f, 40.0f, 0.0f));
		pUI->m_pStar->SetSize(D3DXVECTOR2(30.0f, 30.0f));
		pUI->m_pStar->SetTexture(CObject::TEXTURE_STAR_UI);
		pUI->m_pStar->SetPriority(4);
	}

	std::string str = "00/" + std::to_string(nMaxStar);

	pUI->m_pString = CUIString::Create(D3DXVECTOR3(210.0f, 40.0f, 0.0f), D3DXVECTOR2(180.0f, 25.0f), D3DXCOLOR(1.0f, 0.9f, 0.0f, 1.0f), str.c_str());

	return pUI;
}