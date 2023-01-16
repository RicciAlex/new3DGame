//=============================================================================
//
// fofParticle.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "fogParticle.h"
#include "fogEffect.h"


//�R���X�g���N�^
CFogParticle::CFogParticle()
{
	//�����o�[�ϐ����N���A����
	m_pos = Vec3Null;
	m_bActive = false;
}

//�f�X�g���N�^
CFogParticle::~CFogParticle()
{

}


//����������
HRESULT CFogParticle::Init(void)
{
	//�����o�[�ϐ�������������
	m_pos = Vec3Null;
	m_bActive = false;

	return S_OK;
}

//�I������
void CFogParticle::Uninit(void)
{

}

//�X�V����
void CFogParticle::Update(void)
{
	if (m_bActive)
	{
		for (int nCnt = 0; nCnt < DEFAULT_EFFECT_NUMBER; nCnt++)
		{
			CFogEffect::Create(m_pos, D3DXVECTOR3(0.0f, (float)CObject::random(500, 800) * 0.005f, 0.0f));
		}
	}
}

//�`�揈��
void CFogParticle::Draw(void)
{

}

//�ʒu�̐ݒ菈��
void CFogParticle::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�G�t�F�N�g���X�|�[�����邩�ǂ����̐ݒ菈��
void CFogParticle::SetActiveState(const bool bActive)
{
	m_bActive = bActive;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CFogParticle::GetPos(void)
{
	return m_pos;
}

//�G�t�F�N�g���X�|�[�����邩�ǂ����̎擾����
const bool CFogParticle::GetActiveState(void)
{
	return m_bActive;
}




//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================





//��������
CFogParticle * CFogParticle::Create(const D3DXVECTOR3 pos)
{
	CFogParticle* pParticle = new CFogParticle;		//�C���X�^���X�𐶐�����

	if (FAILED(pParticle->Init()))
	{//����������
		return nullptr;
	}

	pParticle->m_pos = pos;				//�ʒu�̐ݒ�

	return pParticle;					//���������C���X�^���X��Ԃ�
}


