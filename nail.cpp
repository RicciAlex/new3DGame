//=============================================================================
//
// nail.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "nail.h"
#include "BoxHitbox.h"

//�R���X�g���N�^
CNail::CNail()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;				//�q�b�g�{�b�N�X
}

//�f�X�g���N�^
CNail::~CNail()
{

}

//����������
HRESULT CNail::Init(void)
{
	//�����o�[�ϐ�������������
	if (FAILED(CModel::Init()))
	{//�e�N���X�̏���������
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CNail::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}
}

//�X�V����
void CNail::Update(void)
{

}



//=============================================================================
//
// 
//
//=============================================================================




//��������
CNail* CNail::Create(const D3DXVECTOR3 pos)
{
	CNail* pNail = new CNail;			//�C���X�^���X�𐶐�����

	if (FAILED(pNail->Init()))
	{//����������
		return nullptr;
	}

	pNail->SetModel(CModel::MODEL_NAILS);		//���f���̐ݒ�
	pNail->SetPos(pos);							//�ʒu��ݒ肷��
	pNail->SetScale(0.75f);						//�X�P�[����ݒ肷��
	pNail->SetShadowDraw(false);				//�e��`�悵�Ȃ��悤�ɐݒ肷��

	float fRot = (float)CObject::random(-31415, 31415) * 0.0001f;
	pNail->SetRot(D3DXVECTOR3(0.0f, fRot, 0.0f));

	pNail->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, D3DXVECTOR3(37.0f, 10.0f, 37.0f), CHitbox::TYPE_OBSTACLE, pNail, -1, CHitbox::EFFECT_BOUNCE);		//�q�b�g�{�b�N�X�̐���

	return pNail;
}