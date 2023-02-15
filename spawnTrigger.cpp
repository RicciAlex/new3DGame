//=============================================================================
//
// spawnTrigger.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "spawnTrigger.h"


//=============================================================================
//								�ÓI�ϐ��̏�����
//=============================================================================
const D3DXVECTOR3 CSpawnTrigger::DEFAULT_POS = { 0.0f, -10000.0f, 0.0f };				//�f�B�t�H���g�̈ʒu


//�R���X�g���N�^
CSpawnTrigger::CSpawnTrigger()
{
	//�����o�[�ϐ����N���A����
	m_pos = Vec3Null;

	m_vSpawnObj.clear();
	m_vObjHeight.clear();
}

//�f�X�g���N�^
CSpawnTrigger::~CSpawnTrigger()
{

}

//����������
HRESULT CSpawnTrigger::Init(void)
{
	//�����o�[�ϐ�������������
	m_pos = Vec3Null;

	return S_OK;
}

//�I������
void CSpawnTrigger::Uninit(void)
{
	m_vSpawnObj.clear();
	m_vSpawnObj.shrink_to_fit();

	m_vObjHeight.clear();
	m_vObjHeight.shrink_to_fit();
}

//�X�V����
void CSpawnTrigger::Update(void)
{
	if (m_pTrigger)
	{
		if (m_pTrigger->GetTriggeredState())
		{
			for (int nCnt = 0; nCnt < (int)m_vSpawnObj.size(); nCnt++)
			{
				if (m_vSpawnObj.data()[nCnt])
				{
					D3DXVECTOR3 pos = m_vSpawnObj.data()[nCnt]->GetPos();
					pos.y = m_vObjHeight.data()[nCnt];

					m_vSpawnObj.data()[nCnt]->SetPos(pos);
				}
			}

			Release();
			return;
		}
	}
}

//�`�揈��
void CSpawnTrigger::Draw(void)
{

}

//�ʒu�̐ݒ菈��
void CSpawnTrigger::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�I�u�W�F�N�g�̒ǉ�����
void CSpawnTrigger::AddObject(CObject* pObj, const float fHeight)
{
	m_vSpawnObj.push_back(pObj);
	m_vObjHeight.push_back(fHeight);

	D3DXVECTOR3 pos = pObj->GetPos();
	pos.y = DEFAULT_POS.y;
	pObj->SetPos(pos);
}

//�g���K�[�̒ǉ�����
void CSpawnTrigger::AddTriggerPlatform(CTriggerablePlatform * pTrigger)
{
	m_pTrigger = pTrigger;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CSpawnTrigger::GetPos(void)
{
	return m_pos;
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CSpawnTrigger* CSpawnTrigger::Create(void)
{
	CSpawnTrigger* pSpawn = new CSpawnTrigger;			//�C���X�^���X�𐶐�����

	if (FAILED(pSpawn->Init()))
	{//����������
		return nullptr;
	}

	pSpawn->m_pos = DEFAULT_POS;	//�ʒu�̐ݒ�

	return pSpawn;					//���������C���X�^���X��Ԃ�
}

//��������
CSpawnTrigger* CSpawnTrigger::Create(const D3DXVECTOR3 pos)
{
	CSpawnTrigger* pSpawn = new CSpawnTrigger;			//�C���X�^���X�𐶐�����

	if (FAILED(pSpawn->Init()))
	{//����������
		return nullptr;
	}

	pSpawn->m_pos = pos;	//�ʒu�̐ݒ�

	return pSpawn;			//���������C���X�^���X��Ԃ�
}