//=============================================================================
//
// fogbot.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "fogBot.h"
#include "fogParticle.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "rendering.h"
#include "BoxHitbox.h"

//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================
const float CFogbot::DEFAULT_VIEW_RANGE = 300.0f;	//�f�B�t�H���g�̌�����͈͂̔��a
D3DXVECTOR3 CFogbot::DEFAULT_PARTICLE_RELATIVE_POS = {0.0f, 66.0f, 0.0f};		//�p�[�e�B�N���̃f�B�t�H���g�̑��Έʒu
const float CFogbot::DEFAULT_FRAME_ANGLE = D3DX_PI * 0.01f;	//�A�j���[�V�����p�̊p�x
const float CFogbot::DEFAULT_ANIM_AMPLITUDE = 0.35f;
const D3DXVECTOR3 CFogbot::DEFAULT_HITBOX_SIZE = { 25.0f, 70.0f, 25.0f };		//�q�b�g�{�b�N�X�̃f�B�t�H���g�T�C�Y


//�R���X�g���N�^
CFogbot::CFogbot()
{
	//�����o�[�ϐ�������������
	m_fAnimAngle = 0.0f;
	m_fRange = 0.0f;
	m_bActive = false;
	m_pParticle = nullptr;
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CFogbot::~CFogbot()
{

}

//����������
HRESULT CFogbot::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ�������������
	m_fAnimAngle = 0.0f;
	m_fRange = DEFAULT_VIEW_RANGE;
	m_bActive = false;
	m_pParticle = nullptr;
	m_pHitbox = nullptr;

	SetModel(CModel::MODEL_ENEMY_FOGBOT);		//���f���̐ݒ�

	return S_OK;
}

//�I������
void CFogbot::Uninit(void)
{
	//�p�[�e�B�N���̔j������
	if (m_pParticle)
	{//null�`�F�b�N
		m_pParticle->Release();		//���������������
		m_pParticle = nullptr;		//�|�C���^��null�ɂ���
	}

	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox)
	{//null�`�F�b�N
		m_pHitbox->Release();		//���������������
		m_pHitbox = nullptr;		//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V����
void CFogbot::Update(void)
{
	D3DXVECTOR3 pos = GetPos();			//�ʒu�̎擾

	UpdateParticle();

	m_fAnimAngle += DEFAULT_FRAME_ANGLE;

	pos.y += DEFAULT_ANIM_AMPLITUDE * sinf(m_fAnimAngle);

	SetPos(pos);

	if (m_pHitbox)
	{
		m_pHitbox->SetPos(pos);
	}
}

//�f�B�t�H���g�̃{�b�g�̐�������
void CFogbot::CreateDefaultBot(void)
{
	SetModelColor(2, ColorGreen);

	if (!m_pParticle)
	{
		m_pParticle = CFogParticle::Create(GetPos() + DEFAULT_PARTICLE_RELATIVE_POS);		//�p�[�e�B�N���̐���
	}

	if (!m_pHitbox)
	{
		m_pHitbox = CBoxHitbox::Create(GetPos(), Vec3Null, DEFAULT_HITBOX_SIZE, CHitbox::TYPE_NEUTRAL, this);		//�q�b�g�{�b�N�X�̐���
	}
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CFogbot * CFogbot::Create(const D3DXVECTOR3 pos, const float shadowPos)
{
	CFogbot* pEnemy = new CFogbot;			//�C���X�^���X�𐶐�����

	if (FAILED(pEnemy->Init()))
	{//����������
		return nullptr;
	}

	pEnemy->SetPos(pos);					//�ʒu�̐ݒ�
	pEnemy->SetShadowHeight(shadowPos);		//�e�̈ʒu��Y���W�̐ݒ�


	pEnemy->SetModelColor(2, ColorGreen);

	pEnemy->m_pParticle = CFogParticle::Create(pos + DEFAULT_PARTICLE_RELATIVE_POS);		//�p�[�e�B�N���̐���

	pEnemy->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, DEFAULT_HITBOX_SIZE, CHitbox::TYPE_NEUTRAL, pEnemy);		//�q�b�g�{�b�N�X�̐���

	return pEnemy;							//���������C���X�^���X��Ԃ�
}



//=============================================================================
//
//							�v���C�x�[�g�֐�
//
//=============================================================================



//�p�[�e�B�N���̍X�V����
void CFogbot::UpdateParticle(void)
{
	D3DXVECTOR3 pos = GetPos(), playerPos = CApplication::GetGame()->GetPlayer()->GetPos();			//�ʒu�̎擾
	D3DXVECTOR3 distance = playerPos - pos;		//�v���C���[�܂ł̋������v�Z����

	if (D3DXVec3Length(&distance) <= m_fRange)
	{//�v���C���[��������͈͂̒��ɂ�����

		if (!m_bActive)
		{//�܂��A�N�e�B�u�ł͂Ȃ�������

			m_bActive = true;			//�A�N�e�B�u��Ԃɂ���

										//�p�[�e�B�N����L���ɂ���
			if (m_pParticle)
			{//null�`�F�b�N

				m_pParticle->SetActiveState(true);

				SetModelColor(2, ColorRed);

				CRenderer* pRenderer = CApplication::GetRenderer();

				if (pRenderer)
				{
					pRenderer->ChangeFog();
				}
			}
		}
	}
	else
	{
		if (m_bActive)
		{//�܂��A�N�e�B�u��������

			m_bActive = false;			//�A�N�e�B�u�ł͂Ȃ���Ԃɂ���

										//�p�[�e�B�N���𖳌��ɂ���
			if (m_pParticle)
			{//null�`�F�b�N
				m_pParticle->SetActiveState(false);

				SetModelColor(2, ColorGreen);

				CRenderer* pRenderer = CApplication::GetRenderer();

				if (pRenderer)
				{
					pRenderer->ChangeFog();
				}
			}
		}
	}
}
