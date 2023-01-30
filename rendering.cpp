//=============================================================================
//
// rendering.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "rendering.h"
#include "object.h"
#include "camera.h"
#include "application.h"
#include <stdio.h>
#include "debugProc.h"
#include "membraneLighting.h"
#include "phongShading.h"
//#include "fade.h"

//=============================================================================
//								�ÓI�ϐ��̏�����
//=============================================================================
const float CRenderer::DEFAULT_FOG_NEAR = 1500.0f;				//�t�H�O�̊J�n����
const float CRenderer::DEFAULT_FOG_FAR = 3600.0f;				//�t�H�O�̏I������
const float CRenderer::DEEP_FOG_NEAR = 300.0f;					//�t�H�O�̊J�n����(���x����)
const float CRenderer::DEEP_FOG_FAR = 600.0f;					//�t�H�O�̏I������(���x����)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRenderer::CRenderer()
{
	//�����o�[�ϐ����N���A����
	m_pD3D = nullptr;						
	m_pD3DDevice = nullptr;		
	m_pFont = nullptr;		

	m_nCntFog = 0;
	m_fFrameFog = Vec2Null;
	m_fFogNear = 0.0f;
	m_fFogFar = 0.0f;
	m_fFogTarget = 0.0f;
	m_bChangeFog = false;
	m_bActive = false;

	m_pMembrane = nullptr;
}

//=============================================================================
//�@�f�X�g���N�^
//=============================================================================
CRenderer::~CRenderer()
{

} 

//=============================================================================
// ������
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferCount = 1;										// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;							// �J���[���[�h�̎w��
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil = TRUE;							// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;					// �f�v�X�o�b�t�@�Ƃ���24bit�A�X�e���V���o�b�t�@�Ƃ���8�r�b�g���g��
	d3dpp.Windowed = bWindow;										// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��

	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if ((FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))) &&
		// ��L�̐ݒ肪���s������
		// �`��ƒ��_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice))))
	{
		// �������s
		return E_FAIL;
	}

	//�����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�t�H�O�̗L���ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);

	//�t�H�O�J���[�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, ColorWhite);

	//�t�H�O���[�h(�͈͎w��: D3DFOG_LINEAR, ���x�w��: D3DFOG_EXP)
	m_pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);

	//�͈͎w��
	float fFogStart = DEFAULT_FOG_NEAR, fFogEnd = DEFAULT_FOG_FAR;
	m_fFogNear = DEFAULT_FOG_NEAR;
	m_fFogFar = DEFAULT_FOG_FAR;
	m_fFogTarget = DEFAULT_FOG_NEAR;
	m_pD3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fFogStart));
	m_pD3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fFogEnd));

	m_pMembrane = new CMembraneShading(m_pD3DDevice);

	m_pMembrane->Load();

	m_pPhong = new CPhongShading(m_pD3DDevice);

	m_pPhong->Load();


#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
#endif

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CRenderer::Uninit()
{

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
#endif // _DEBUG

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}

	//�V�F�[�_�[�̃G�t�F�N�g�̔j������
	if (m_pMembrane)
	{
		m_pMembrane->Invalidate();
		delete m_pMembrane;
		m_pMembrane = nullptr;
	}
	if (m_pPhong)
	{
		m_pPhong->Invalidate();
		delete m_pPhong;
		m_pPhong = nullptr;
	}
}

//=============================================================================
// �X�V
//=============================================================================
void CRenderer::Update()
{
	UpdateFog();

	CObject::UpdateAll();			//�I�u�W�F�N�g�̍X�V����
}

