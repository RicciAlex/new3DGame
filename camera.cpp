//=============================================================================
//
// camera.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "camera.h"
#include "application.h"
#include "rendering.h"
//#include "inputMouse.h"
#include "inputKeyboard.h"
#include "debugProc.h"
#include "pointLight.h"
#include "player.h"

//=============================================================================
//
//�ÓI�ϐ��̏�����
//
//=============================================================================
const float CCamera::CAMERA_SPEED = 1.0;				//�J�����̈ړ���

//�R���X�g���N�^
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_
	m_DestPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړI�̎��_
	m_DestPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړI�̒����_
	m_vecU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//������x�N�g��
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړI�̌���
	m_fLenght = 0.0f;									//���_���璍���_�܂ł̋���			
	m_nDelay = 0;										//�f�B���C	
}

//�f�X�g���N�^
CCamera::~CCamera()
{

}

//����������
HRESULT CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�����_
	m_DestPosV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړI�̎��_
	m_DestPosR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړI�̒����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//������x�N�g��
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړI�̌���
	m_fLenght = 0.0f;									//���_���璍���_�܂ł̋���	
	m_nDelay = 0;										//�f�B���C

	return S_OK;
}

//�I������
void CCamera::Uninit(void)
{

}

//�X�V����
void CCamera::Update(void)
{
	if (CInputKeyboard::GetKeyboardPress(DIK_UP))
	{
		D3DXVECTOR3 dir = m_posR - m_posV;
		dir.y = 0.0f;
		D3DXVec3Normalize(&dir, &dir);
		D3DXVECTOR3 move = D3DXVECTOR3(2.5f * dir.x, 0.0f, 2.5f * dir.z);
		m_posV += move;
		m_posR += move;
	}
	if (CInputKeyboard::GetKeyboardPress(DIK_DOWN))
	{
		D3DXVECTOR3 dir = m_posR - m_posV;
		dir.y = 0.0f;
		D3DXVec3Normalize(&dir, &dir);
		D3DXVECTOR3 move = D3DXVECTOR3(2.5f * ((dir.x * cosf(D3DX_PI)) - (dir.z * sinf((D3DX_PI)))), 0.0f, 2.5f * ((dir.z * cosf(D3DX_PI) + dir.x * sinf(D3DX_PI))));
		m_posV += move;
		m_posR += move;
	}
	if (CInputKeyboard::GetKeyboardPress(DIK_LEFT))
	{
		D3DXVECTOR3 dir = m_posR - m_posV;
		dir.y = 0.0f;
		D3DXVec3Normalize(&dir, &dir);
		D3DXVECTOR3 move = D3DXVECTOR3(2.5f * ((dir.x * cosf(D3DX_PI * 0.5f)) - (dir.z * sinf((D3DX_PI * 0.5f)))), 0.0f, 2.5f * ((dir.z * cosf(D3DX_PI * 0.5f) + dir.x * sinf(D3DX_PI * 0.5f))));
		m_posV += move;
		m_posR += move;
	}
	if (CInputKeyboard::GetKeyboardPress(DIK_RIGHT))
	{
		D3DXVECTOR3 dir = m_posR - m_posV;
		dir.y = 0.0f;
		D3DXVec3Normalize(&dir, &dir);
		D3DXVECTOR3 move = D3DXVECTOR3(2.5f * ((dir.x * cosf(-D3DX_PI * 0.5f)) - (dir.z * sinf((-D3DX_PI * 0.5f)))), 0.0f, 2.5f * ((dir.z * cosf(-D3DX_PI * 0.5f) + dir.x * sinf(-D3DX_PI * 0.5f))));
		m_posV += move;
		m_posR += move;
	}
}

//�ݒ菈��
void CCamera::Set(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		5000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);
}

//���_�̎擾����
const D3DXVECTOR3 CCamera::GetPos(void)
{
	return m_posV;
}

//��]�p�x�̎擾����
const D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}

//�J�����̌����̎擾����
const D3DXVECTOR3 CCamera::GetDirection(void)
{
	D3DXVECTOR3 dir = m_posR - m_posV;
	D3DXVec3Normalize(&dir, &dir);

	return dir;
}

//�����_�̎擾����
const D3DXVECTOR3 CCamera::GetFocalPoint(void)
{
	return m_posR;
}

//�����_�̐ݒ菈��
void CCamera::SetFocalPoint(const D3DXVECTOR3 pos)
{
	m_posR = pos;
}

//���_�����_�̐ݒ�
void CCamera::SetPos(const D3DXVECTOR3 posV, const D3DXVECTOR3 posR)
{
	m_posV = posV;
	m_posR = posR;
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================


//��������
CCamera* CCamera::Create(D3DXVECTOR3 pos, D3DXVECTOR3 focalPoint)
{
	CCamera* pCamera = new CCamera;				//�J�����̐���

	if (FAILED(pCamera->Init()))
	{//����������
		return nullptr;
	}

	pCamera->m_posV = pos;									//���_�̐ݒ�
	pCamera->m_posR = focalPoint;							//�����_�̐ݒ�
															
	D3DXVECTOR3 v = pCamera->m_posR - pCamera->m_posV;		//���_���璍���_�܂ł̃x�N�g�����v�Z����
	D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);		//�P�ʃx�N�g��
	D3DXVec3Normalize(&v, &v);								//���_���璍���_�܂ł̃x�N�g���𐳋K������

	pCamera->m_rot.y = acosf(D3DXVec3Dot(&v, &unit));		//���ς��v�Z����

	if (pCamera->m_posR.z < pCamera->m_posV.z)
	{//�K�v��������A���K������
		pCamera->m_rot.y *= -1.0f;
	}

	//���_���璍���_�܂ł̋������v�Z����
	pCamera->m_fLenght = sqrtf(((pCamera->m_posR.x - pCamera->m_posV.x) * (pCamera->m_posR.x - pCamera->m_posV.x)) + ((pCamera->m_posR.z - pCamera->m_posV.z) * (pCamera->m_posR.z - pCamera->m_posV.z)));

	return pCamera;				//���������J������Ԃ�
}