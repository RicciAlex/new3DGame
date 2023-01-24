//=============================================================================
//
// fireParticle.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "fireParticle.h"
#include "fireEffect.h"
#include "application.h"
#include "camera.h"


//�R���X�g���N�^
CFireParticle::CFireParticle()
{
	//�����o�[�ϐ����N���A����
	m_pos = Vec3Null;
	m_bActive = false;
}

//�f�X�g���N�^
CFireParticle::~CFireParticle()
{

}


//����������
HRESULT CFireParticle::Init(void)
{
	//�����o�[�ϐ�������������
	m_pos = Vec3Null;
	m_bActive = true;

	return S_OK;
}

//�I������
void CFireParticle::Uninit(void)
{

}

//�X�V����
void CFireParticle::Update(void)
{
	if (m_bActive)
	{
		D3DXVECTOR3 dist = CApplication::GetCamera()->GetPos() - GetPos();

		if (D3DXVec3Length(&dist) <= 2500.0f)
		{
			CFireEffect* pEffect = nullptr;

			for (int nCnt = 0; nCnt < DEFAULT_EFFECT_NUMBER; nCnt++)
			{
				CFireEffect::Create(m_pos + D3DXVECTOR3((nCnt * 5.0f) - 15, 0.0f, 0.0f), D3DXVECTOR3((float)CObject::random(-50, 50) * 0.01f, (float)CObject::random(10, 100) * 0.025f, (float)CObject::random(-50, 50) * 0.01f));
			}
		}
	}
}

//�`�揈��
void CFireParticle::Draw(void)
{

}

//�ʒu�̐ݒ菈��
void CFireParticle::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�G�t�F�N�g���X�|�[�����邩�ǂ����̐ݒ菈��
void CFireParticle::SetActiveState(const bool bActive)
{
	m_bActive = bActive;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CFireParticle::GetPos(void)
{
	return m_pos;
}

//�G�t�F�N�g���X�|�[�����邩�ǂ����̎擾����
const bool CFireParticle::GetActiveState(void)
{
	return m_bActive;
}




//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================





//��������
CFireParticle * CFireParticle::Create(const D3DXVECTOR3 pos)
{
	CFireParticle* pParticle = new CFireParticle;		//�C���X�^���X�𐶐�����

	if (FAILED(pParticle->Init()))
	{//����������
		return nullptr;
	}

	pParticle->m_pos = pos;				//�ʒu�̐ݒ�

	return pParticle;					//���������C���X�^���X��Ԃ�
}


