//=============================================================================
//
// FirePipe.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "FirePipe.h"
#include "fireParticle.h"
#include "CylinderHitbox.h"
#include "application.h"
#include "sound.h"
#include "game.h"
#include "player.h"

//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================
const D3DXVECTOR3 CFirePipe::FIRE_HITBOX_SIZE = {72.0f, 100.0f, 72.0f};		//�΂̃q�b�g�{�b�N�X�̃T�C�Y
const D3DXVECTOR3 CFirePipe::HITBOX_SIZE =		{72.0f, 1000.0f, 72.0f};		//�q�b�g�{�b�N�X�̃T�C�Y

//�R���X�g���N�^
CFirePipe::CFirePipe()
{
	//�����o�[�ϐ����N���A����
	m_nCntTime = 0;
	m_nFireTime = 0;
	m_nCntSound = 0;

	m_pParticle = nullptr;
	m_pHitbox = nullptr;
	m_pFireHitbox = nullptr;
}

//�f�X�g���N�^
CFirePipe::~CFirePipe()
{

}

//����������
HRESULT CFirePipe::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ�������������
	m_nCntTime = 0;
	m_nFireTime = DEFAULT_FIRE_TIME;
	m_nCntSound = 0;

	m_pParticle = nullptr;
	m_pHitbox = nullptr;
	m_pFireHitbox = nullptr;

	return S_OK;
}

//�I������
void CFirePipe::Uninit(void)
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

	//�΃q�b�g�{�b�N�X�̔j������
	if (m_pFireHitbox)
	{//null�`�F�b�N
		m_pFireHitbox->Release();		//���������������
		m_pFireHitbox = nullptr;		//�|�C���^��null�ɂ���
	}
}

//�X�V����
void CFirePipe::Update(void)
{
	m_nCntTime++;			//�J�E���^�[���C���N�������g����

	if (m_nCntTime >= m_nFireTime)
	{//�ݒ肵�����Ԃ��o������

		m_nCntTime = 0;		//�J�E���^�[�����ɖ߂�

		if (m_pParticle)
		{//�p�[�e�B�N����null�`�F�b�N

			//�A�N�e�B�u��Ԃ��t�ɂ���
			if (m_pParticle->GetActiveState())
			{
				m_pParticle->SetActiveState(false);

				//�q�b�g�{�b�N�X���ړ�����
				if (m_pFireHitbox)
				{//null�`�F�b�N
					m_pFireHitbox->SetPos(GetPos() + D3DXVECTOR3(0.0f, -5000.0f, 0.0f));
				}

				m_nCntSound = 0;
			}
			else
			{
				m_pParticle->SetActiveState(true);

				//�q�b�g�{�b�N�X���ړ�����
				if (m_pFireHitbox)
				{//null�`�F�b�N
					m_pFireHitbox->SetPos(GetPos());
				}
			}
		}
	}

	if (m_nCntSound <= 0)
	{
		if (m_pParticle)
		{//�p�[�e�B�N����null�`�F�b�N

		 //�A�N�e�B�u��Ԃ��t�ɂ���
			if (m_pParticle->GetActiveState())
			{
				D3DXVECTOR3 dist = CApplication::GetGame()->GetPlayer()->GetPos() - GetPos();

				if (D3DXVec3Length(&dist) <= 2500.0f)
				{
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);

					m_nCntSound = 30;
				}
			}
		}
	}
	else
	{
		m_nCntSound--;
	}
}

void CFirePipe::Draw(void)
{
	CModel::Draw();
}



//=============================================================================
//
// FirePipe.cpp
// Author : Ricci Alex
//
//=============================================================================



//��������
CFirePipe* CFirePipe::Create(const D3DXVECTOR3 pos)
{
	CFirePipe* pPipe = new CFirePipe;			//�C���X�^���X�𐶐�����

	if (FAILED(pPipe->Init()))
	{//����������
		return nullptr;
	}

	pPipe->SetModel(CModel::MODEL_PIPE);	//���f���̐ݒ�
	pPipe->SetPos(pos);						//�ʒu�̐ݒ�
	pPipe->SetShadowDraw(false);			//�e��`�悵�Ȃ��悤�ɐݒ肷��

	pPipe->m_pParticle = CFireParticle::Create(pos);			//�p�[�e�B�N���𐶐�����

	//�q�b�g�{�b�N�X�̐���
	pPipe->m_pHitbox = CCylinderHitbox::Create(pos + D3DXVECTOR3(0.0f, -1000.0f, 0.0f), Vec3Null, HITBOX_SIZE, CHitbox::TYPE_NEUTRAL, pPipe);
	pPipe->m_pFireHitbox = CCylinderHitbox::Create(pos, Vec3Null, FIRE_HITBOX_SIZE, CHitbox::TYPE_OBSTACLE, -1, pPipe, CHitbox::EFFECT_BOUNCE);

	if (pPipe->m_pFireHitbox)
	{
		pPipe->m_pFireHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);
	}

	return pPipe;				//���������C���X�^���X��Ԃ�
}

//��������
CFirePipe* CFirePipe::Create(const D3DXVECTOR3 pos, const int nFireTime)
{
	CFirePipe* pPipe = new CFirePipe;			//�C���X�^���X�𐶐�����

	if (FAILED(pPipe->Init()))
	{//����������
		return nullptr;
	}

	pPipe->SetModel(CModel::MODEL_PIPE);	//���f���̐ݒ�
	pPipe->SetPos(pos);						//�ʒu�̐ݒ�
	pPipe->SetShadowDraw(false);			//�e��`�悵�Ȃ��悤�ɐݒ肷��

	if (nFireTime >= MIN_FIRE_TIME)
	{
		pPipe->m_nFireTime = nFireTime;			//�΂�����/�t����܂ł̃t���[�����̐ݒ�
	}
	else
	{
		pPipe->m_nFireTime = MIN_FIRE_TIME;		//�΂�����/�t����܂ł̃t���[�����̐ݒ�
	}

	pPipe->m_pParticle = CFireParticle::Create(pos);			//�p�[�e�B�N���𐶐�����

	//�q�b�g�{�b�N�X�̐���
	pPipe->m_pHitbox = CCylinderHitbox::Create(pos + D3DXVECTOR3(0.0f, -1000.0f, 0.0f), Vec3Null, HITBOX_SIZE, CHitbox::TYPE_NEUTRAL, pPipe);
	pPipe->m_pFireHitbox = CCylinderHitbox::Create(pos, Vec3Null, FIRE_HITBOX_SIZE, CHitbox::TYPE_OBSTACLE, -1, pPipe, CHitbox::EFFECT_BOUNCE);

	if (pPipe->m_pFireHitbox)
	{
		pPipe->m_pFireHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);
	}

	return pPipe;				//���������C���X�^���X��Ԃ�
}