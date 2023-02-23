//=============================================================================
//
// explosion.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "explosion.h"
#include "fireEffect.h"


//=============================================================================
//								�ÓI�ϐ��̏�����
//=============================================================================
const int CExplosion::DEFAULT_LIFE = 30;	//�f�B�t�H���g�̃��C�t
const int CExplosion::EFFECT_NUMBER = 35;	//���t���[�����������G�t�F�N�g��


//�R���X�g���N�^
CExplosion::CExplosion()
{
	//�����o�[�ϐ����N���A����
	m_pos = Vec3Null;
}

//�f�X�g���N�^
CExplosion::~CExplosion()
{

}


//����������
HRESULT CExplosion::Init(void)
{
	m_nLife = DEFAULT_LIFE;

	return S_OK;
}

//�I������
void CExplosion::Uninit(void)
{

}

//�X�V����
void CExplosion::Update(void)
{
	m_nLife--;			//���C�t�̍X�V

	if (m_nLife <= 0)
	{
		Release();
		return;
	}

	for (int nCnt = 0; nCnt < EFFECT_NUMBER; nCnt++)
	{
		D3DXVECTOR3 pos = m_pos + D3DXVECTOR3((float)random(-1000, 1000) * 0.01f, (float)random(-1000, 1000) * 0.01f, (float)random(-1000, 1000) * 0.01f);
		D3DXVECTOR3 move = D3DXVECTOR3((float)random(-1000, 1000) * 0.005f, (float)random(-1000, 1000) * 0.005f, (float)random(-1000, 1000) * 0.005f);

		CFireEffect::Create(pos, move);
	}
}

//�`�揈��
void CExplosion::Draw(void)
{

}

//�ʒu�̐ݒ菈��
void CExplosion::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CExplosion::GetPos(void)
{
	return m_pos;
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CExplosion* CExplosion::Create(const D3DXVECTOR3 pos)
{
	CExplosion* pExplosion = new CExplosion;		//�C���X�^���X�𐶐�����

	if (FAILED(pExplosion->Init()))
	{//����������

		return nullptr;
	}

	pExplosion->m_pos = pos;	//�ʒu�̐ݒ�

	return pExplosion;			//���������C���X�^���X��Ԃ�
}