//=============================================================================
//
// PauseMenu.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "PauseMenu.h"
#include "menuButton.h"
#include "application.h"


//=============================================================================
//								�ÓI�ϐ��̏�����
//=============================================================================
const D3DXVECTOR3 CPauseMenu::DEFAULT_MENU_POS = { (float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f };		//�f�B�t�H���g�̃��j���[�̈ʒu
const D3DXVECTOR2 CPauseMenu::DEFAULT_MENU_SIZE = { 200.0f, 200.0f };				//�f�B�t�H���g�̃��j���[�̃T�C�Y
const D3DXVECTOR2 CPauseMenu::DEFAULT_BUTTON_SIZE = { 300.0f, 100.0f};			//�f�B�t�H���g�̃{�^���̃T�C�Y
const float		  CPauseMenu::DEFAULT_BUTTON_DISTANCE = 100.0f;		//�{�^���̊Ԃ̋���
const char		  CPauseMenu::BUTTON_STRING[CPauseMenu::TYPE_MAX][48] = 
{
	"CONTINUE",
	"QUIT"
};		//�{�^���̕�����


//�R���X�g���N�^
CPauseMenu::CPauseMenu()
{
	m_bActive = false;

	for (int nCnt = 0; nCnt < CPauseMenu::TYPE_MAX; nCnt++)
	{
		m_buttonRelativePos[nCnt] = Vec3Null;

		m_pButton[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CPauseMenu::~CPauseMenu()
{

}

//����������
HRESULT CPauseMenu::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CMenu::Init()))
	{
		return -1;
	}

	CreateBg(DEFAULT_MENU_POS, DEFAULT_MENU_SIZE, CObject::TEXTURE_BLOCK);

	return S_OK;
}

//�I������
void CPauseMenu::Uninit(void)
{
	//�{�^���̔j������
	for (int nCnt = 0; nCnt < CPauseMenu::TYPE_MAX; nCnt++)
	{
		if (m_pButton[nCnt])
		{
			m_pButton[nCnt]->Release();		//���������������
			m_pButton[nCnt] = nullptr;		//�|�C���^��null�ɂ���
		}
	}

	//��{�N���X�̏I������
	CMenu::Uninit();
}

//�X�V����
void CPauseMenu::Update(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_pButton[nCnt])
		{
			m_pButton[nCnt]->Update();

			if (m_pButton[nCnt]->GetTriggerState())
			{
				SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, 5000.0f, 0.0f));			//��ʊO�Ɉړ�����
				m_bActive = false;
				CApplication::SetPause(false);

				switch (nCnt)
				{
				case CPauseMenu::TYPE_CONTINUE:

				{

				}

				break;

				case CPauseMenu::TYPE_QUIT:

				{
					CApplication::SetFade(CApplication::MODE_TITLE);
				}

				break;

				default:
					break;
				}
			}
		}

		//��{�N���X�̍X�V����
		CMenu::Update();
	}
}

//�`�揈��
void CPauseMenu::Draw(void)
{
	//��{�N���X�̕`�揈��
	CMenu::Draw();
}

//�ʒu�̐ݒ菈��
void CPauseMenu::SetPos(const D3DXVECTOR3 pos)
{
	//��{�N���X�̈ʒu�̐ݒ菈��
	CMenu::SetPos(pos);

	//�{�^���̈ʒu�̐ݒ�
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_pButton[nCnt])
		{
			m_pButton[nCnt]->SetPos(pos + m_buttonRelativePos[nCnt]);
		}
	}
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CPauseMenu * CPauseMenu::Create(void)
{
	CPauseMenu* pMenu = new CPauseMenu;			//�C���X�^���X�𐶐�����

	//����������
	if (FAILED(pMenu->Init()))
	{
		return nullptr;
	}

	pMenu->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, 5000.0f, 0.0f));		//�ʒu�̐ݒ�
	pMenu->CreateButton();					//�{�^���̐�������

	return pMenu;					//���������C���X�^���X��Ԃ�
}

//�{�^���̐�������
void CPauseMenu::CreateButton(void)
{
	for (int nCnt = 0; nCnt < CPauseMenu::TYPE_MAX; nCnt++)
	{
		D3DXVECTOR3 pos = GetPos();
		pos.y += (-DEFAULT_BUTTON_DISTANCE * (TYPE_MAX * 0.5f)) + (DEFAULT_BUTTON_DISTANCE * nCnt * 2.0f);

		m_buttonRelativePos[nCnt] = pos - GetPos();

		m_pButton[nCnt] = CMenuButton::Create(pos, DEFAULT_BUTTON_SIZE, BUTTON_STRING[nCnt]);
	}
}
