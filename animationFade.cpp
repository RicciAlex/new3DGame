//=============================================================================
//
// animationFade.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "animationFade.h"
#include "application.h"
#include "camera.h"
#include "game.h"
#include "player.h"

//=============================================================================
//							静的変数の初期化
//=============================================================================
const float CAnimationFade::DEFAULT_FADE_SPEED = 0.05f;				//ディフォルトのフェードスピード

//ディフォルトのアニメーションフレーム数
const int   CAnimationFade::DEFAULT_ANIM_FRAMES[TYPE_MAX] =
{
	15,
	120
};

//コンストラクタ
CAnimationFade::CAnimationFade()
{
	//メンバー変数をクリアする
	m_startingPos = Vec3Null;
	m_cameraPos   = Vec3Null;
	m_startingFocal = Vec3Null;
	m_focalPos = Vec3Null;
	m_nAnimFrame = 0;
	m_type = (FADE_ANIMATION_TYPE)0;
	m_phase = (FADE_PHASE)0;
}

//デストラクタ
CAnimationFade::~CAnimationFade()
{

}

//初期化処理
HRESULT CAnimationFade::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	CCamera* pCamera = CApplication::GetCamera();

	if (!pCamera)
	{
		return -1;
	}

	//メンバー変数を初期化する
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

//終了処理
void CAnimationFade::Uninit(void)
{
	//基本クラスの終了処理
	CObject_2D::Uninit();
}

//更新処理
void CAnimationFade::Update(void)
{
	//基本クラスの更新処理
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
//								静的関数
//
//=============================================================================



//生成処理
CAnimationFade* CAnimationFade::Create(const D3DXVECTOR3 cameraPos, const D3DXVECTOR3 focalPoint, FADE_ANIMATION_TYPE type)
{
	CAnimationFade* pObj = new CAnimationFade;			//インスタンスを生成する

	if (FAILED(pObj->Init()))
	{//初期化処理
		return nullptr;
	}

	pObj->m_cameraPos = cameraPos;				//カメラの位置の設定
	pObj->m_focalPos = focalPoint;				//カメラの注視点の設定
	pObj->m_type = type;						//アニメーションの種類の設定
	pObj->SetPriority(5);						//プライオリティの設定

	pObj->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	pObj->SetSize(D3DXVECTOR2((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f));

	return pObj;
}


//=============================================================================
//
//							プライベート関数
//
//=============================================================================


//フェードアウトの関数
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

//フェードインの関数
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

//プラットフォームアニメーション
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

//普通のアニメーション
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
