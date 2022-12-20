//=============================================================================
//
// application.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "application.h"
#include "rendering.h"
#include "debugProc.h"
#include "object2D.h"
#include "directionalLight.h"
#include "camera.h"
#include "object3D.h"
#include "model.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include "meshfield.h"
#include "player.h"
#include "animator.h"
#include "firstStage.h"
#include "fade.h"
#include "silhouette.h"
#include "title.h"
#include "results.h"
#include "BoxHitbox.h"


//�ÓI�����o�[�ϐ��̐錾
HWND CApplication::m_hWnd;													//�E�C���h�E
CRenderer* CApplication::m_pRenderer = nullptr;								//�����f�B���O�C���X�^���X�ւ̃|�C���^
CInputKeyboard* CApplication::m_pKeyboard = nullptr;						//�L�[�{�[�h�ւ̃|�C���^
//CInputMouse* CApplication::m_pMouse = nullptr;								//�}�E�X�C���X�^���X�ւ̃|�C���^
//CInputPad* CApplication::m_pPad = nullptr;									//�p�b�h�̃C���X�^���X
CSound* CApplication::m_pSound = nullptr;									//�T�E���h�̃C���X�^���X
CFade* CApplication::m_pFade = nullptr;										//�t�F�[�h�̃C���X�^���X
CCamera* CApplication::m_pCamera = nullptr;									//�J�����̃C���X�^���X
CMode* CApplication::m_pMode = nullptr;										// ���[�h�ւ̃|�C���^
//CMenu* CApplication::m_pMenu = nullptr;										// ���j���[�ւ̃|�C���^
//CMessage* CApplication::m_pMessage = nullptr;								// ���b�Z�[�W�ւ̃|�C���^
CDebugProc* CApplication::m_pDebug = nullptr;								//�f�o�b�O�\��
CApplication::Mode CApplication::m_mode = CApplication::MODE_TITLE;			//���[�h
CApplication::Mode CApplication::m_modeNext = CApplication::MODE_TITLE;		//���̃��[�h
bool CApplication::m_bPause = false;										//�|�[�Y��Ԃł��邩�ǂ���
bool CApplication::m_bFade = true;
int CApplication::m_nStageSelect = 0;										// �X�e�[�W�I��ԍ�

//�R���X�g���N�^
CApplication::CApplication()
{

}

//�f�X�g���N�^
CApplication::~CApplication()
{

}

//����������
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_hWnd = hWnd;				//�E�C���h�E�̐ݒ菈��

								//�����f�B���O�C���X�^���X�̐�������
	if (m_pRenderer == nullptr)
	{//�|�C���^��null�ł͂Ȃ�������
		m_pRenderer = new CRenderer;
	}

	//�����f�B���O�C���X�^���X�̏���������
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{//��2������FALSE��������A�t���X�N���[���ɂȂ�܂��B
		return -1;
	}

	m_pDebug = CDebugProc::Create();			//�f�o�b�O�e�L�X�g�̐�������

												//�e�N�X�`���S�������[�h����
	CObject_2D::LoadTextures();

	//���f���S�������[�h����
	CModel::LoadAllModels();

	//�S���̃A�j���[�V�����̓ǂݍ���
	CAnimator::LoadAllAnimation();

	//�T�E���h�̐���
	m_pSound = CSound::Create(hWnd);

	CLight::ReleaseAll();																						//�S���̃��C�g�̃����[�X����
	CDirectionalLight::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(2, -5, 2));						//���C�����C�g�̐���
	CDirectionalLight::Create(D3DXCOLOR(0.75f, 0.75f, 0.75f, 0.75f), D3DXVECTOR3(-0.2f, 0.2f, 1.0f));			//���C�g�̐���

	m_pCamera = CCamera::Create(D3DXVECTOR3(0.0f, 0.0f, -500.0f), D3DXVECTOR3(0.0f, -200.0f, 100.0f));			//�J�����̐���

	m_pMode = CTitle::Create();

	m_pFade = CFade::Create(0.01f);

	//�L�[�{�[�h�C���X�^���X�̐������� 
	m_pKeyboard = new CInputKeyboard;

	//�L�[�{�[�h�̏���������
	if (FAILED(m_pKeyboard->Init(hInstance, hWnd, GUID_SysKeyboard)))
	{
		return -1;
	}

	////�p�b�h�̐���
	//m_pPad = new CInputPad;

	//if (m_pPad != nullptr)
	//{//�p�b�h�̏���������
	//	m_pPad->Init(hInstance, hWnd, GUID_SysMouse);
	//}

	m_bPause = false;	//�|�[�Y�𖢎g�p�ɂ���

	m_nStageSelect = 0;	// �X�e�[�W�ԍ�������

	CSilhouette::Create();

	return S_OK;
}

