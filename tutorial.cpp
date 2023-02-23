//=============================================================================
//
// tutorial.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "tutorial.h"
#include "player.h"
#include "object2D.h"
#include "UIString.h"

#include "inputKeyboard.h"
#include "application.h"
#include "camera.h"


//�R���X�g���N�^
CTutorial::CTutorial()
{
	//�����o�[�ϐ����N���A����
	m_bChangeIcon = false;

	m_pUiString = nullptr;
	m_pUiIcon[0] = nullptr;
	m_pUiIcon[1] = nullptr;
}

//�f�X�g���N�^
CTutorial::~CTutorial()
{

}

//����������
HRESULT CTutorial::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CGame::Init()))
	{
		return -1;
	}

	CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, -190.0f, 0.0f), 0);

	if (!pPlayer)
	{
		return -1;
	}

	SetPlayer(pPlayer);

	LoadMap("data\\STAGESET\\MapData\\Tutorial.txt", CObject::TEXTURE_SNOW);

	m_pUiIcon[0] = CObject_2D::Create(5, D3DXVECTOR3(150.0f, 150.0f, 0.0f), D3DXVECTOR2(87.5f, 75.0f), CObject::TEXTURE_WASD_KEY);

	if (m_pUiIcon[0])
	{
		m_pUiIcon[0]->SetTextureParameter(8, 2, 4, 30);
	}

	m_pUiIcon[1] = CObject_2D::Create(5, D3DXVECTOR3(150.0f, 300.0f, 0.0f), D3DXVECTOR2(35.0f, 70.0f), CObject::TEXTURE_PRESS_KEY);

	if (m_pUiIcon[1])
	{
		m_pUiIcon[1]->SetTextureParameter(2, 2, 5, 45);
		m_pUiIcon[1]->SetAnimationBase(4);
		m_pUiIcon[1]->SetAnimPattern(4);
	}

	/*CObject_2D* pObj = CObject_2D::Create(5, D3DXVECTOR3(950.0f, 50.0f, 0.0f), D3DXVECTOR2(35.0f, 40.0f), CObject::TEXTURE_GUIDE_ARROW);

	if (pObj)
	{
		pObj->SetTextureParameter(2, 2, 1, 20);
		pObj->SetColor(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
		pObj->SetStartingRot(D3DX_PI * 0.5f);
	}*/

	return S_OK;
}

//�I������
void CTutorial::Uninit(void)
{
	//UI�̕�����̔j������
	if (m_pUiString)
	{//null�`�F�b�N
		m_pUiString->Release();	//���������������
		m_pUiString = nullptr;	//�|�C���^��null�ɂ���
	}

	//UI�̃A�C�R���̔j������
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pUiIcon[nCnt])
		{//null�`�F�b�N
			m_pUiIcon[nCnt]->Release();		//���������������
			m_pUiIcon[nCnt] = nullptr;		//�|�C���^��null�ɂ���
		}
	}

	//��{�N���X�̏I��
	CGame::Uninit();
}

//�X�V����
void CTutorial::Update(void)
{
	//��{�N���X�̍X�V����
	CGame::Update();

	D3DXVECTOR3 cameraPos = CApplication::GetCamera()->GetPos();

	if (m_pUiIcon[1])
	{
		if (cameraPos.z >= 3500.0f && !m_bChangeIcon)
		{
			m_pUiIcon[1]->SetAnimationBase(8);
			m_pUiIcon[1]->SetAnimPattern(8);
			m_bChangeIcon = true;
		}
		else if (cameraPos.z < 3500.0f && m_bChangeIcon)
		{
			m_pUiIcon[1]->SetAnimationBase(4);
			m_pUiIcon[1]->SetAnimPattern(4);
			m_bChangeIcon = false;
		}
	}

#ifdef _DEBUG

	if (CInputKeyboard::GetKeyboardTrigger(DIK_O))
	{
		CApplication::SetMode(CApplication::MODE_TUTORIAL);
	}

#endif // _DEBUG

}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CTutorial* CTutorial::Create(void)
{
	CTutorial* pTutorial = new CTutorial;		//�C���X�^���X�𐶐�����

	if (FAILED(pTutorial->Init()))
	{//����������
		return nullptr;
	}

	return pTutorial;				//���������C���X�^���X��Ԃ�
}