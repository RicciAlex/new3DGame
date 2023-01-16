//=============================================================================
//
// checkpoint.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "checkpoint.h"
#include "model.h"
#include "application.h"
#include "game.h"
#include "player.h"

//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================
const float			CCheckpoint::ANIMATION_AMPLITUDE = 0.005f;
const float			CCheckpoint::DEFAULT_RANGE = 300.0f;				//�f�B�t�H���g�̔��a
const D3DXCOLOR		CCheckpoint::DEFAULT_NORMAL_COLOR = D3DXCOLOR(1.0f, 0.5f, 0.1f, 0.5f);		//�f�B�t�H���g�̕��ʂ̐F
const D3DXCOLOR		CCheckpoint::DEFAULT_ACTIVE_COLOR = D3DXCOLOR(0.1f, 1.0f, 0.1f, 0.5f);		//�f�B�t�H���g�̃A�N�e�B�u�̐F
bool				CCheckpoint::m_bChange = false;
bool				CCheckpoint::m_bFirst = true;

//�R���X�g���N�^
CCheckpoint::CCheckpoint()
{
	//�����o�[�ϐ����N���A����
	m_pos = Vec3Null;
	m_fRange = 0.0f;
	m_normalCol = ColorNull;
	m_activeCol = ColorNull;
	m_nScaleAnimCnt = 0;
	m_fScaleAnim = 0.0f;
	m_bActive = false;

	m_pFlag = nullptr;
	m_pAura = nullptr;
}

//�f�X�g���N�^
CCheckpoint::~CCheckpoint()
{

}

//����������
HRESULT CCheckpoint::Init(void)
{
	//�����o�[�ϐ�������������
	m_pos = Vec3Null;
	m_fRange = DEFAULT_RANGE;
	m_normalCol = DEFAULT_NORMAL_COLOR;
	m_activeCol = DEFAULT_ACTIVE_COLOR;
	m_nScaleAnimCnt = 0;
	m_fScaleAnim = ANIMATION_AMPLITUDE;
	m_bActive = false;

	m_pFlag = nullptr;
	m_pAura = nullptr;

	return S_OK;
}

//�I������
void CCheckpoint::Uninit(void)
{
	//���f���̔j������
	if (m_pFlag)
	{//null�`�F�b�N
		m_pFlag->Release();			//���������������
		m_pFlag = nullptr;			//�|�C���^��null�ɂ���
	}
	if (m_pAura)
	{//null�`�F�b�N
		m_pAura->Release();			//���������������
		m_pAura = nullptr;			//�|�C���^��null�ɂ���
	}
}

//�X�V����
void CCheckpoint::Update(void)
{
	if (!m_bActive)
	{
		CPlayer* pPlayer = CApplication::GetGame()->GetPlayer();

		if (pPlayer)
		{
			D3DXVECTOR3 distance = pPlayer->GetPos() - m_pos;			//�������v�Z����

			if (D3DXVec3Length(&distance) <= m_fRange)
			{
				if (m_pAura)
				{
					m_pAura->SetModelColor(0, m_activeCol);
				}

				m_bActive = true;

				if (!m_bFirst)
				{
					m_bChange = true;
				}
				else
				{
					m_bFirst = false;
				}

				pPlayer->SetRespawnPoint(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z - 50.0f));
			}
		}
	}
	else
	{
		if (m_bChange)
		{
			if (m_pAura)
			{
				m_pAura->SetModelColor(0, m_normalCol);
			}

			m_bActive = false;
			m_bChange = false;
		}
	}

	if (m_pAura)
	{
		float fScale = m_pAura->GetScale();

		m_nScaleAnimCnt++;

		if (m_nScaleAnimCnt >= ANIMATION_FRAMES)
		{
			m_nScaleAnimCnt = 0;

			m_fScaleAnim *= -1.0f;
		}

		fScale += m_fScaleAnim;

		m_pAura->SetScale(fScale);
	}
}

//�`�揈��
void CCheckpoint::Draw(void)
{

}

