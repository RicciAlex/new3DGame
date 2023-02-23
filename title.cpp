//=============================================================================
//
// title.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "title.h"
#include "object2D.h"
#include "inputKeyboard.h"
#include "application.h"
#include "menuButton.h"
#include "AnimateUI.h"
#include "camera.h"
#include "model.h"
#include "meshfield.h"
#include "rendering.h"
#include "billboard.h"
#include "gem.h"
#include "nail.h"
#include "spikeTrap.h"
#include "fireParticle.h"
#include "checkpoint.h"
#include "iceWall.h"
#include "fallBoard.h"
#include "movingCube.h"
#include "star.h"
#include "animationFade.h"
#include "UIString.h"
#include "accelerationFloor.h"


//=============================================================================
//								静的変数の初期化
//=============================================================================
const D3DXVECTOR3 CTitle::FOCAL_POINT_RELATIVE_POS = { { 0.0f,  -500.0f, 750.0f } };		//注視点の相対位置
const D3DXVECTOR3 CTitle::BG_RELATIVE_POS = { 0.0f, 0.0f, 2500.0f };		//背景の相対位置
const D3DXVECTOR3 CTitle::START_POS[2] = { { 0.0f, 500.0f, -750.0f }, { { 10000.0f, 500.0f, -750.0f } } };			//開始の位置
const D3DXVECTOR3 CTitle::END_POS[2]   = { { 0.0f, 500.0f, 2900.0f }, { { 10000.0f, 500.0f, 2900.0f } } };			//終了の位置


//コンストラクタ
CTitle::CTitle()
{
	//メンバー変数をクリアする
	m_nPresentCourse = 0;
	m_bChange = false;

	m_pBg = nullptr;
}

//デストラクタ
CTitle::~CTitle()
{

}

//初期化処理
HRESULT CTitle::Init(void)
{
	/*CObject_2D* pObj = CObject_2D::Create();

	if (!pObj)
	{
		return -1;
	}
*/
	CCamera* pCamera = CApplication::GetCamera();

	if (pCamera)
	{
		pCamera->SetPos(START_POS[m_nPresentCourse], START_POS[m_nPresentCourse] + FOCAL_POINT_RELATIVE_POS);
	}

	/*pObj->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_WIDTH * 0.5f, 0.0f));
	pObj->SetSize(D3DXVECTOR2((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_WIDTH * 0.5f));
	pObj->SetColor(ColorCyan);
	pObj->SetPriority(4);*/

	m_pBg = CBillboard::Create(START_POS[m_nPresentCourse] + BG_RELATIVE_POS, D3DXVECTOR2(5000.0f, 5000.0f));

	if (m_pBg)
	{
		m_pBg->SetColor(ColorCyan);
	}

	//CUIString* pString = CUIString::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.45f, (float)SCREEN_HEIGHT * 0.3f, 0.0f), D3DXVECTOR2(200.0f, 50.0f), ColorYellow, "TITLE", 5);
	CAnimateUI::UIAnimation animInfo;
	animInfo.deltaSize = D3DXVECTOR2(0.5f, 0.25f);
	animInfo.nChangeFrame = 60;
	CAnimateUI* pLogo = CAnimateUI::Create(CObject::TEXTURE_TITLE, D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.25f, 0.0f), D3DXVECTOR2(300.0f, 150.0f), ColorWhite, animInfo);
	pLogo->AnimateColor(true);

	CApplication::GetRenderer()->SetDeepFog(false);

	SetMap();

	animInfo.nChangeFrame = 45;

	CAnimateUI::Create(CObject::TEXTURE_PRESS_ENTER, D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.8f, 0.0f),
		D3DXVECTOR2(235.0f, 36.0f), ColorWhite, animInfo);

	CObject_2D* pObj = CObject_2D::Create(3, D3DXVECTOR3((float)SCREEN_WIDTH - 100.0f, (float)SCREEN_HEIGHT - 100.0f, 0.0f),
		D3DXVECTOR2(50.0f, 100.0f), CObject::TEXTURE_SPACE_KEY);

	if (pObj)
	{
		pObj->SetTextureParameter(2, 2, 2, 30);
	}

	return S_OK;
}

//終了処理
void CTitle::Uninit(void)
{
	//背景の破棄処理
	if (m_pBg)
	{//nullチェック
		m_pBg->Release();		//メモリを解放する
		m_pBg = nullptr;		//ポインタをnullにする
	}
}

