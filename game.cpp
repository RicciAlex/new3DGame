//=============================================================================
//
// game.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "game.h"
#include "player.h"

//�R���X�g���N�^
CGame::CGame() : CMode(true)
{
	m_pPlayer = nullptr;
}

//�f�X�g���N�^
CGame::~CGame()
{

}

//����������
HRESULT CGame::Init(void)
{
	m_pPlayer = nullptr;

	return S_OK;
}

//�I������
void CGame::Uninit(void)
{
	
}

//�X�V����
void CGame::Update(void)
{
	
}


//�v���C���[�̐ݒ菈��
void CGame::SetPlayer(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}

//�v���C���[�̎擾����
CPlayer* CGame::GetPlayer(void)
{
	return m_pPlayer;
}