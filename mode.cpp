//=============================================================================
//
// mode.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"
#include "application.h"
#include "rendering.h"

//�R���X�g���N�^
CMode::CMode()
{
	m_bGame = false;

	CRenderer* pRenderer = CApplication::GetRenderer();

	if (pRenderer)
	{
		LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

		if (pDevice)
		{
			pDevice->SetRenderState(D3DRS_FOGCOLOR, ColorWhite);		//�t�H�O�̐F�𔒂ɖ߂�
		}
	}	
}

//�R���X�g���N�^
CMode::CMode(const bool bGame) : m_bGame(bGame)
{

}

//�f�X�g���N�^
CMode::~CMode()
{

}

//�Q�[���ł��邩�ǂ���
const bool CMode::IsGame(void)
{
	return m_bGame;
}