//=============================================================================
//
// ShurikenTrap.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "ShurikenTrap.h"
#include "shuriken.h"
#include "button.h"
#include "CylinderHitbox.h"

//�R���X�g���N�^
CShurikenTrap::CShurikenTrap()
{
	//�����o�[�ϐ����N���A����
	m_spawnPos = Vec3Null;
	m_rot = Vec3Null;
	m_nDelay = 0;

	m_pButton = nullptr;
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CShurikenTrap::~CShurikenTrap()
{

}

//����������
HRESULT CShurikenTrap::Init(void)
{
	//�����o�[�ϐ�������������
	m_spawnPos = Vec3Null;
	m_rot = Vec3Null;
	m_nDelay = 60;

	m_pButton = nullptr;
	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CShurikenTrap::Uninit(void)
{
	//�{�^���̔j������
	if (m_pButton)
	{//null�`�F�b�N
		m_pButton->Release();		//���������������
		m_pButton = nullptr;		//�|�C���^��null�ɂ���
	}

	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox)
	{//null�`�F�b�N
		m_pHitbox->Release();		//���������������
		m_pHitbox = nullptr;		//�|�C���^��null�ɂ���
	}
}

//�X�V����
void CShurikenTrap::Update(void)
{
	if (m_nDelay > 0)
	{
		m_nDelay--;
	}

	if (m_pButton)
	{
		if (m_pButton->GetTrigger())
		{
			if (m_nDelay <= 0)
			{
				D3DXVECTOR3 speed = m_pButton->GetPos() - m_spawnPos;
				speed.y = 0.0f;
				D3DXVec3Normalize(&speed, &speed);
				speed.x *= 10.0f;
				speed.z *= 10.0f;

				CShuriken::Create(m_spawnPos, speed);

				m_nDelay = 15;
			}
		}
	}
}

//�`�揈��
void CShurikenTrap::Draw(void)
{

}

//�ʒu�̐ݒ菈��
void CShurikenTrap::SetPos(const D3DXVECTOR3 pos)
{
	
}

//�ʒu�̎擾����
const D3DXVECTOR3 CShurikenTrap::GetPos(void)
{
	return Vec3Null;
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================


//��������
CShurikenTrap* CShurikenTrap::Create(const D3DXVECTOR3 pos, const float Yrot, const float fDistance)
{
	CShurikenTrap* pTrap = new CShurikenTrap;

	if (FAILED(pTrap->Init()))
	{
		return nullptr;
	}

	pTrap->m_pButton = CButton::Create(pos);

	if (!pTrap->m_pButton)
	{
		return nullptr;
	}

	D3DXVECTOR3 sPos = Vec3Null, unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXMATRIX mtxOut, mtxRot;

	D3DXMatrixIdentity(&mtxOut);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Yrot, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxRot);

	D3DXVec3TransformCoord(&unit, &unit, &mtxOut);
	unit.x *= fDistance;
	unit.z *= fDistance;

	CModel* pModel = CModel::Create(CModel::MODEL_TRAP_PILLAR, pos + unit);
	pModel->SetRot(D3DXVECTOR3(0.0f, -Yrot, 0.0f));
	pModel->SetScale(1.5f);

	pTrap->m_pHitbox = CCylinderHitbox::Create(pos + unit, Vec3Null, D3DXVECTOR3(15.0f, 130.0f, 15.0f), CHitbox::TYPE_NEUTRAL, pTrap);

	unit.y += 100.0f;

	pTrap->m_spawnPos = pos + unit;

	return pTrap;
}

//��������
CShurikenTrap* CShurikenTrap::Create(const D3DXVECTOR3 pos, const float Yrot, const float fDistance,
								     const D3DXCOLOR buttonCol, const D3DXCOLOR triggeredCol)
{
	CShurikenTrap* pTrap = new CShurikenTrap;

	if (FAILED(pTrap->Init()))
	{
		return nullptr;
	}

	pTrap->m_pButton = CButton::Create(pos, buttonCol, triggeredCol);

	if (!pTrap->m_pButton)
	{
		return nullptr;
	}

	D3DXVECTOR3 sPos = Vec3Null, unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXMATRIX mtxOut, mtxRot;

	D3DXMatrixIdentity(&mtxOut);
	D3DXMatrixRotationYawPitchRoll(&mtxRot, Yrot, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtxOut, &mtxOut, &mtxRot);

	D3DXVec3TransformCoord(&unit, &unit, &mtxOut);
	unit.x *= fDistance;
	unit.z *= fDistance;

	CModel* pModel = CModel::Create(CModel::MODEL_TRAP_PILLAR, pos);
	pModel->SetRot(D3DXVECTOR3(0.0f, -Yrot, 0.0f));

	pTrap->m_pHitbox = CCylinderHitbox::Create(pos + unit, Vec3Null, D3DXVECTOR3(15.0f, 130.0f, 15.0f), CHitbox::TYPE_NEUTRAL, pTrap);

	unit.y += 100.0f;

	pTrap->m_spawnPos = pos + unit;

	return pTrap;
}