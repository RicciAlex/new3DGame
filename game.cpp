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
#include "timer.h"

//�R���X�g���N�^
CGame::CGame() : CMode(true)
{
	m_pPlayer = nullptr;
	m_pTimer = nullptr;
}

//�f�X�g���N�^
CGame::~CGame()
{

}

//����������
HRESULT CGame::Init(void)
{
	m_pPlayer = nullptr;
	m_pTimer = CTimer::Create();

	return S_OK;
}

//�I������
void CGame::Uninit(void)
{
	if (m_pPlayer)
	{
		m_pPlayer->Release();
		m_pPlayer = nullptr;
	}

	if (m_pTimer)
	{
		m_pTimer->Release();
		m_pTimer = nullptr;
	}
}

//�X�V����
void CGame::Update(void)
{
	
}

//���Ԃ̒ǉ�����
void CGame::AddTime(const float fMilliseconds)
{
	if (m_pTimer)
	{
		m_pTimer->AddTime(fMilliseconds);
	}
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