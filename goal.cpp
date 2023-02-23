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
#include "score.h"
#include "game.h"
#include "player.h"
#include "magicCircleEffect.h"
#include "object2D.h"
#include <string>


//=============================================================================
//								�ÓI�ϐ��̏�����
//=============================================================================
const float CGoal::DEFAULT_RADIUS = 80.0f;				//�f�B�t�H���g�̔��a


//�R���X�g���N�^
CGoal::CGoal()
{
	//�����o�[�ϐ����N���A����
	m_nPresentGem = 0;
	m_bCreate = false;

	m_pGemNeeded = nullptr;
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
	//UI�̔j������
	if (m_pGemNeeded)
	{//null�`�F�b�N
		m_pGemNeeded->Release();		//���������������
		m_pGemNeeded = nullptr;			//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V����
void CGoal::Update(void)
{
	if (!m_bCreate && CApplication::GetModeInstance()->IsGame())
	{
		m_bCreate = true;

		CObject_2D* pObj = CObject_2D::Create(5, D3DXVECTOR3(600.0f, 40.0f, 0.0f), D3DXVECTOR2(25.0f, 25.0f), CObject::TEXTURE_GEM_ICON);

		if (pObj)
		{
			pObj->SetTextureParameter(1, 3, 2, INT_MAX);
		}

		if (!m_pGemNeeded)
		{
			m_pGemNeeded = CUIString::Create(D3DXVECTOR3(640.0f, 40.0f, 0.0f), D3DXVECTOR2(75.0f, 40.0f), ColorYellow, "0/3");
		}
	}

	CGame* pGame = CApplication::GetGame();

	if (pGame)
	{
		if (m_nPresentGem <= 0)
		{
			D3DXVECTOR3 distance = pGame->GetPlayer()->GetPos() - GetPos();

			float fDistance = D3DXVec3Length(&distance);

			if (fDistance <= DEFAULT_RADIUS)
			{
				if (CApplication::GetMode() != CApplication::MODE_TUTORIAL)
				{
					CScore* pScore = CApplication::GetScore();
					CMode* pMode = CApplication::GetModeInstance();

					if (pScore && pMode)
					{
						if (pMode->IsGame())
						{
							pScore->SetTime(CApplication::GetGame()->GetTime());
						}
					}

					if (CApplication::GetMode() == CApplication::MODE_FIRST_STAGE)
					{
						CApplication::SetFade(CApplication::MODE_RESULTS);
					}
					else if (CApplication::GetMode() == CApplication::MODE_SECOND_STAGE)
					{
						CApplication::SetFade(CApplication::MODE_BOSS_STAGE);
					}
				}
				else
				{
					CApplication::SetFade(CApplication::MODE_STAGE_SELECT);
				}
			}
		}
	}
}

//��΂̉��Z����
void CGoal::AddGem(void)
{
	m_nPresentGem++;

	if (m_pGemNeeded)
	{
		std::string str = std::to_string(3 - m_nPresentGem) + "/3";

		m_pGemNeeded->ChangeString(str.c_str());
	}
}

//��΂̌��Z����
void CGoal::SubtractGem(void)
{
	m_nPresentGem--;

	if (m_pGemNeeded)
	{
		std::string str = std::to_string(3 - m_nPresentGem) + "/3";

		m_pGemNeeded->ChangeString(str.c_str());
	}
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