//�I������
void CApplication::Uninit(void)
{
	//Renderer�C���X�^���X�̔j��
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit();			//�I������
		delete m_pRenderer;				//�j������
		m_pRenderer = nullptr;			//null�ɂ���
	}

	// ���[�h�̔j������
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();				//�I������
		delete m_pMode;					//�j������
		m_pMode = nullptr;				//null�ɂ���
	}

	//�J�����̔j������
	if (m_pCamera != nullptr)
	{
		m_pCamera->Uninit();			//�I������
		delete m_pCamera;				//�j������
		m_pCamera = nullptr;			//null�ɂ���
	}

	//�L�[�{�[�h�̔j��
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	//�L�[�{�[�h�̔j��
	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	////�p�b�h�̔j������
	//if (m_pPad != nullptr)
	//{
	//	m_pPad->Uninit();				//�I������
	//	delete m_pPad;					//�j������
	//	m_pPad = nullptr;				//null�ɂ���
	//}

	//�T�E���h�̔j������
	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();				//�I������
		delete m_pSound;				//�j������
		m_pSound = nullptr;				//null�ɂ���
	}

	//�f�o�b�O�e�L�X�g�̔j������
	if (m_pDebug != nullptr)
	{
		m_pDebug->Uninit();
		delete m_pDebug;				//�j������
		m_pDebug = nullptr;				//null�ɂ���
	}

	//�I�u�W�F�N�g�S�̂̏I������
	CObject::ReleaseAll();

	//�q�b�g�{�b�N�X�̔j������
	CHitbox::ReleaseAll();

	CMeshfield::ClearFields();

	//���C�g�̔j������
	CLight::ReleaseAll();

	//�e�N�X�`���S���̔j��
	CObject_2D::DestroyLoadedTextures();

	//�S���̃A�j���[�V�����̔j������
	CAnimator::DestroyLoadedAnimation();

	//���f���S���j���̔j������
	CModel::DestroyAllModels();
}

//�X�V����
void CApplication::Update(void)
{
	//�L�[�{�[�h�̍X�V����
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Update();
	}

	// �|�[�Y���łȂ��ꍇ�̂ݍX�V
	if (m_bPause == false)
	{
		//�J�����̍X�V����
		if (m_pCamera != nullptr)
		{
			m_pCamera->Update();
		}
	}

	//�t�F�[�h�̍X�V����
	if (m_pFade != nullptr)
	{
		//�t�F�[�h���ǂݍ��܂�Ă��Ȃ��ꍇ
		if (m_bFade)
		{
			m_pFade->Update();
		}
	}

	//Renderer�̍X�V����
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	//���݂̃��[�h�̍X�V����
	if (m_pMode != nullptr)
	{
		if (!m_bPause && !m_bFade)
		{
			m_pMode->Update();
		}
	}

	////�p�b�h�̍X�V����
	//if (m_pPad != nullptr)
	//{
	//	m_pPad->Update();
	//}
}

//�`�揈��
void CApplication::Draw(void)
{
	//Renderer�̕`�揈��
	if (m_pRenderer != nullptr)
	{//null�ł͂Ȃ�������
		m_pRenderer->Draw();
	}
}

//Renderer�̎擾����
CRenderer* CApplication::GetRenderer(void)
{
	return m_pRenderer;
}

//�E�C���h�E�̎擾����
HWND CApplication::GetWindow(void)
{
	return m_hWnd;
}

//�T�E���h�̎擾����
CSound* CApplication::GetSound(void)
{
	return m_pSound;
}

//�J�����̎擾����
CCamera* CApplication::GetCamera(void)
{
	return m_pCamera;
}

//�t�F�[�h�̎擾����
const bool CApplication::GetFade(void)
{
	return m_bFade;
}

//�t�F�[�h�̐ݒ菈��
void CApplication::SetFade(const bool bFade)
{
	m_bFade = bFade;
}

//�t�F�[�h�̐ݒ菈��
void CApplication::SetFade(CApplication::Mode mode)
{
	if (m_pFade != nullptr)
	{
		m_pFade->SetFadeOut(mode);
	}
}

// ���[�h�̎擾����
CApplication::Mode CApplication::GetMode(void)
{
	return m_mode;
}

void CApplication::SetMode(Mode mode)
{
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	CObject::ReleaseAll();
	CMeshfield::ClearFields();
	//CHitbox::ReleaseAll();

	if (m_pSound != nullptr)
	{
		m_pSound->Stop();
	}

	switch (mode)
	{
	
	case CApplication::MODE_TITLE:

	{
		m_pMode = CTitle::Create();
	}

		break;

	case CApplication::MODE_FIRST_STAGE:

	{
		m_pMode = CFirstStage::Create();

		CSilhouette::Create();
	}

		break;

	case CApplication::MODE_RESULTS:

	{
		m_pMode = CResults::Create();
	}

	break;

	default:

		break;
	}
}

//�Q�[�����[�h�̎擾����
CGame* CApplication::GetGame(void)
{
	if (m_pMode)
	{
		if (m_pMode->IsGame())
		{
			CGame* pGame = dynamic_cast<CGame*>(m_pMode);
			return pGame;
		}
	}

	return nullptr;
}



//=====================================
// �|�[�Y�擾����
//=====================================
bool CApplication::GetPause()
{
	return m_bPause;
}

//=====================================
// �|�[�Y�ݒ菈��
//=====================================
void CApplication::SetPause(const bool bPause)
{
	m_bPause = bPause;
}