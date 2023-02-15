//=============================================================================
//
// goal.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "goal.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "magicCircleEffect.h"


//=============================================================================
//								�ÓI�ϐ��̏�����
//=============================================================================
const float CGoal::DEFAULT_RADIUS = 80.0f;				//�f�B�t�H���g�̔��a


//�R���X�g���N�^
CGoal::CGoal()
{
	//�����o�[�ϐ����N���A����
	m_nPresentGem = 0;
}

//�f�X�g���N�^
CGoal::~CGoal()
{

}

//����������
HRESULT CGoal::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	return S_OK;
}

//�I������
void CGoal::Uninit(void)
{
	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V����
void CGoal::Update(void)
{
	CGame* pGame = CApplication::GetGame();

	if (pGame)
	{
		if (m_nPresentGem <= 0)
		{
			D3DXVECTOR3 distance = pGame->GetPlayer()->GetPos() - GetPos();

			float fDistance = D3DXVec3Length(&distance);

			if (fDistance <= DEFAULT_RADIUS)
			{
				CApplication::SetFade(CApplication::MODE_RESULTS);
			}
		}
	}
}

//��΂̉��Z����
void CGoal::AddGem(void)
{
	m_nPresentGem++;
}

//��΂̌��Z����
void CGoal::SubtractGem(void)
{
	m_nPresentGem--;
}




//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================




//��������
CGoal* CGoal::Create(const D3DXVECTOR3 pos)
{
	CGoal* pGoal = new CGoal;		//�C���X�^���X�𐶐�����

	if (FAILED(pGoal->Init()))
	{//����������
		return nullptr;
	}

	pGoal->SetPos(pos);						//�ʒu�̐ݒ�
	pGoal->SetModel(CModel::MODEL_FLAG);	//���f���̐ݒ�
	pGoal->SetShadowHeight(pos.y);			//�e��Y���W�̐ݒ�

	CMagicCircleEffect::Create(D3DXVECTOR3(pos.x, pos.y + 0.1f, pos.z));		//�G�t�F�N�g�̐���

	return pGoal;					//���������C���X�^���X��Ԃ�
}