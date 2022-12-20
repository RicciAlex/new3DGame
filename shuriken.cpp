//=============================================================================
//
// shuriken.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "shuriken.h"
#include "BoxHitbox.h"
#include "application.h"
#include "rendering.h"
#include "camera.h"
#include "directionalLight.h"
#include "phongShading.h"

//�R���X�g���N�^
CShuriken::CShuriken()
{
	//�����o�[�ϐ����N���A����
	m_move = Vec3Null;
	m_nLife = 0;

	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CShuriken::~CShuriken()
{

}

//����������
HRESULT CShuriken::Init(void)
{
	if (FAILED(CModel::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	//�����o�[�ϐ�������������
	m_move = Vec3Null;
	m_nLife = 120;

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CShuriken::Uninit(void)
{
	if (m_pHitbox)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}
}

//�X�V����
void CShuriken::Update(void)
{
	CModel::Update();

	D3DXVECTOR3 pos = GetPos() + m_move;
	SetPos(pos);

	if (m_pHitbox)
	{
		m_pHitbox->SetPos(GetPos());

		if (m_pHitbox->GetCollisionState())
		{
			m_pHitbox->SetCollisionState(false);
		}
	}
	
	m_nLife--;

	if (m_nLife <= 0)
	{
		Release();
	}
}

void CShuriken::Draw(void)
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
//								�ÓI�֐�
//
//=============================================================================



//��������
CShuriken* CShuriken::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 speed)
{
	CShuriken* pShuriken = new CShuriken;

	if (FAILED(pShuriken->Init()))
	{
		return nullptr;
	}

	pShuriken->SetPos(pos);
	pShuriken->m_move = speed;
	pShuriken->SetModel(CModel::MODEL_SHURIKEN);
	pShuriken->SetShadowDraw(false);
	pShuriken->StartRotation(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.1f));

	pShuriken->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(17.0f, 20.0f, 17.0f), CHitbox::TYPE_OBSTACLE, pShuriken, -1, CHitbox::EFFECT_DAMAGE);

	return pShuriken;
}

CShuriken* CShuriken::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 speed, const float fShadowHeight)
{
	CShuriken* pShuriken = new CShuriken;

	if (FAILED(pShuriken->Init()))
	{
		return nullptr;
	}

	pShuriken->SetPos(pos);
	pShuriken->m_move = speed;
	pShuriken->SetModel(CModel::MODEL_SHURIKEN);
	pShuriken->SetShadowHeight(fShadowHeight);
	pShuriken->StartRotation(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.1f));

	pShuriken->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(17.0f, 20.0f, 17.0f), CHitbox::TYPE_OBSTACLE, pShuriken, -1, CHitbox::EFFECT_DAMAGE);

	return pShuriken;
}