//�ʒu�̐ݒ菈��
void CCheckpoint::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CCheckpoint::GetPos(void)
{
	return m_pos;
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CCheckpoint* CCheckpoint::Create(const D3DXVECTOR3 pos)
{
	CCheckpoint* pPoint = new CCheckpoint;			//�C���X�^���X�𐶐�����

	if (FAILED(pPoint->Init()))
	{//����������
		return nullptr;
	}

	pPoint->m_pos = pos;			//�ʒu�̐ݒ�

	pPoint->m_pFlag = CModel::Create(CModel::MODEL_FLAG, pos);			//�`�F�b�N�|�C���g�̃t���O���f���̐���

	if (pPoint->m_pFlag)
	{//�����o������A�e��`�悵�Ȃ��悤�ɂ���
		pPoint->m_pFlag->SetShadowDraw(false);
		pPoint->m_pFlag->SetModelColor(1, ColorGreen);
	}

	pPoint->m_pAura = CModel::Create(CModel::MODEL_CHECKPOINT_AURA, pos);		//�`�F�b�N�|�C���g�̃I�[�����f���̐���

	if (pPoint->m_pAura)
	{
		pPoint->m_pAura->SetScale(3.0f);
		pPoint->m_pAura->SetShadowDraw(false);
	}

	return pPoint;			//���������C���X�^���X��Ԃ�
}

//��������
CCheckpoint* CCheckpoint::Create(const D3DXVECTOR3 pos, const float fRange)
{
	CCheckpoint* pPoint = new CCheckpoint;			//�C���X�^���X�𐶐�����

	if (FAILED(pPoint->Init()))
	{//����������
		return nullptr;
	}

	pPoint->m_pos = pos;					//�ʒu�̐ݒ�
	pPoint->m_fRange = fRange;				//���a�̐ݒ�

	pPoint->m_pFlag = CModel::Create(CModel::MODEL_FLAG, pos);			//�`�F�b�N�|�C���g�̃t���O���f���̐���

	if (pPoint->m_pFlag)
	{//�����o������A�e��`�悵�Ȃ��悤�ɂ���
		pPoint->m_pFlag->SetShadowDraw(false);
		pPoint->m_pFlag->SetModelColor(1, ColorGreen);
	}

	pPoint->m_pAura = CModel::Create(CModel::MODEL_CHECKPOINT_AURA, pos);		//�`�F�b�N�|�C���g�̃I�[�����f���̐���

	if (pPoint->m_pAura)
	{
		pPoint->m_pAura->SetScale(3.0f);
		pPoint->m_pAura->SetShadowDraw(false);
	}

	return pPoint;			//���������C���X�^���X��Ԃ�
}

//��������
CCheckpoint* CCheckpoint::Create(const D3DXVECTOR3 pos, const float fRange, const D3DXCOLOR normalCol)
{
	CCheckpoint* pPoint = new CCheckpoint;			//�C���X�^���X�𐶐�����

	if (FAILED(pPoint->Init()))
	{//����������
		return nullptr;
	}

	pPoint->m_pos = pos;					//�ʒu�̐ݒ�
	pPoint->m_fRange = fRange;				//���a�̐ݒ�
	pPoint->m_normalCol = normalCol;		//���ʂ̐F�̐ݒ�

	pPoint->m_pFlag = CModel::Create(CModel::MODEL_FLAG, pos);			//�`�F�b�N�|�C���g�̃t���O���f���̐���

	if (pPoint->m_pFlag)
	{//�����o������A�e��`�悵�Ȃ��悤�ɂ���
		pPoint->m_pFlag->SetShadowDraw(false);
		pPoint->m_pFlag->SetModelColor(1, ColorGreen);
	}

	pPoint->m_pAura = CModel::Create(CModel::MODEL_CHECKPOINT_AURA, pos);		//�`�F�b�N�|�C���g�̃I�[�����f���̐���

	if (pPoint->m_pFlag)
	{//�����o������A�F��ݒ肷��
		pPoint->m_pAura->SetModelColor(0, normalCol);
		pPoint->m_pAura->SetScale(3.0f);
		pPoint->m_pAura->SetShadowDraw(false);
	}

	return pPoint;			//���������C���X�^���X��Ԃ�
}

//��������
CCheckpoint* CCheckpoint::Create(const D3DXVECTOR3 pos, const float fRange, const D3DXCOLOR normalCol, const D3DXCOLOR activeCol)
{
	CCheckpoint* pPoint = new CCheckpoint;			//�C���X�^���X�𐶐�����

	if (FAILED(pPoint->Init()))
	{//����������
		return nullptr;
	}

	pPoint->m_pos = pos;					//�ʒu�̐ݒ�
	pPoint->m_fRange = fRange;				//���a�̐ݒ�
	pPoint->m_normalCol = normalCol;		//���ʂ̐F�̐ݒ�
	pPoint->m_activeCol = activeCol;		//�A�N�e�B�u�̐F�̐ݒ�

	pPoint->m_pFlag = CModel::Create(CModel::MODEL_FLAG, pos);			//�`�F�b�N�|�C���g�̃t���O���f���̐���

	if (pPoint->m_pFlag)
	{//�����o������A�e��`�悵�Ȃ��悤�ɂ���
		pPoint->m_pFlag->SetShadowDraw(false);
		pPoint->m_pFlag->SetModelColor(1, ColorGreen);
	}

	pPoint->m_pAura = CModel::Create(CModel::MODEL_CHECKPOINT_AURA, pos);		//�`�F�b�N�|�C���g�̃I�[�����f���̐���

	if (pPoint->m_pFlag)
	{//�����o������A�F��ݒ肷��
		pPoint->m_pAura->SetModelColor(0, normalCol);
		pPoint->m_pAura->SetScale(3.0f);
		pPoint->m_pAura->SetShadowDraw(false);
	}

	return pPoint;			//���������C���X�^���X��Ԃ�
}