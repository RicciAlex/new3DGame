//=============================================================================
//
// title.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "title.h"
#include "object2D.h"
#include "inputKeyboard.h"
#include "application.h"
#include "menuButton.h"
#include "AnimateUI.h"

//�R���X�g���N�^
CTitle::CTitle()
{

}

//�f�X�g���N�^
CTitle::~CTitle()
{

}

//����������
HRESULT CTitle::Init(void)
{
	CObject_2D* pObj = CObject_2D::Create();

	if (!pObj)
	{
		return -1;
	}

	pObj->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_WIDTH * 0.5f, 0.0f));
	pObj->SetSize(D3DXVECTOR2((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_WIDTH * 0.5f));
	pObj->SetColor(ColorCyan);
	pObj->SetPriority(4);

	//CUIString* pString = CUIString::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.45f, (float)SCREEN_HEIGHT * 0.3f, 0.0f), D3DXVECTOR2(200.0f, 50.0f), ColorYellow, "TITLE", 5);
	CAnimateUI::UIAnimation animInfo;
	animInfo.deltaSize = D3DXVECTOR2(0.5f, 0.25f);
	animInfo.nChangeFrame = 60;
	CAnimateUI* pLogo = CAnimateUI::Create(CObject::TEXTURE_TITLE, D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.4f, 0.0f), D3DXVECTOR2(300.0f, 150.0f), ColorWhite, animInfo);
	pLogo->AnimateColor(true);

	return S_OK;
}

//�I������
void CTitle::Uninit(void)
{

}

//�X�V����
void CTitle::Update(void)
{
	if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
	{
		CApplication::SetFade(CApplication::MODE_FIRST_STAGE);
	}
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CTitle* CTitle::Create(void)
{
	CTitle* pTitle = new CTitle;

	if (FAILED(pTitle->Init()))
	{
		return nullptr;
	}

	return pTitle;
}
