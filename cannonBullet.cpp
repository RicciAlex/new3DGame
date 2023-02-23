//=============================================================================
//
// cannonBullet.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "cannonBullet.h"
#include "boss.h"
#include "explosion.h"
#include "application.h"
#include "sound.h"


//=============================================================================
//								�ÓI�ϐ��̏�����
//=============================================================================
const float CCannonBullet::GRAVITY_ACCELERATION = -1.0f;		//�d�͉����x
const int CCannonBullet::DEFAULT_LIFE = 60;					//�f�B�t�H���g�̃��C�t


//�R���X�g���N�^
CCannonBullet::CCannonBullet()
{
	//�����o�[�ϐ����N���A����
	m_nLife = 0;
	m_move = Vec3Null;

	m_pBoss = nullptr;
}

//�f�X�g���N�^
CCannonBullet::~CCannonBullet()
{

}

//����������
HRESULT CCannonBullet::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	SetModel(CModel::MODEL_CANNON_BULLET);	//���f���̐ݒ�
	m_nLife = DEFAULT_LIFE;					//���C�t�̐ݒ�
	SetDrawDistance(5000.0f);

	return S_OK;
}

//�I������
void CCannonBullet::Uninit(void)
{
	if (m_pBoss)
	{
		m_pBoss = nullptr;
	}

	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V����
void CCannonBullet::Update(void)
{
	m_nLife--;		//���C�t�̍X�V

	if (m_nLife <= 0)
	{//���C�t��0�ɂȂ�����A����

		if (m_pBoss)
		{//null�`�F�b�N

			m_pBoss->DealDamage();		//�_���[�W��^����
		}

		CExplosion::Create(GetPos());	//�����𐶐�����

		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CANNONBALL);

		Release();		//���������������
		return;
	}

	D3DXVECTOR3 pos = GetPos() + m_move;		//�ʒu�̍X�V

	m_move.y += GRAVITY_ACCELERATION;			//�d�͂�������

	SetPos(pos);			//�ʒu�̐ݒ�

	//��{�N���X�̍X�V����
	CModel::Update();
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CCannonBullet* CCannonBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 target)
{
	CCannonBullet* pBullet = new CCannonBullet;		//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������

		return nullptr;
	}

	pBullet->SetPos(pos);		//�ʒu�̐ݒ�
	pBullet->SetShadowHeight(pos.y + 0.1f);		//�e�̈ʒu�̐ݒ�
	pBullet->SetSpeed(target);	//���x�̐ݒ菈��

	return pBullet;				//���������C���X�^���X��Ԃ�
}

CCannonBullet * CCannonBullet::Create(const D3DXVECTOR3 pos, CBoss * pBoss)
{
	CCannonBullet* pBullet = new CCannonBullet;		//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������

		return nullptr;
	}

	pBullet->SetPos(pos);		//�ʒu�̐ݒ�
	pBullet->SetShadowHeight(pos.y + 0.1f);		//�e�̈ʒu�̐ݒ�
	pBullet->m_pBoss = pBoss;	//�{�X�ւ̃|�C���^�̐ݒ�

	D3DXVECTOR3 target = pBoss->GetPos();

	pBullet->SetSpeed(target);	//���x�̐ݒ菈��

	return pBullet;				//���������C���X�^���X��Ԃ�
}



//=============================================================================
//	
//								�v���C�x�[�g�֐�
//
//=============================================================================



//���x�̐ݒ菈��
void CCannonBullet::SetSpeed(const D3DXVECTOR3 target)
{
	D3DXVECTOR3 pos = GetPos(), move = target - pos;		//�ʒu�̎擾

	//���x���v�Z����
	if (DEFAULT_LIFE != 0)
	{
		move.x /= DEFAULT_LIFE;
		move.z /= DEFAULT_LIFE;
	}

	move.y = -GRAVITY_ACCELERATION * ((float)DEFAULT_LIFE * 0.5f);

	m_move = move;				//���x�̐ݒ�
}