//=============================================================================
// �`��
//=============================================================================
void CRenderer::Draw()
{
	//��ʃN���A(�X�e���V���o�b�t�@�A�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ
	 // �|���S���̕`�揈��

		CApplication::GetCamera()->Set();

		CObject::DrawAll();

		//CFade* pFade = CApplication::GetFade();
		//if (pFade != nullptr)
		//{
		//	//�t�F�[�h���ǂݍ��܂�Ă��Ȃ��ꍇ
		//	if (pFade->GetFade() != CFade::FADE_NONE)
		//	{
		//		pFade->Draw();
		//	}
		//}
#ifdef _DEBUG
		// FPS�\��
		//DrawFPS();
		CDebugProc::Draw();
		
#endif // _DEBUG

		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �f�o�C�X�̎擾����
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}

//�V�F�[�_�[�̃G�t�F�N�g�̎擾����
CMembraneShading * CRenderer::GetMembraneEffect(void)
{
	return m_pMembrane;
}

CPhongShading * CRenderer::GetPhongEffect(void)
{
	return m_pPhong;
}

void CRenderer::ChangeFog(void)
{
	m_bChangeFog = !m_bChangeFog;
	m_bActive = true;

	if (m_fFogTarget == DEFAULT_FOG_NEAR)
	{
		m_fFogTarget = DEEP_FOG_NEAR;
		m_fFrameFog.x = (DEEP_FOG_NEAR - m_fFogNear) / (float)DEFAULT_FOG_CHANGE_TIME;
		m_fFrameFog.y = (DEEP_FOG_FAR - m_fFogFar) / (float)DEFAULT_FOG_CHANGE_TIME;
	}
	else
	{
		m_fFogTarget = DEFAULT_FOG_NEAR;

		m_fFrameFog.x = (DEFAULT_FOG_NEAR - m_fFogNear) / (float)DEFAULT_FOG_CHANGE_TIME;
		m_fFrameFog.y = (DEFAULT_FOG_FAR - m_fFogFar) / (float)DEFAULT_FOG_CHANGE_TIME;
	}
}

//�t�H�O�̐ݒ菈��
void CRenderer::SetDeepFog(const bool bFog)
{
	if (m_bChangeFog != bFog)
	{
		m_bChangeFog = bFog;
		m_bActive = true;

		if (m_fFogTarget == DEFAULT_FOG_NEAR)
		{
			m_fFogTarget = DEEP_FOG_NEAR;
			m_fFrameFog.x = (DEEP_FOG_NEAR - m_fFogNear) / (float)DEFAULT_FOG_CHANGE_TIME;
			m_fFrameFog.y = (DEEP_FOG_FAR - m_fFogFar) / (float)DEFAULT_FOG_CHANGE_TIME;
		}
		else
		{
			m_fFogTarget = DEFAULT_FOG_NEAR;

			m_fFrameFog.x = (DEFAULT_FOG_NEAR - m_fFogNear) / (float)DEFAULT_FOG_CHANGE_TIME;
			m_fFrameFog.y = (DEFAULT_FOG_FAR - m_fFogFar) / (float)DEFAULT_FOG_CHANGE_TIME;
		}
	}
}

void CRenderer::UpdateFog(void)
{
	if (m_bActive)
	{
		m_nCntFog++;

		m_fFogNear += m_fFrameFog.x;
		m_fFogFar += m_fFrameFog.y;

		if (m_nCntFog >= DEFAULT_FOG_CHANGE_TIME)
		{
			if (m_fFogTarget == DEFAULT_FOG_NEAR)
			{
				m_fFogNear = DEFAULT_FOG_NEAR;
				m_fFogFar  = DEFAULT_FOG_FAR;
			}
			else
			{
				m_fFogNear = DEEP_FOG_NEAR;
				m_fFogFar  = DEEP_FOG_FAR;
			}

			m_nCntFog = 0;
			m_bActive = false;
		}

		m_pD3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&m_fFogNear));
		m_pD3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&m_fFogFar));
	}
}

#ifdef _DEBUG

//=============================================================================
// FPS�\��
//=============================================================================
void CRenderer::DrawFPS(void)
{
	int fps = GetFPS();
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	TCHAR str[256];

	sprintf(str, _T("FPS : %d\n\n \n"), fps);

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

#endif // _DEBUG