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
#include "application.h"
#include "rendering.h"
#include "phongShading.h"
#include "camera.h"
#include "directionalLight.h"

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

//�`�揈��
void CNail::Draw(void)
{
	CPhongShading* pPhong = CApplication::GetRenderer()->GetPhongEffect();

	if (pPhong)
	{
		D3DXVECTOR3 posV = CApplication::GetCamera()->GetPos();		//���_�̎擾

																	//���_�̈ʒu��Vector4�ɕϊ�����
		D3DXVECTOR4 cameraPos = {};

		cameraPos.x = posV.x;
		cameraPos.y = posV.y;
		cameraPos.z = posV.z;
		cameraPos.w = 1.0f;

		//�ʒu���擾���Ă���AVector4�ɕϊ����āA���K������
		D3DXVECTOR3 l = CDirectionalLight::GetPrincipalLightDir();
		D3DXVec3Normalize(&l, &l);
		D3DXVECTOR4 light = D3DXVECTOR4(posV.x - l.x, posV.y - l.y, posV.z - l.z, 0.0f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light, (D3DXVECTOR3*)&light);

		pPhong->Begin();											//�V�F�[�_�[�G�t�F�N�g�̊J�n����
		pPhong->SetAmbient(0.50f);									//�����̐ݒ�
		pPhong->SetSpecular(40.0f);									//�X�y�L�����[�͈̔͂̐ݒ�
		pPhong->SetSpecularPower(0.75f);							//�X�y�L�����[�̋��x�̐ݒ�
		pPhong->SetMatrix(GetWorldMatrix(), &cameraPos, &light);	//���[���h�}�g���b�N�X�̐ݒ�
		pPhong->BeginPass();										//�p�X�̊J�n
	}

	//��{�N���X�̕`�揈��
	CModel::Draw();

	if (pPhong)
	{
		pPhong->EndPass();		//�p�X�̏I������
		pPhong->End();			//�V�F�[�_�[�G�t�F�N�g�̏I������
	}
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