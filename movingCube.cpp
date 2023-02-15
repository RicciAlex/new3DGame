//=============================================================================
//
// movingCube.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "movingCube.h"
#include "BoxHitbox.h"
#include "application.h"
#include "rendering.h"
#include "phongShading.h"
#include "camera.h"
#include "directionalLight.h"
#include "game.h"
#include "player.h"

//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================
const D3DXVECTOR3 CMovingCube::m_metalBoxSize = D3DXVECTOR3(100.0f, 20.0f, 100.0f);				//���^���{�b�N�X�̃T�C�Y


//�R���X�g���N�^
CMovingCube::CMovingCube()
{
	//�����o�[�ϐ����N���A����
	m_OriginalPos = Vec3Null;
	m_size = Vec3Null;
	m_move = Vec3Null;
	m_fRange = 0.0f;

	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CMovingCube::~CMovingCube()
{

}


//����������
HRESULT CMovingCube::Init(void)
{
	if (FAILED(CModel::Init()))
	{//��{�N���X�̏���������

		return -1;
	}

	//�����o�[�ϐ�������������
	m_OriginalPos = Vec3Null;
	m_size = Vec3Null;
	m_move = Vec3Null;
	m_fRange = 0.0f;

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CMovingCube::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox)
	{//null�`�F�b�N
		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V����
void CMovingCube::Update(void)
{
	SetPos(GetPos() + m_move);			//�ʒu�̍X�V

	//�q�b�g�{�b�N�X�̍X�V
	if (m_pHitbox)
	{//null�`�F�b�N

		m_pHitbox->SetPos(GetPos());	//�q�b�g�{�b�N�X�̈ʒu�̍X�V

		PushOut();
	}

	ClampPos();							//�ʒu�𐧌����鏈��
}

//�`�揈��
void CMovingCube::Draw(void)
{
	CPhongShading* pPhong = CApplication::GetRenderer()->GetPhongEffect();			//�V�F�[�_�[�G�t�F�N�g�̎擾����

	if (pPhong)
	{//null�`�F�b�N

		//���_���擾���āAVector4�ɕϊ�����
		D3DXVECTOR3 posV = CApplication::GetCamera()->GetPos();		
		D3DXVECTOR4 cameraPos = {};									

		cameraPos.x = posV.x;
		cameraPos.y = posV.y;
		cameraPos.z = posV.z;
		cameraPos.w = 1.0f;

		//���C�g�̕������擾���āAVector4�ɕϊ�����
		D3DXVECTOR3 l = CDirectionalLight::GetPrincipalLightDir();
		D3DXVec3Normalize(&l, &l);
		D3DXVECTOR4 light = D3DXVECTOR4(posV.x - l.x, posV.y - l.y, posV.z - l.z, 0.0f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light, (D3DXVECTOR3*)&light);

		pPhong->Begin();											//�G�t�F�N�g�̊J�n����
		pPhong->SetAmbient(0.20f);									//�����̐ݒ�
		pPhong->SetSpecular(20.0f);									//�X�y�L�����[�͈̔͂̐ݒ�
		pPhong->SetSpecularPower(1.0f);							//�X�y�L�����[�̋��x�̐ݒ�
		pPhong->SetMatrix(GetWorldMatrix(), &cameraPos, &light);	//���[���h�}�g���b�N�X�̐ݒ�
		pPhong->BeginPass();										//�p�X�̊J�n����
	}

	CModel::Draw();				//��{�N���X�̕`�揈��

	if (pPhong)
	{//null�`�F�b�N
		pPhong->EndPass();		//�p�X�̏I������
		pPhong->End();			//�V�F�[�_�[�G�t�F�N�g�̏I������
	}
}

//�ʒu�̐ݒ菈��
void CMovingCube::SetPos(const D3DXVECTOR3 pos)
{
	CModel::SetPos(pos);
}

//���̈ʒu�̐ݒ菈��
void CMovingCube::SetOriginalPos(const D3DXVECTOR3 oPos)
{
	m_OriginalPos = oPos;
}

//���x�̐ݒ菈��
void CMovingCube::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;				//���x�̐ݒ�

	//�q�b�g�{�b�N�X�̑��x�̐ݒ�
	if (m_pHitbox)
	{//null�`�F�b�N
		m_pHitbox->SetMove(m_move);
	}
}

void CMovingCube::SetMove(const D3DXVECTOR3 move, const float fRange)
{
	m_move = move;				//���x�̐ݒ�
	m_fRange = fRange;			//�ړ��̌��E�̐ݒ�

	//�q�b�g�{�b�N�X�̑��x�̐ݒ�
	if (m_pHitbox)
	{//null�`�F�b�N
		m_pHitbox->SetMove(m_move);
	}
}




//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CMovingCube* CMovingCube::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fRange)
{
	CMovingCube* pCube = new CMovingCube;			//�C���X�^���X�𐶐�����

	if (FAILED(pCube->Init()))
	{//����������

		return nullptr;
	}

	pCube->SetModel(CModel::MODEL_METAL_CUBE);			//���f���̐ݒ�
	pCube->SetPos(pos);				//�ʒu�̐ݒ�
	pCube->m_OriginalPos = pos;		//���̈ʒu�̐ݒ�
	pCube->m_size = m_metalBoxSize;	//�T�C�Y�̐ݒ�
	pCube->m_move = move;			//���x�̐ݒ�
	pCube->m_fRange = fRange;		//�ړ��̌��E�̐ݒ�

	//�q�b�g�{�b�N�X�̐���
	pCube->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, -m_metalBoxSize.y * 0.5f, 0.0f), 
		D3DXVECTOR3(m_metalBoxSize.x * 0.5f, m_metalBoxSize.y, m_metalBoxSize.z * 0.5f), CHitbox::TYPE_NEUTRAL, pCube);

	if (pCube->m_pHitbox)
	{
		pCube->m_pHitbox->SetMove(move);
	}

	return pCube;					//���������C���X�^���X��Ԃ�
}



