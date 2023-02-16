//=============================================================================
//
// iceBoulder.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "iceBoulder.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "CylinderHitbox.h"
#include "meshfield.h"
#include "iceShard.h"

//=============================================================================
//								�ÓI�ϐ��̏�����
//=============================================================================
const float CIceBoulder::DEFAULT_GRAVITY_ACCELERATION = -0.8f;			//�d��
const int   CIceBoulder::ATTACK_FRAME = 90;								//�U���̃t���[����
const int   CIceBoulder::SHARD_NUMBER = 5;								//�j�Ђ̐�
const D3DXVECTOR3 CIceBoulder::HITBOX_RELATIVE_POS = { 0.0f, 49.5f, 0.0f };			//�q�b�g�{�b�N�X�̑��Έʒu
const D3DXVECTOR3 CIceBoulder::HITBOX_SIZE = { 50.0f, 100.0f, 50.0f };				//�q�b�g�{�b�N�X�̃T�C�Y


//�R���X�g���N�^
CIceBoulder::CIceBoulder()
{
	//�����o�[�ϐ����N���A����
	m_target = Vec3Null;
	m_move = Vec3Null;

	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CIceBoulder::~CIceBoulder()
{

}

//����������
HRESULT CIceBoulder::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	SetModel(CModel::MODEL_ICE_BOULDER);		//���f���̐ݒ�
	StartRotation(D3DXVECTOR3(D3DX_PI * 0.0025f * (float)random(-500, 500), D3DX_PI * 0.0025f * (float)random(-500, 500), 0.0f));	//��]�̊J�n����
	
	return S_OK;
}

//�I������
void CIceBoulder::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if(m_pHitbox)
	{//null�`�F�b�N

		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V����
void CIceBoulder::Update(void)
{
	//��{�N���X�̍X�V����
	CModel::Update();

	m_move.y += DEFAULT_GRAVITY_ACCELERATION;
	SetPos(GetPos() + m_move);			//�ʒu�̍X�V

	if (GetPos().y <= -5000.0f)
	{
		Release();
		return;
	}

	UpdateHitbox();			//�q�b�g�{�b�N�X�̍X�V����
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CIceBoulder* CIceBoulder::Create(const D3DXVECTOR3 pos)
{
	CIceBoulder* pBoulder = new CIceBoulder;		//�C���X�^���X�𐶐�����

	if (FAILED(pBoulder->Init()))
	{//����������
		return nullptr;
	}

	pBoulder->SetPos(pos);			//�ʒu�̐ݒ�
	pBoulder->SetSpeed();			//���x�̐ݒ菈��

	pBoulder->m_pHitbox = CCylinderHitbox::Create(pos + HITBOX_RELATIVE_POS, Vec3Null, HITBOX_SIZE, CHitbox::TYPE_OBSTACLE, -1, pBoulder, CHitbox::EFFECT_BOUNCE);

	return pBoulder;				//���������C���X�^���X��Ԃ�
}



//=============================================================================
//
//								�v���C�x�[�g�֐�
//
//=============================================================================



//���x�̐ݒ菈��
void CIceBoulder::SetSpeed(void)
{
	m_target = CApplication::GetGame()->GetPlayer()->GetPos();		//�v���C���[�̈ʒu�̎擾

	m_move = m_target - GetPos();			//�����̌v�Z
	m_move.x /= (float)ATTACK_FRAME;		//���x��X���W�̐ݒ�
	m_move.z /= (float)ATTACK_FRAME;		//���x��Z���W�̐ݒ�

	m_move.y = -DEFAULT_GRAVITY_ACCELERATION * ATTACK_FRAME * 0.5f;		//���x��Y���W�̐ݒ�
}

//�q�b�g�{�b�N�X�̍X�V����
void CIceBoulder::UpdateHitbox(void)
{
	if (m_pHitbox)
	{
		m_pHitbox->SetPos(GetPos() + HITBOX_RELATIVE_POS);

		if (m_pHitbox->GetCollisionState())
		{
			CreateShard();		//�j�Ђ̐�������

			Release();
			return;
		}
	}

	if (CMeshfield::FieldInteraction(this))
	{
		CreateShard();			//�j�Ђ̐�������

		Release();
		return;
	}
}

//�j�Ђ̐�������
void CIceBoulder::CreateShard(void)
{
	for (int nCnt = 0; nCnt < SHARD_NUMBER; nCnt++)
	{
		D3DXVECTOR3 translation = D3DXVECTOR3((float)random(-500, 500) * 0.01f * 20.0f, (float)random(-500, 500) * 0.01f * 20.0f, (float)random(-500, 500) * 0.01f * 20.0f);
		D3DXVECTOR3 move = Vec3Null;
		D3DXVec3Normalize(&move, &translation);
		move.y = (float)random(250, 500) * 0.01f * 5.0f;

		CIceShard::Create(GetPos() + translation, move);
	}
}
