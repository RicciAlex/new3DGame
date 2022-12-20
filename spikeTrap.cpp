//=============================================================================
//
// spikeTrap.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "spikeTrap.h"
#include "BoxHitbox.h"
#include "application.h"
#include "rendering.h"
#include "camera.h"
#include "directionalLight.h"
#include "phongShading.h"


//�R���X�g���N�^
CSpikeTrap::CSpikeTrap()
{
	//�����o�[�ϐ����N���A����
	m_nDelay = 0;
	m_nCntTime = 0;
	m_fSpeed = 0.0f;
	m_fStartingHeight = 0.0f;
	m_bMoving = false;

	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CSpikeTrap::~CSpikeTrap()
{

}

//����������
HRESULT CSpikeTrap::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ�������������
	m_nDelay = 60;
	m_nCntTime = 0;
	m_fSpeed = 1.0f;
	m_fStartingHeight = 0.0f;
	m_bMoving = false;

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CSpikeTrap::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j��
	if (m_pHitbox)
	{//null�`�F�b�N
		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V����
void CSpikeTrap::Update(void)
{
	//�㉺�ړ��̏���
	if (m_bMoving)
	{//�����Ă�����

		D3DXVECTOR3 pos = GetPos();		//�ʒu�̎擾

		pos.y += m_fSpeed;				//�����̍X�V

		//���E�𒴂�����A�߂��Ă���A���x���t�ɂ��āA�����Ȃ��悤�ɐݒ肷��
		if (pos.y >= m_fStartingHeight + 40.0f)
		{
			m_fSpeed *= -1.0f;
			pos.y = m_fStartingHeight + 40.0f;
			m_bMoving = false;
		}
		else if (pos.y <= m_fStartingHeight)
		{
			pos.y = m_fStartingHeight;
			m_fSpeed *= -1.0f;
			m_bMoving = false;
		}

		SetPos(pos);				//�ʒu�̐ݒ�
	}
	else
	{//�����Ă��Ȃ�������

		m_nCntTime++;			//�J�E���^�[���C���N�������g����

		if (m_nCntTime >= m_nDelay)
		{//�ݒ肵�����Ԃ��o������A�J�E���^�[��0�ɖ߂��āA�����悤�ɐݒ肷��
			m_nCntTime = 0;
			m_bMoving = true;
		}
	}

	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox)
	{//null�`�F�b�N
		m_pHitbox->SetPos(GetPos());		//�q�b�g�{�b�N�X�̈ʒu�̍X�V

		m_pHitbox->Update();
	}
}

//�`�揈��
void CSpikeTrap::Draw(void)
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

//�������̃f�B���C�̐ݒ菈��
void CSpikeTrap::SetStartingDelay(const int nDelay)
{
	m_nCntTime = -nDelay;
}


//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CSpikeTrap * CSpikeTrap::Create(const D3DXVECTOR3 pos)
{
	CSpikeTrap* pTrap = new CSpikeTrap;			//�C���X�^���X�𐶐�����

	if (FAILED(pTrap->Init()))
	{//����������
		return nullptr;
	}

	pTrap->SetPos(pos);								//�ʒu�̐ݒ�
	pTrap->SetModel(CModel::MODEL_SPIKE_TRAP);		//���f���̐ݒ�
	pTrap->m_fStartingHeight = pos.y - 40.0f;		//�������̍����̐ݒ�

													//�q�b�g�{�b�N�X�̐���
	pTrap->m_pHitbox = CBoxHitbox::Create(D3DXVECTOR3(pos.x, pos.y - 40.0f, pos.z), Vec3Null, D3DXVECTOR3(32.0f, 35.0f, 32.0f), CHitbox::TYPE_OBSTACLE, pTrap, -1, CHitbox::EFFECT_BOUNCE);

	CModel* pModel = CModel::Create(CModel::MODEL_SPIKE_BASE, D3DXVECTOR3(pos.x, pos.y + 0.1f, pos.z));			//���̃��f���̐���
	pModel->SetShadowDraw(false);

	return pTrap;					//���������C���X�^���X��Ԃ�
}

//��������
CSpikeTrap* CSpikeTrap::Create(const D3DXVECTOR3 pos, const float fSpeed)
{
	CSpikeTrap* pTrap = new CSpikeTrap;			//�C���X�^���X�𐶐�����

	if (FAILED(pTrap->Init()))
	{//����������
		return nullptr;
	}

	pTrap->SetPos(pos);								//�ʒu�̐ݒ�
	pTrap->SetModel(CModel::MODEL_SPIKE_TRAP);		//���f���̐ݒ�
	pTrap->m_fSpeed = fSpeed;						//���x�̐ݒ�
	pTrap->m_fStartingHeight = pos.y - 40.0f;		//�������̍����̐ݒ�

	//�q�b�g�{�b�N�X�̐���
	pTrap->m_pHitbox = CBoxHitbox::Create(D3DXVECTOR3(pos.x, pos.y - 40.0f, pos.z), Vec3Null, D3DXVECTOR3(32.0f, 35.0f, 32.0f), CHitbox::TYPE_OBSTACLE, pTrap, -1, CHitbox::EFFECT_BOUNCE);

	CModel* pModel = CModel::Create(CModel::MODEL_SPIKE_BASE, D3DXVECTOR3(pos.x, pos.y + 0.1f, pos.z));			//���̃��f���̐���
	pModel->SetShadowDraw(false);

	return pTrap;					//���������C���X�^���X��Ԃ�

}

//��������(delay�Ƃ����͉̂�������A�O��オ��܂ł̃t���[���ł��B�f�t�H���g��60)
CSpikeTrap* CSpikeTrap::Create(const D3DXVECTOR3 pos, const float fSpeed, const int nDelay)
{
	CSpikeTrap* pTrap = new CSpikeTrap;			//�C���X�^���X�𐶐�����

	if (FAILED(pTrap->Init()))
	{//����������
		return nullptr;
	}

	pTrap->SetPos(pos);								//�ʒu�̐ݒ�
	pTrap->SetModel(CModel::MODEL_SPIKE_TRAP);		//���f���̐ݒ�
	pTrap->m_fSpeed = fSpeed;						//���x�̐ݒ�
	pTrap->m_fStartingHeight = pos.y - 40.0f;		//�������̍����̐ݒ�

	if (nDelay <= 0)
	{
		pTrap->m_nDelay = 1;							//�f�B���C�̐ݒ�
	}
	else
	{
		pTrap->m_nDelay = nDelay;						//�f�B���C�̐ݒ�
	}

	//�q�b�g�{�b�N�X�̐���
	pTrap->m_pHitbox = CBoxHitbox::Create(D3DXVECTOR3(pos.x, pos.y - 40.0f, pos.z), Vec3Null, D3DXVECTOR3(32.0f, 35.0f, 32.0f), CHitbox::TYPE_OBSTACLE, pTrap, -1, CHitbox::EFFECT_BOUNCE);

	CModel* pModel = CModel::Create(CModel::MODEL_SPIKE_BASE, D3DXVECTOR3(pos.x, pos.y + 0.1f, pos.z));			//���̃��f���̐���
	pModel->SetShadowDraw(false);

	return pTrap;				//���������C���X�^���X��Ԃ�
}

CSpikeTrap * CSpikeTrap::Create(const D3DXVECTOR3 pos, const float fSpeed, const int nDelay, const int nStartDelay)
{
	CSpikeTrap* pTrap = new CSpikeTrap;			//�C���X�^���X�𐶐�����

	if (FAILED(pTrap->Init()))
	{//����������
		return nullptr;
	}

	pTrap->SetPos(pos);								//�ʒu�̐ݒ�
	pTrap->SetModel(CModel::MODEL_SPIKE_TRAP);		//���f���̐ݒ�
	pTrap->m_fSpeed = fSpeed;						//���x�̐ݒ�
	pTrap->m_fStartingHeight = pos.y - 40.0f;		//�������̍����̐ݒ�
	pTrap->m_nCntTime = -nStartDelay;				//�������̃f�B���C�̐ݒ�

	if (nDelay <= 0)
	{
		pTrap->m_nDelay = 1;							//�f�B���C�̐ݒ�
	}
	else
	{
		pTrap->m_nDelay = nDelay;						//�f�B���C�̐ݒ�
	}

	//�q�b�g�{�b�N�X�̐���
	pTrap->m_pHitbox = CBoxHitbox::Create(D3DXVECTOR3(pos.x, pos.y - 40.0f, pos.z), Vec3Null, D3DXVECTOR3(32.0f, 35.0f, 32.0f), CHitbox::TYPE_OBSTACLE, pTrap, -1, CHitbox::EFFECT_BOUNCE);

	CModel* pModel = CModel::Create(CModel::MODEL_SPIKE_BASE, D3DXVECTOR3(pos.x, pos.y + 0.1f, pos.z));			//���̃��f���̐���
	pModel->SetShadowDraw(false);

	return pTrap;				//���������C���X�^���X��Ԃ�
}