//=============================================================================
//
//								�v���C�x�[�g�֐�
//
//=============================================================================



//�ړ��𐧌����鏈��
void CMovingCube::ClampPos(void)
{
	D3DXVECTOR3 pos = GetPos();				//�ʒu�̎擾

	//�S���̍��W���m�F���āA���E�𒴂�����A�߂��āA���x���t�ɂ���
	if (pos.x <= m_OriginalPos.x - m_fRange)
	{
		pos.x = m_OriginalPos.x - m_fRange;
		m_move.x *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.x *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}
	if (pos.y <= m_OriginalPos.y - m_fRange)
	{
		pos.y = m_OriginalPos.y - m_fRange;
		m_move.y *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.y *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}
	if (pos.z <= m_OriginalPos.z - m_fRange)
	{
		pos.z = m_OriginalPos.z - m_fRange;
		m_move.z *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.z *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}

	if (pos.x >= m_OriginalPos.x + m_fRange)
	{
		pos.x = m_OriginalPos.x + m_fRange;
		m_move.x *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.x *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}
	if (pos.y >= m_OriginalPos.y + m_fRange)
	{
		pos.y = m_OriginalPos.y + m_fRange;
		m_move.y *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.y *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}
	if (pos.z >= m_OriginalPos.z + m_fRange)
	{
		pos.z = m_OriginalPos.z + m_fRange;
		m_move.z *= -1.0f;

		if (m_pHitbox)
		{
			D3DXVECTOR3 move = m_pHitbox->GetMove();
			move.z *= -1.0f;
			m_pHitbox->SetMove(move);
		}
	}
}

//�v���C���[�̉����o������
void CMovingCube::PushOut(void)
{
	CPlayer* pPlayer = CApplication::GetGame()->GetPlayer();			//�v���C���[���̎擾

	D3DXVECTOR3 playerPos = pPlayer->GetPos();							//�v���C���[�̈ʒu�̎擾
	D3DXVECTOR3 pos = GetPos();											//�ʒu�̎擾
	D3DXVECTOR3 distance = playerPos - pos;

	if (D3DXVec3Length(&distance) <= 200.0f)
	{
		if (playerPos.x >= pos.x - m_size.x * 0.5f && playerPos.x <= pos.x + m_size.x * 0.5f &&
			playerPos.z >= pos.z - m_size.z * 0.5f && playerPos.z <= pos.z + m_size.z * 0.5f &&
			playerPos.y < pos.y + m_size.y * 0.5f && pPlayer->GetLastPos().y >= pos.y - m_move.y + m_size.y * 0.5f)
		{
			playerPos.y = pos.y + m_size.y * 0.5f;
			pPlayer->SetPos(playerPos);
			pPlayer->SetLanded();
			pPlayer->SetFriction(1.0f);
		}
	}
}
