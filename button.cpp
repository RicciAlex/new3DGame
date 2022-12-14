//=============================================================================
//
// button.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "button.h"
#include "CylinderHitbox.h"

//�R���X�g���N�^
CButton::CButton()
{
	//�����o�[�ϐ����N���A����
	m_originalPos = Vec3Null;
	m_normalCol = ColorNull;
	m_triggeredCol = ColorNull;
	m_bTriggered = false;
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CButton::~CButton()
{

}


//����������
HRESULT CButton::Init(void)
{
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	m_originalPos = Vec3Null;
	m_normalCol = ColorRed;
	m_triggeredCol = ColorGreen;
	m_bTriggered = false;
	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CButton::Uninit(void)
{
	if (m_pHitbox)
	{
		m_pHitbox->Release();
		m_pHitbox = false;
	}
}

//�X�V����
void CButton::Update(void)
{
	if (m_pHitbox)
	{
		if (m_pHitbox->GetCollisionState())
		{
			m_pHitbox->SetCollisionState(false);

			m_bTriggered = true;
			SetModelColor(0, m_triggeredCol);
			SetPos(m_originalPos + D3DXVECTOR3(0.0f, -9.0f, 0.0f));
		}
		else
		{
			m_bTriggered = false;
			SetModelColor(0, m_normalCol);
			SetPos(m_originalPos);
		}
	}
}

//�����ꂽ���ǂ����̎擾����
bool CButton::GetTrigger(void)
{
	return m_bTriggered;
}




//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CButton* CButton::Create(const D3DXVECTOR3 pos)
{
	CButton* pButton = new CButton;					//�C���X�^���X�𐶐�����

	if (FAILED(pButton->Init()))
	{//����������
		return nullptr;
	}

	pButton->SetPos(pos);							//�ʒu�̐ݒ�
	pButton->m_originalPos = pos;					//���̈ʒu�̐ݒ�
	pButton->SetModel(CModel::MODEL_BUTTON);		//���f���̐ݒ�
	pButton->m_normalCol = ColorRed;				//���ʂ̐F�̐ݒ�
	pButton->m_triggeredCol = ColorGreen;			//�����ꂽ��̐F�̐ݒ�
	pButton->SetShadowDraw(false);					//�e��`�悵�Ȃ��悤�ɂ���

	//�q�b�g�{�b�N�X�̐���
	pButton->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(50.0f, 10.0f, 50.0f), CHitbox::TYPE_BUTTON, pButton);
	pButton->m_pHitbox->IgnoreAllCollision();
	pButton->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);

	return pButton;									//���������C���X�^���X��Ԃ�
}	

//��������
CButton* CButton::Create(const D3DXVECTOR3 pos, const D3DXCOLOR normalCol, const D3DXCOLOR pressedCol)
{
	CButton* pButton = new CButton;					//�C���X�^���X�𐶐�����

	if (FAILED(pButton->Init()))
	{//����������
		return nullptr;
	}

	pButton->SetPos(pos);							//�ʒu�̐ݒ�
	pButton->m_originalPos = pos;					//���̈ʒu�̐ݒ�
	pButton->SetModel(CModel::MODEL_BUTTON);		//���f���̐ݒ�
	pButton->SetModelColor(0, normalCol);			//�F�̐ݒ�
	pButton->m_normalCol = normalCol;				//���ʂ̐F�̐ݒ�
	pButton->m_triggeredCol = pressedCol;			//�����ꂽ��̐F�̐ݒ�
	pButton->SetShadowDraw(false);					//�e��`�悵�Ȃ��悤�ɂ���

	//�q�b�g�{�b�N�X�̐���
	pButton->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(50.0f, 10.0f, 50.0f), CHitbox::TYPE_BUTTON, pButton);
	pButton->m_pHitbox->IgnoreAllCollision();
	pButton->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);

	return pButton;									//���������C���X�^���X��Ԃ�
}