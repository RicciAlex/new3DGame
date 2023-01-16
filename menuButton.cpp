//=============================================================================
//
// menuButton.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "menuButton.h"
#include "UIString.h"
#include "object2D.h"

#include "application.h"
#include "inputMouse.h"
#include "inputKeyboard.h"

//�R���X�g���N�^
CMenuButton::CMenuButton()
{
	//�����o�[�ϐ����N���A����
	m_pos = Vec3Null;
	m_size = Vec2Null;
	m_type = (BUTTON_TYPE)0;
	m_normalCol = ColorNull;
	m_TriggeredCol = ColorNull;
	m_bOverlap = false;

	m_pString = nullptr;
}

//�f�X�g���N�^
CMenuButton::~CMenuButton()
{

}

//����������
HRESULT CMenuButton::Init(void)
{
	//�����o�[�ϐ�������������
	m_pos = Vec3Null;
	m_size = Vec2Null;
	m_type = (BUTTON_TYPE)0;
	m_normalCol = ColorRed;
	m_TriggeredCol = ColorYellow;
	m_bOverlap = false;

	m_pString = nullptr;

	return S_OK;
}

//�I������
void CMenuButton::Uninit(void)
{
	//UI�̔z��̔j������
	if (m_pString)
	{//null�`�F�b�N

		m_pString->Release();		//���������������
		m_pString = nullptr;		//�|�C���^��null�ɂ���
	}
}

//�X�V����
void CMenuButton::Update(void)
{
	m_bOverlap = MouseOnButton();
}

//�`�揈��
void CMenuButton::Draw(void)
{

}

//�ʒu�̐ݒ菈��
void CMenuButton::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�ʒu�̎擾����
const D3DXVECTOR3 CMenuButton::GetPos(void)
{
	return m_pos;
}


//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================

//��������
CMenuButton* CMenuButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char* pString, BUTTON_TYPE type)
{
	CMenuButton* pButton = new CMenuButton;				//�C���X�^���X�𐶐�����

	if (FAILED(pButton->Init()))
	{//����������
		return nullptr;
	}

	pButton->m_pos = pos;				//�ʒu�̐ݒ�
	pButton->m_size = size;				//�T�C�Y�̐ݒ�
	pButton->m_type = type;				//��ނ̐ݒ�

	pButton->m_pString = CUIString::Create(D3DXVECTOR3(pos.x - (size.x * 0.5f), pos.y, 0.0f), size, pButton->m_normalCol, pString);		//UI�̔z��𐶐�����

	return pButton;					//���������C���X�^���X��Ԃ�
}

//��������
CMenuButton* CMenuButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, D3DXCOLOR stringCol, const char* pString, BUTTON_TYPE type)
{
	CMenuButton* pButton = new CMenuButton;				//�C���X�^���X�𐶐�����

	if (FAILED(pButton->Init()))
	{//����������
		return nullptr;
	}

	pButton->m_pos = pos;				//�ʒu�̐ݒ�
	pButton->m_size = size;				//�T�C�Y�̐ݒ�
	pButton->m_type = type;				//��ނ̐ݒ�

	pButton->m_normalCol = stringCol;	//���ʂ̐F�̐ݒ�

	pButton->m_pString = CUIString::Create(D3DXVECTOR3(pos.x - (size.x * 0.5f), pos.y, 0.0f), size, stringCol, pString);		//UI�̔z��𐶐�����

	return pButton;					//���������C���X�^���X��Ԃ�
}

//��������
CMenuButton* CMenuButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, D3DXCOLOR stringCol, D3DXCOLOR triggeredCol, const char* pString, BUTTON_TYPE type)
{
	CMenuButton* pButton = new CMenuButton;				//�C���X�^���X�𐶐�����

	if (FAILED(pButton->Init()))
	{//����������
		return nullptr;
	}

	pButton->m_pos = pos;						//�ʒu�̐ݒ�
	pButton->m_size = size;						//�T�C�Y�̐ݒ�
	pButton->m_type = type;						//��ނ̐ݒ�

	pButton->m_normalCol = stringCol;			//���ʂ̐F�̐ݒ�
	pButton->m_TriggeredCol = triggeredCol;		//�}�E�X�J�[�\���Əd�Ȃ������̂̐F�̐ݒ�

	pButton->m_pString = CUIString::Create(D3DXVECTOR3(pos.x - (size.x * 0.5f), pos.y, 0.0f), size, stringCol, pString);		//UI�̔z��𐶐�����

	return pButton;					//���������C���X�^���X��Ԃ�
}


//=============================================================================
//
//							�v���C�x�[�g�֐�
//
//=============================================================================



//�}�E�X�J�[�\�����{�^�����d�Ȃ��Ă��邩�ǂ����𔻒f����֐�
bool CMenuButton::MouseOnButton(void)
{
	//�}�E�X�J�[�\���̈ʒu�̎擾�ƕϊ�
	POINT pt;
	GetCursorPos(&pt);
	HWND wnd = CApplication::GetWindow();
	ScreenToClient(wnd, &pt);
	D3DXVECTOR3 MousePos;
	MousePos.x = (float)pt.x;
	MousePos.y = (float)pt.y;
	MousePos.z = 0.0f;

	if (MousePos.x >= m_pos.x - m_size.x * 0.5f && MousePos.x <= m_pos.x + m_size.x * 0.5f &&
		MousePos.y >= m_pos.y - m_size.y && MousePos.y <= m_pos.y + m_size.y)
	{
		if (!m_bOverlap)
		{
			if (m_pString)
			{
				m_pString->ChangeColor(m_TriggeredCol);
			}
		}

		return true;
	}
	else
	{
		if (m_bOverlap)
		{
			if (m_pString)
			{
				m_pString->ChangeColor(m_normalCol);
			}
		}
	}

	return false;
}
