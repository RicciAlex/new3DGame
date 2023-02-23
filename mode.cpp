//=============================================================================
//
// mode.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"
#include "application.h"
#include "rendering.h"

//コンストラクタ
CMode::CMode()
{
	m_bGame = false;

	CRenderer* pRenderer = CApplication::GetRenderer();

	if (pRenderer)
	{
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		if (pDevice)
		{
			pDevice->SetRenderState(D3DRS_FOGCOLOR, ColorWhite);		//フォグの色を白に戻す
		}
	}	
}

//コンストラクタ
CMode::CMode(const bool bGame) : m_bGame(bGame)
{

}

//デストラクタ
CMode::~CMode()
{

}

//ゲームであるかどうか
const bool CMode::IsGame(void)
{
	return m_bGame;
}