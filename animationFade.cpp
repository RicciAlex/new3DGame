//=============================================================================
//
// animationFade.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "animationFade.h"
#include "application.h"
#include "camera.h"
#include "game.h"
#include "player.h"

//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================
const float CAnimationFade::DEFAULT_FADE_SPEED = 0.05f;				//�f�B�t�H���g�̃t�F�[�h�X�s�[�h

//�f�B�t�H���g�̃A�j���[�V�����t���[����
const int   CAnimationFade::DEFAULT_ANIM_FRAMES[TYPE_MAX] =
{
	15,
	120
};

//�R���X�g���N�^
CAnimationFade::CAnimationFade()
{
	//�����o�[�ϐ����N���A����
	m_startingPos = Vec3Null;
	m_cameraPos   = Vec3Null;
	m_startingFocal = Vec3Null;
	m_focalPos = Vec3Null;
	m_nAnimFrame = 0;
	m_type = (FADE_ANIMATION_TYPE)0;
	m_phase = (FADE_PHASE)0;
}

//�f�X�g���N�^
CAnimationFade::~CAnimationFade()
{

}

//����������
HRESULT CAnimationFade::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	CCamera* pCamera = CApplication::GetCamera();

	if (!pCamera)
	{
		return -1;
	}

	//�����o�[�ϐ�������������
	m_startingPos = pCamera->GetPos();
	m_cameraPos = Vec3Null;
	m_startingFocal = pCamera->GetFocalPoint();
	m_focalPos = Vec3Null;
	m_nAnimFrame = 0;
	m_type = (FADE_ANIMATION_TYPE)0;
	m_phase = START_OUT;

	SetTexture(CObject::TEXTURE_NULL);
	SetColor(ColorNull);

	return S_OK;
}

//�I������
void CAnimationFade::Uninit(void)
{
	//��{�N���X�̏I������
	CObject_2D::Uninit();
}

//�X�V����
void CAnimationFade::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	switch (m_type)
	{
	case CAnimationFade::TYPE_NORMAL:

		NormalAnim();

		break;
	case CAnimationFade::TYPE_PLATFORM:

		PlatformAnim();

		break;

	default:
		break;
	}
}


//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CAnimationFade* CAnimationFade::Create(const D3DXVECTOR3 cameraPos, const D3DXVECTOR3 focalPoint, FADE_ANIMATION_TYPE type)
{
	CAnimationFade* pObj = new CAnimationFade;			//�C���X�^���X�𐶐�����

	if (FAILED(pObj->Init()))
	{//����������
		return nullptr;
	}

	pObj->m_cameraPos = cameraPos;				//�J�����̈ʒu�̐ݒ�
	pObj->m_focalPos = focalPoint;				//�J�����̒����_�̐ݒ�
	pObj->m_type = type;						//�A�j���[�V�����̎�ނ̐ݒ�
	pObj->SetPriority(5);						//�v���C�I���e�B�̐ݒ�

	pObj->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	pObj->SetSize(D3DXVECTOR2((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f));

	return pObj;
}


//=============================================================================
//
//							�v���C�x�[�g�֐�
//
//=============================================================================


//�t�F�[�h�A�E�g�̊֐�
bool CAnimationFade::FadeOut(void)
{
	D3DXCOLOR col = GetColor();

	col.a += DEFAULT_FADE_SPEED;

	if (col.a >= 1.0f)
	{
		col.a = 1.0f;

		m_phase = (FADE_PHASE)(m_phase + 1);

		SetColor(col);

		return true;
	}

	SetColor(col);

	return false;
}

//�t�F�[�h�C���̊֐�
bool CAnimationFade::FadeIn(void)
{
	D3DXCOLOR col = GetColor();

	col.a -= DEFAULT_FADE_SPEED;

	if (col.a <= 0.0f)
	{
		col.a = 0.0f;

		m_phase = (FADE_PHASE)(m_phase + 1);

		return true;
	}

	SetColor(col);

	return false;
}

//�v���b�g�t�H�[���A�j���[�V����
void CAnimationFade::PlatformAnim(void)
{
	CCamera* pCamera = CApplication::GetCamera();

	if (pCamera)
	{
		switch (m_phase)
		{

		case CAnimationFade::START_OUT:

		{
			if (FadeOut())
			{
				pCamera->SetPos(m_cameraPos, m_focalPos);
			}
		}

		break;

		case CAnimationFade::START_IN:

		{
			FadeIn();
		}

		break;

		case CAnimationFade::ANIM_PAUSE:

		{
			m_nAnimFrame++;

			if (m_nAnimFrame >= DEFAULT_ANIM_FRAMES[m_type])
			{
				m_nAnimFrame = 0;

				m_phase = END_OUT;
			}
		}

		break;

		case CAnimationFade::END_OUT:

		{
			if (FadeOut())
			{
				pCamera->SetPos(m_startingPos, m_startingFocal);
			}
		}

		break;

		case CAnimationFade::END_IN:

		{
			FadeIn();
		}

		break;

		case CAnimationFade::PHASE_MAX:

		{
			Release();

			CApplication::GetGame()->GetPlayer()->SetCameraAnim(false);

			return;
		}

		break;

		default:
			break;
		}
	}
}

//���ʂ̃A�j���[�V����
void CAnimationFade::NormalAnim(void)
{
	switch (m_phase)
	{

	case CAnimationFade::START_OUT:

	{
		if (FadeOut())
		{
			m_phase = ANIM_PAUSE;
		}
	}

	break;

	case CAnimationFade::ANIM_PAUSE:

	{
		m_nAnimFrame++;

		if (m_nAnimFrame >= DEFAULT_ANIM_FRAMES[m_type])
		{
			m_nAnimFrame = 0;

			m_phase = END_IN;
		}

		D3DXCOLOR col = GetColor();
	}

	break;

	case CAnimationFade::END_IN:

	{
		FadeIn();
	}

	break;

	case CAnimationFade::PHASE_MAX:

	{
		Release();
		return;
	}

	break;

	default:
		break;
	}
}