//更新処理
void CTitle::Update(void)
{
	if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
	{
		CApplication::SetFade(CApplication::MODE_STAGE_SELECT);
	}

	if (CInputKeyboard::GetKeyboardTrigger(DIK_SPACE))
	{
		CApplication::SetFade(CApplication::MODE_RANKING);
	}

	CCamera* pCamera = CApplication::GetCamera();

	if (pCamera)
	{
		D3DXVECTOR3 pos = pCamera->GetPos();

		pos.z += 5.0f;

		if (pos.z >= END_POS[m_nPresentCourse].z - 150.0f && !m_bChange)
		{
			m_bChange = true;
			CAnimationFade::Create(pos, pos + FOCAL_POINT_RELATIVE_POS, CAnimationFade::TYPE_NORMAL);
		}

		if (pos.z >= END_POS[m_nPresentCourse].z)
		{
			m_bChange = false;
			m_nPresentCourse ^= 1;
			pos = START_POS[m_nPresentCourse];
		}

		if (m_pBg)
		{
			m_pBg->SetPos(pos + BG_RELATIVE_POS);
		}

		pCamera->SetPos(pos, pos + FOCAL_POINT_RELATIVE_POS);
	}
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CTitle* CTitle::Create(void)
{
	CTitle* pTitle = new CTitle;

	if (FAILED(pTitle->Init()))
	{
		return nullptr;
	}

	return pTitle;
}






//マップの配置処理
void CTitle::SetMap(void)
{
	CMeshfield* pField = CMeshfield::Create(D3DXVECTOR3(-500.0f, -50.0f, 17500.0f), Vec3Null, "data\\STAGESET\\FieldsData\\Title\\TitleMeshfield.txt", 3);
	pField->SetTexture(CObject::TEXTURE_IRON);

	pField = CMeshfield::Create(D3DXVECTOR3(-350.0f, -50.0f, 1000.0f), Vec3Null, "data\\STAGESET\\FieldsData\\Level1\\Level1Field5.txt", 3);
	pField->SetTexture(CObject::TEXTURE_IRON);


	pField = CMeshfield::Create(D3DXVECTOR3(-125.0f, -50.0f, 2000.0f), Vec3Null, "data\\STAGESET\\FieldsData\\Level1\\Level1Field4.txt", 3);
	pField->SetTexture(CObject::TEXTURE_IRON);

	CFallBoard::Create(D3DXVECTOR3(0.0f, -45.0f, 1500.0f));

	CFallBoard::Create(D3DXVECTOR3(0.0f, -45.0f, 1200.0f));

	CFallBoard::Create(D3DXVECTOR3(0.0f, -45.0f, 900.0f));

	CModel* pModel = CModel::Create(CModel::MODEL_PIPE, D3DXVECTOR3(0.0f, -45.0f, 2300.0f));
	pModel->SetShadowDraw(false);

	CFireParticle::Create(D3DXVECTOR3(0.0f, -45.0f, 2300.0f));

	CMovingCube::Create(D3DXVECTOR3(0.0f, -45.0f, 2700.0f), D3DXVECTOR3(0.0f, 0.0f, 2.0f), 200.0f);

	CGoal::Create(D3DXVECTOR3(0.0f, -50.0f, 3500.0f));

	CNail::Create(D3DXVECTOR3(100.0f, -45.0f, 500.0f));
	CNail::Create(D3DXVECTOR3(-100.0f, -45.0f, 500.0f));
	CNail::Create(D3DXVECTOR3( 200.0f, -45.0f, 500.0f));
	CNail::Create(D3DXVECTOR3(-200.0f, -45.0f, 500.0f));
	CSpikeTrap::Create(D3DXVECTOR3(0.0f, -45.0f, 500.0f));

	CSpikeTrap::Create(D3DXVECTOR3(   0.0f, -50.0f, 300.0f), 2.0f, 40);
	CSpikeTrap::Create(D3DXVECTOR3(-100.0f, -50.0f, 200.0f), 2.0f, 40, 30);
	CSpikeTrap::Create(D3DXVECTOR3( 100.0f, -50.0f, 200.0f), 2.0f, 40, 10);
	CSpikeTrap::Create(D3DXVECTOR3(   0.0f, -50.0f, 100.0f), 2.0f, 40, 20);

	pModel = CModel::Create(CModel::MODEL_JEWEL, D3DXVECTOR3(0.0f, -25.0f, 200.0f));
	pModel->SetShadowHeight(-49.9f);

	CGoldStar* pStar = CGoldStar::Create(D3DXVECTOR3(0.0f, 25.0f, 1200.0f));
	pStar->SetShadowHeight(-5000.0f);

	pStar = CGoldStar::Create(D3DXVECTOR3(0.0f, 25.0f, 2300.0f));
	pStar->SetShadowHeight(-5000.0f);


	//===============================================================================================================================
	//===============================================================================================================================


	pField = CMeshfield::Create(D3DXVECTOR3(10000.0f + -350.0f, -50.0f, 800.0f), Vec3Null, "data\\STAGESET\\FieldsData\\Level1\\Level1Field5.txt", 3);
	pField->SetTexture(CObject::TEXTURE_SNOW);
	pField = CMeshfield::Create(D3DXVECTOR3(10000.0f + -350.0f, -50.0f, 6000.0f), Vec3Null, "data\\STAGESET\\FieldsData\\Level1\\Level1Field5.txt", 3);
	pField->SetTexture(CObject::TEXTURE_ICE);
	pField = CMeshfield::Create(D3DXVECTOR3(10000.0f + -350.0f, -49.5f, 7500.0f), Vec3Null, "data\\STAGESET\\FieldsData\\Level1\\Level1Field5.txt", 3);
	pField->SetTexture(CObject::TEXTURE_SNOW);

	CIceWall::Create(D3DXVECTOR3(10000.0f + -175.0f, -50.0f, 300.0f), false);
	CIceWall::Create(D3DXVECTOR3(10000.0f +  175.0f, -50.0f, 300.0f), false);

	CNail::Create(D3DXVECTOR3(10000.0f + -40.0f, -50.0f, 300.0f), CModel::MODEL_ICE_SPIKES);
	CNail::Create(D3DXVECTOR3(10000.0f +  40.0f, -50.0f, 300.0f), CModel::MODEL_ICE_SPIKES);

	CFallBoard::Create(D3DXVECTOR3(10000.0f, -50.0f, 700.0f));
	CFallBoard::Create(D3DXVECTOR3(10000.0f, -50.0f, 950.0f));

	CAccelerationFloor::Create(D3DXVECTOR3(10000.0f, -49.0f, 1500.0f), D3DXVECTOR2(250.0f, 250.0f), D3DXVECTOR2(0.0f, 2.0f));

	pStar = CGoldStar::Create(D3DXVECTOR3(10000.0f - 200.0f, 25.0f, 1950.0f));
	pStar->SetShadowHeight(-5000.0f);

	CNail::Create(D3DXVECTOR3(10000.0f - 200.0f, -50.0f, 2025.0f), CModel::MODEL_ICE_SPIKES);
	CNail::Create(D3DXVECTOR3(10000.0f - 125.0f, -50.0f, 2025.0f), CModel::MODEL_ICE_SPIKES);
	CNail::Create(D3DXVECTOR3(10000.0f - 125.0f, -50.0f, 1950.0f), CModel::MODEL_ICE_SPIKES);

	pStar = CGoldStar::Create(D3DXVECTOR3(10000.0f + 200.0f, 25.0f, 1950.0f));
	pStar->SetShadowHeight(-5000.0f);

	CNail::Create(D3DXVECTOR3(10000.0f + 200.0f, -50.0f, 2025.0f), CModel::MODEL_ICE_SPIKES);
	CNail::Create(D3DXVECTOR3(10000.0f + 125.0f, -50.0f, 2025.0f), CModel::MODEL_ICE_SPIKES);
	CNail::Create(D3DXVECTOR3(10000.0f + 125.0f, -50.0f, 1950.0f), CModel::MODEL_ICE_SPIKES);

	CIceWall::Create(D3DXVECTOR3(D3DXVECTOR3(10000.0f + 175.0f, -50.0f, 2200.0f)), false);
	CIceWall::Create(D3DXVECTOR3(D3DXVECTOR3(10000.0f - 175.0f, -50.0f, 2200.0f)), false);

	CSpikeTrap::Create(D3DXVECTOR3(10000.0f - 50.0f, -50.0f, 2200.0f), 2.0f, 30, 0);
	CSpikeTrap::Create(D3DXVECTOR3(10000.0f + 50.0f, -50.0f, 2200.0f), 2.0f, 30, 0);
	CSpikeTrap::Create(D3DXVECTOR3(10000.0f - 50.0f, -50.0f, 2300.0f), 2.0f, 30, 10);
	CSpikeTrap::Create(D3DXVECTOR3(10000.0f + 50.0f, -50.0f, 2300.0f), 2.0f, 30, 10);
	CSpikeTrap::Create(D3DXVECTOR3(10000.0f - 50.0f, -50.0f, 2400.0f), 2.0f, 30, 20);
	CSpikeTrap::Create(D3DXVECTOR3(10000.0f + 50.0f, -50.0f, 2400.0f), 2.0f, 30, 20);

	pModel = CModel::Create(CModel::MODEL_JEWEL, D3DXVECTOR3(10000.0f, 25.0f, 2300.0f));
	pModel->SetShadowHeight(-49.9f);
	pModel->SetModelColor(1, ColorBlue);

	CGoal::Create(D3DXVECTOR3(10000.0f, -49.0f, 3300.0f));

	CAccelerationFloor::Create(D3DXVECTOR3(10000.0f - 125.0f, -48.5f, 3000.0f), D3DXVECTOR2(125.0f, 125.0f), D3DXVECTOR2(-2.0f, 0.0f));
	CAccelerationFloor::Create(D3DXVECTOR3(10000.0f + 125.0f, -48.5f, 3000.0f), D3DXVECTOR2(125.0f, 125.0f), D3DXVECTOR2(+2.0f, 0.0f));

	pStar = CGoldStar::Create(D3DXVECTOR3(10000.0f - 200.0f, 25.0f, 3000.0f));
	pStar->SetShadowHeight(-48.0f);
	pStar = CGoldStar::Create(D3DXVECTOR3(10000.0f + 200.0f, 25.0f, 3000.0f));
	pStar->SetShadowHeight(-48.0f);
}
