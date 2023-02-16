//=============================================================================
//
// iceWall.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "iceWall.h"
#include "modelPart.h"
#include "BoxHitbox.h"


//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================

const D3DXVECTOR3 CIceWall::HITBOX_SIZE = { 100.0f, 325.0f, 50.0f };		//�f�B�t�H���g�̃T�C�Y

const D3DXVECTOR3 CIceWall::RELATIVE_PARTS_POS[CIceWall::PART_NUMBER] =
{
	{ -41.0f,  50.0f, 0.0f },
	{  39.0f,  40.0f, 0.0f },
	{  39.0f, 160.0f, 0.0f },
	{ -40.0f, 159.0f, 0.0f },
	{   0.0f, 267.0f, 0.0f }
};	//�p�[�c�̑��Έʒu


//�R���X�g���N�^
CIceWall::CIceWall()
{
	//�����o�[�ϐ����N���A����
	m_pos = Vec3Null;
	m_rot = Vec3Null;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nCntDeath = 0;
	m_bBroken = false;
	
	for (int nCnt = 0; nCnt < CIceWall::PART_NUMBER; nCnt++)
	{
		m_move[nCnt] = Vec3Null;
		m_partsRot[nCnt] = Vec3Null;
		m_pPart[nCnt] = nullptr;
	}

	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CIceWall::~CIceWall()
{

}

//����������
HRESULT CIceWall::Init(void)
{
	//�����o�[�ϐ�������������
	m_nCntDeath = 90;

	return S_OK;
}

//�I������
void CIceWall::Uninit(void)
{
	for (int nCnt = 0; nCnt < CIceWall::PART_NUMBER; nCnt++)
	{
		if (m_pPart[nCnt])
		{
			m_pPart[nCnt]->Uninit();
			delete m_pPart[nCnt];
			m_pPart[nCnt] = nullptr;
		}
	}

	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox)
	{//null�`�F�b�N

		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//�|�C���^��null�ɂ���
	}
}

//�X�V����
void CIceWall::Update(void)
{
	if (!m_bBroken)
	{
		if (m_pHitbox)
		{
			m_pHitbox->Update();

			if (m_pHitbox->GetEffect() == CHitbox::EFFECT_DAMAGE)
			{
				m_pHitbox->Release();
				m_pHitbox = nullptr;

				m_bBroken = true;
			}
		}
	}
	else
	{
		m_nCntDeath--;

		if (m_nCntDeath <= 0)
		{
			Release();
			return;
		}

		for (int nCnt = 0; nCnt < CIceWall::PART_NUMBER; nCnt++)
		{
			m_move[nCnt].y += -0.8f;

			if (m_pPart[nCnt])
			{
				m_pPart[nCnt]->SetPos(m_pPart[nCnt]->GetPos() + m_move[nCnt]);
				m_pPart[nCnt]->SetRot(m_pPart[nCnt]->GetRot() + m_partsRot[nCnt]);
			}
		}
	}
}

//�`�揈��
void CIceWall::Draw(void)
{
	D3DXMATRIX mtxTrans, mtxRot;		//�v�Z�p�̃}�g���b�N�X

	D3DXMatrixIdentity(&m_mtxWorld);	//�}�g���b�N�X�̏�����

	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	for (int nCnt = 0; nCnt < CIceWall::PART_NUMBER; nCnt++)
	{
		if (m_pPart[nCnt])
		{
			m_pPart[nCnt]->Draw(m_mtxWorld);
		}
	}
}

//�ʒu�̐ݒ菈��
void CIceWall::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CIceWall::GetPos(void)
{
	return m_pos;
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================




//��������
CIceWall* CIceWall::Create(const D3DXVECTOR3 pos, const bool bRotate)
{
	CIceWall* pWall = new CIceWall;			//�C���X�^���X�𐶐�����

	if (FAILED(pWall->Init()))
	{//����������
		return nullptr;
	}

	pWall->m_pos = pos;									//�ʒu�̐ݒ�
	pWall->m_rot = Vec3Null;

	D3DXVECTOR3 size = HITBOX_SIZE;						//�T�C�Y�̐ݒ�

	if (bRotate)
	{
		pWall->m_rot = D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f);		//��]�p�x�̐ݒ�
		size = D3DXVECTOR3(HITBOX_SIZE.z, HITBOX_SIZE.y, HITBOX_SIZE.x);	//�T�C�Y�̒���
	}

	for (int nCnt = 0; nCnt < CIceWall::PART_NUMBER; nCnt++)
	{
		pWall->m_pPart[nCnt] = CModelPart::Create((CModel::ModelType)((int)CModel::MODEL_ICE_FRAGMENT_1 + nCnt), RELATIVE_PARTS_POS[nCnt], Vec3Null);
	
		if (pWall->m_pPart[nCnt])
		{
			pWall->m_pPart[nCnt]->SetShadowHeight(-5000.0f);
		}
	}

	pWall->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, size, CHitbox::TYPE_NEUTRAL, pWall);

	if (pWall->m_pHitbox)
	{
		pWall->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_OBSTACLE, CHitbox::RESPONSE_OVERLAP);
	}

	pWall->SetMove();

	return pWall;				//���������C���X�^���X��Ԃ�
}



//=============================================================================
//
//								�v���C�x�[�g�֐�
//
//=============================================================================



//���x�̐ݒ菈��
void CIceWall::SetMove(void)
{
	D3DXMATRIX mtxRot;

	D3DXMatrixIdentity(&mtxRot);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	m_move[0] = D3DXVECTOR3(random(-500, -100) * 0.01f, random(100, 500) * 0.01f, 0.0f);
	m_move[1] = D3DXVECTOR3(random( 100,  500) * 0.01f, random(100, 500) * 0.01f, 0.0f);
	m_move[2] = D3DXVECTOR3(random( 100,  500) * 0.01f, random(200, 600) * 0.01f, 0.0f);
	m_move[3] = D3DXVECTOR3(random(-500, -100) * 0.01f, random(200, 600) * 0.01f, 0.0f);
	m_move[4] = D3DXVECTOR3(random(-500,  500) * 0.01f, random(300, 650) * 0.01f, 0.0f);

	for (int nCnt = 0; nCnt < CIceWall::PART_NUMBER; nCnt++)
	{
		D3DXVec3TransformCoord(&m_move[nCnt], &m_move[nCnt], &mtxRot);

		m_partsRot[nCnt] = D3DXVECTOR3(0.0f, random(-100, 100) * D3DX_PI * 0.001f, random(-100, 100) * D3DX_PI * 0.001f);
		D3DXVec3TransformCoord(&m_partsRot[nCnt], &m_partsRot[nCnt], &mtxRot);
	}
}
