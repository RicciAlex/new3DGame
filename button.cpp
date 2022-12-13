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

}

//�����ꂽ���ǂ����̎擾����
bool CButton::GetTrigger(void)
{
	return false;
}




//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CButton* CButton::Create(const D3DXVECTOR3 pos)
{
	return nullptr;
}

//��������
CButton* CButton::Create(const D3DXVECTOR3 pos, const D3DXCOLOR normalCol, const D3DXCOLOR pressedCol)
{
	return nullptr;
}