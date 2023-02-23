//=============================================================================
//
// game.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "game.h"
#include "application.h"
#include "player.h"
#include "timer.h"
#include "inputKeyboard.h"
#include "meshfield.h"
#include "BoxHitbox.h"
#include "goal.h"
#include "bg.h"
#include "nail.h"
#include "spikeTrap.h"
#include "star.h"
#include "ShurikenTrap.h"
#include "triggerablePlatform.h"
#include "movingCube.h"
#include "accelerationFloor.h"
#include "cameraSetter.h"
#include "checkpoint.h"
#include "fallBoard.h"
#include "FirePipe.h"
#include "fogBot.h"
#include "PendulumClock.h"
#include "PauseMenu.h"
#include "gem.h"
#include "iceWall.h"
#include "stalkingBot.h"
#include "guideArrow.h"
#include <stdio.h>
#include <string.h>


//コンストラクタ
CGame::CGame() : CMode(true)
{
	m_pPlayer = nullptr;
	m_pTimer = nullptr;
	m_pPauseMenu = nullptr;
	m_pGoal = nullptr;
}

//デストラクタ
CGame::~CGame()
{

}

//初期化処理
HRESULT CGame::Init(void)
{
	m_pPlayer = nullptr;
	m_pTimer = CTimer::Create();
	m_pPauseMenu = CPauseMenu::Create();

	CBg* pBg = CBg::Create(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), 3500.0f);

	if (pBg)
	{
		pBg->SetBg(Vec3Null, D3DXCOLOR(0.2f, 0.4f, 0.5f, 1.0f));
	}

	return S_OK;
}

//終了処理
void CGame::Uninit(void)
{
	if (m_pPlayer)
	{
		m_pPlayer->Release();
		m_pPlayer = nullptr;
	}

	if (m_pTimer)
	{
		m_pTimer->Release();
		m_pTimer = nullptr;
	}

	if (m_pPauseMenu)
	{
		m_pPauseMenu->Uninit();
		delete m_pPauseMenu;
		m_pPauseMenu = nullptr;
	}
}

//更新処理
void CGame::Update(void)
{
	if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
	{
		if (m_pPauseMenu && !CApplication::GetPause())
		{
			m_pPauseMenu->SetPos(CPauseMenu::DEFAULT_MENU_POS);
			CApplication::SetPause(true);
		}
	}

	if (CApplication::GetPause())
	{
		m_pPauseMenu->Update();
	}
}

//時間の追加処理
void CGame::AddTime(const float fMilliseconds)
{
	if (m_pTimer)
	{
		m_pTimer->AddTime(fMilliseconds);
	}
}


//プレイヤーの設定処理
void CGame::SetPlayer(CPlayer* pPlayer)
{
	m_pPlayer = pPlayer;
}

//時間の取得処理
const float CGame::GetTime(void)
{
	float fTime = 0.0f;

	if (m_pTimer)
	{
		fTime = m_pTimer->GetTime();
	}

	return fTime;
}

//プレイヤーの取得処理
CPlayer* CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//ゴールの取得処理
CGoal * CGame::GetGoal(void)
{
	return m_pGoal;
}

//マップのロード処理
void CGame::LoadMap(char* pPass, CObject::TextType fieldTexture)
{
	FILE* pFile = fopen(pPass, "r");

	if (pFile)
	{
		char aStr[1024] = {};			//読み込み処理に必要な文字列を宣言する

		int nStar = 0;

		/*std::function<void(FILE*)> func = [this](FILE* pFile) {
			LoadMeshField(pFile,); 
		};
		func(pFile);*/

		while (strcmp(aStr, "END_SCRIPT") != 0)
		{
			fscanf(pFile, "%s", aStr);

			if (strcmp(aStr, "FIELD") == 0)
			{
				LoadMeshField(pFile, fieldTexture);
			}
			else if (strcmp(aStr, "BOX_HITBOX") == 0)
			{
				LoadHitbox(pFile);
			}
			else if (strcmp(aStr, "GOAL") == 0)
			{
				LoadGoal(pFile, m_pGoal);
			}
			else if (strcmp(aStr, "NAIL") == 0)
			{
				LoadNail(pFile);
			}
			else if (strcmp(aStr, "SPIKE_TRAP") == 0)
			{
				LoadSpikeTrap(pFile);
			}
			else if (strcmp(aStr, "STAR") == 0)
			{
				LoadStar(pFile, nStar);
			}
			else if (strcmp(aStr, "SHURIKEN_TRAP") == 0)
			{
				LoadShurikenTrap(pFile);
			}
			else if (strcmp(aStr, "TRIGGERABLE_PLATFORM") == 0)
			{
				LoadTriggerablePlatform(pFile);
			}
			else if (strcmp(aStr, "MOVING_CUBE") == 0)
			{
				LoadMovingCube(pFile);
			}
			else if (strcmp(aStr, "ACCELERATION_FLOOR") == 0)
			{
				LoadAccelerationFloor(pFile);
			}
			else if (strcmp(aStr, "CAMERA_SETTER") == 0)
			{
				LoadCameraSetter(pFile);
			}
			else if (strcmp(aStr, "CHECKPOINT") == 0)
			{
				LoadCheckpoint(pFile);
			}
			else if (strcmp(aStr, "FALLBOARD") == 0)
			{
				LoadFallBoard(pFile);
			}
			else if (strcmp(aStr, "FIRE_PIPE") == 0)
			{
				LoadFirePipe(pFile);
			}
			else if (strcmp(aStr, "FOG_BOT") == 0)
			{
				LoadFogbot(pFile);
			}
			else if (strcmp(aStr, "CLOCK") == 0)
			{
				LoadPendulumClock(pFile);
			}
			else if (strcmp(aStr, "GEM") == 0)
			{
				LoadGem(pFile);
			}
			else if (strcmp(aStr, "ICE_WALL") == 0)
			{
				LoadIceWall(pFile);
			}
			else if (strcmp(aStr, "GUIDE_ARROW") == 0)
			{
				LoadGuideArrow(pFile);
			}
		}

		fclose(pFile);

		if (m_pPlayer)
		{
			m_pPlayer->SetStarNumber(nStar);
		}
	}
}

void CGame::LoadVector2(FILE * pFile, D3DXVECTOR2 & vector2)
{
	float fX = 0.0f, fY = 0.0f;

	fscanf(pFile, "%f", &fX);
	fscanf(pFile, "%f", &fY);

	vector2 = D3DXVECTOR2(fX, fY);
}

void CGame::LoadVector3(FILE * pFile, D3DXVECTOR3 & vector3)
{
	float fX = 0.0f, fY = 0.0f, fZ = 0.0f;

	fscanf(pFile, "%f", &fX);
	fscanf(pFile, "%f", &fY);
	fscanf(pFile, "%f", &fZ);

	vector3 = D3DXVECTOR3(fX, fY, fZ);
}

void CGame::LoadColor(FILE * pFile, D3DXCOLOR & col)
{
	float fR = 0.0f, fG = 0.0f, fB = 0.0f, fA = 0.0f;

	fscanf(pFile, "%f", &fR);
	fscanf(pFile, "%f", &fG);
	fscanf(pFile, "%f", &fB);
	fscanf(pFile, "%f", &fA);

	col = D3DXCOLOR(fR, fG, fB, fA);
}

void CGame::LoadMeshField(FILE * pFile, CObject::TextType fieldTexture)
{
	char aStr[1024] = {};
	FILE* pCheck = nullptr;
	bool bCreate = false;
	bool bFriction = false;
	char aPass[1024] = {};
	D3DXVECTOR3 pos = Vec3Null;
	D3DXVECTOR3 rot = Vec3Null;
	float fFriction = 0.0f;

	while (strcmp(aStr, "END_FIELD") != 0)
	{
		fscanf(pFile, "%s", aStr);

		if (strcmp(aStr, "PASS") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%s", aPass);

			if (pCheck = fopen(aPass, "r"))
			{
				fclose(pCheck);
				bCreate = true;
			}
		}
		else if (strcmp(aStr, "POS") == 0)
		{
			fscanf(pFile, "%s", aStr);
			
			LoadVector3(pFile, pos);
		}
		else if (strcmp(aStr, "ROT") == 0)
		{
			fscanf(pFile, "%s", aStr);
			
			LoadVector3(pFile, rot);
		}
		else if (strcmp(aStr, "FRICTION") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%f", &fFriction);
			bFriction = true;
		}
		else if (strcmp(aStr, "TEXTURE") == 0)
		{
			char aTex[80] = {};

			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%s", aTex);
			bFriction = true;

			if (strcmp(aTex, "IRON") == 0)
			{
				fieldTexture = CObject::TEXTURE_IRON;
			}
			else if (strcmp(aTex, "ICE") == 0)
			{
				fieldTexture = CObject::TEXTURE_ICE;
			}
			else if (strcmp(aTex, "SNOW") == 0)
			{
				fieldTexture = CObject::TEXTURE_SNOW;
			}
		}
	}

	if (bCreate)
	{
		CMeshfield* pField = CMeshfield::Create(pos, rot, aPass, 3);
		bCreate = false;

		if (pField)
		{
			pField->SetTexture(fieldTexture);

			if (bFriction)
			{
				pField->SetFriction(fFriction);
			}
		}
	}
}

void CGame::LoadHitbox(FILE* pFile)
{
	char aStr[1024] = {};
	D3DXVECTOR3 pos = Vec3Null;
	D3DXVECTOR3 relativePos = Vec3Null;
	D3DXVECTOR3 size = Vec3Null;
	CHitbox::HITBOX_TYPE type = CHitbox::TYPE_MAX;
	int nScore = 0;
	CHitbox::INTERACTION_EFFECT effect = CHitbox::EFFECT_MAX;

	while (strcmp(aStr, "END_HITBOX") != 0)
	{
		fscanf(pFile, "%s", aStr);

		if (strcmp(aStr, "POS") == 0)
		{
			fscanf(pFile, "%s", aStr);
			
			LoadVector3(pFile, pos);
		}
		if (strcmp(aStr, "RELATIVE_POS") == 0)
		{
			fscanf(pFile, "%s", aStr);
			
			LoadVector3(pFile, relativePos);
		}
		else if (strcmp(aStr, "SIZE") == 0)
		{
			fscanf(pFile, "%s", aStr);
			
			LoadVector3(pFile, size);
		}
		else if (strcmp(aStr, "TYPE") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%s", aStr);

			SetLoadedHitboxType(aStr, type);
		}
		else if (strcmp(aStr, "SCORE") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%d", &nScore);
		}
		else if (strcmp(aStr, "EFFECT") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%s", aStr);

			SetLoadedHitboxEffect(aStr, effect);
		}
	}

	CBoxHitbox::Create(pos, relativePos, size, type, nullptr, nScore, effect);
}

void CGame::SetLoadedHitboxType(char * pLoadedType, CHitbox::HITBOX_TYPE &type)
{
	if (strcmp(pLoadedType, "PLAYER") == 0)
	{
		type = CHitbox::TYPE_PLAYER;
	}
	else if (strcmp(pLoadedType, "OBSTACLE") == 0)
	{
		type = CHitbox::TYPE_OBSTACLE;
	}
	else if (strcmp(pLoadedType, "NEUTRAL") == 0)
	{
		type = CHitbox::TYPE_NEUTRAL;
	}
	else if (strcmp(pLoadedType, "VANISHING") == 0)
	{
		type = CHitbox::TYPE_VANISHING;
	}
	else if (strcmp(pLoadedType, "BUTTON") == 0)
	{
		type = CHitbox::TYPE_BUTTON;
	}
	else if (strcmp(pLoadedType, "OVERLAPPABLE") == 0)
	{
		type = CHitbox::TYPE_OVERLAPPABLE;
	}
	else if (strcmp(pLoadedType, "FALL") == 0)
	{
		type = CHitbox::TYPE_FALL;
	}
}

void CGame::SetLoadedHitboxEffect(char * pLoadedType, CHitbox::INTERACTION_EFFECT & effect)
{
	if (strcmp(pLoadedType, "DAMAGE") == 0)
	{
		effect = CHitbox::EFFECT_DAMAGE;
	}
	else if (strcmp(pLoadedType, "LAUNCH") == 0)
	{
		effect = CHitbox::EFFECT_LAUNCH;
	}
	else if (strcmp(pLoadedType, "PUSH") == 0)
	{
		effect = CHitbox::EFFECT_PUSH;
	}
	else if (strcmp(pLoadedType, "BOUNCE") == 0)
	{
		effect = CHitbox::EFFECT_BOUNCE;
	}
	else if (strcmp(pLoadedType, "JUMP") == 0)
	{
		effect = CHitbox::EFFECT_JUMP;
	}
	else if (strcmp(pLoadedType, "FALL") == 0)
	{
		effect = CHitbox::EFFECT_FALL;
	}
}

void CGame::LoadGoal(FILE * pFile, CGoal* pGoal)
{
	if (!m_pGoal)
	{
		char aStr[1024] = {};
		D3DXVECTOR3 pos = Vec3Null;

		while (strcmp(aStr, "END_GOAL") != 0)
		{
			fscanf(pFile, "%s", aStr);

			if (strcmp(aStr, "POS") == 0)
			{
				fscanf(pFile, "%s", aStr);

				LoadVector3(pFile, pos);

				break;
			}
		}

		m_pGoal = CGoal::Create(pos);
	}
}

void CGame::LoadNail(FILE * pFile)
{
	char aStr[1024] = {};
	D3DXVECTOR3 pos = Vec3Null;
	bool bIce = false;

	while (strcmp(aStr, "END_NAIL") != 0)
	{
		fscanf(pFile, "%s", aStr);

		if (strcmp(aStr, "POS") == 0)
		{
			fscanf(pFile, "%s", aStr);
			
			LoadVector3(pFile, pos);
		}

		if (strcmp(aStr, "ICE") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%s", aStr);

			if (strcmp(aStr, "YES") == 0)
			{
				bIce = true;
			}
		}
	}

	if (!bIce)
	{
		CNail::Create(pos);
	}
	else
	{
		CNail::Create(pos, CModel::MODEL_ICE_SPIKES);
	}
}

void CGame::LoadSpikeTrap(FILE * pFile)
{
	char aStr[1024] = {};
	D3DXVECTOR3 pos = Vec3Null;
	float fSpeed = CSpikeTrap::DEFAULT_SPEED;
	int nDelay = CSpikeTrap::DEFAULT_DELAY;
	int nStartDelay = 0;

	while (strcmp(aStr, "END_SPIKE_TRAP") != 0)
	{
		fscanf(pFile, "%s", aStr);

		if (strcmp(aStr, "POS") == 0)
		{
			fscanf(pFile, "%s", aStr);
			
			LoadVector3(pFile, pos);
		}
		else if (strcmp(aStr, "SPEED") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%f", &fSpeed);
		}
		else if (strcmp(aStr, "DELAY") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%d", &nDelay);
		}
		else if (strcmp(aStr, "START_DELAY") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%d", &nStartDelay);
		}
	}

	CSpikeTrap::Create(pos, fSpeed, nDelay, nStartDelay);
}

void CGame::LoadStar(FILE * pFile, int& nStar)
{
	char aStr[1024] = {};
	D3DXVECTOR3 pos = Vec3Null;
	float fShadowHeight = -199.9f;

	while (strcmp(aStr, "END_STAR") != 0)
	{
		fscanf(pFile, "%s", aStr);

		if (strcmp(aStr, "POS") == 0)
		{
			fscanf(pFile, "%s", aStr);
			
			LoadVector3(pFile, pos);
		}
		else if (strcmp(aStr, "SHADOW_HEIGHT") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%f", &fShadowHeight);
		}
	}

	CGoldStar* pStar = CGoldStar::Create(pos, fShadowHeight);

	if (pStar)
	{
		nStar++;
	}
}

void CGame::LoadShurikenTrap(FILE * pFile)
{
	char aStr[1024] = {};
	D3DXVECTOR3 pos = Vec3Null;
	float fYRot = 0.0f;
	float fDistance = 0.0f;
	D3DXCOLOR col = ColorRed, triggeredCol = ColorGreen;

	while (strcmp(aStr, "END_SHURIKEN_TRAP") != 0)
	{
		fscanf(pFile, "%s", aStr);

		if (strcmp(aStr, "POS") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector3(pFile, pos);
		}
		else if (strcmp(aStr, "Y_ROT") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%f", &fYRot);
		}
		else if (strcmp(aStr, "DISTANCE") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%f", &fDistance);
		}
		else if (strcmp(aStr, "NORMAL_COLOR") == 0)
		{
			fscanf(pFile, "%s", aStr);
			
			LoadColor(pFile, col);
		}
		else if (strcmp(aStr, "TRIGGERED_COLOR") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadColor(pFile, triggeredCol);
		}
	}

	CShurikenTrap::Create(pos, fYRot, fDistance, col, triggeredCol);
}

void CGame::LoadTriggerablePlatform(FILE * pFile)
{
	char aStr[1024] = {};
	D3DXVECTOR3 pos = Vec3Null;
	D3DXVECTOR3 buttonPos = Vec3Null;
	D3DXVECTOR3 move = Vec3Null;
	float fRange = 0.0f;
	bool bMoved = false;
	D3DXVECTOR3 originalPos = Vec3Null;

	while (strcmp(aStr, "END_TRIGGERABLE_PLATFORM") != 0)
	{
		fscanf(pFile, "%s", aStr);

		if (strcmp(aStr, "POS") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector3(pFile, pos);
		}
		if (strcmp(aStr, "BUTTON_POS") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector3(pFile, buttonPos);
		}
		if (strcmp(aStr, "MOVE") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector3(pFile, move);
		}
		if (strcmp(aStr, "RANGE") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%f", &fRange);
		}
		if (strcmp(aStr, "ORIGINAL_POS") == 0)
		{
			fscanf(pFile, "%s", aStr);
			
			LoadVector3(pFile, originalPos);
			bMoved = true;
		}
	}

	CTriggerablePlatform* pPlatform = CTriggerablePlatform::Create(pos, buttonPos, move, fRange);

	if (bMoved && pPlatform)
	{
		pPlatform->SetOriginalPos(originalPos);
	}
}

void CGame::LoadMovingCube(FILE * pFile)
{
	char aStr[1024] = {};
	D3DXVECTOR3 pos = Vec3Null;
	D3DXVECTOR3 move = Vec3Null;
	float fRange = 0.0f;

	while (strcmp(aStr, "END_MOVING_CUBE") != 0)
	{
		fscanf(pFile, "%s", aStr);

		if (strcmp(aStr, "POS") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector3(pFile, pos);
		}
		if (strcmp(aStr, "MOVE") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector3(pFile, move);
		}
		if (strcmp(aStr, "RANGE") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%f", &fRange);
		}
	}

	CMovingCube::Create(pos, move, fRange);
}

void CGame::LoadAccelerationFloor(FILE * pFile)
{
	char aStr[1024] = {};
	D3DXVECTOR3 pos = Vec3Null;
	D3DXVECTOR2 size = Vec2Null;
	D3DXVECTOR2 speed = Vec2Null;
	D3DXVECTOR2 tiling = Vec2Null;
	bool bTiling = false;

	while (strcmp(aStr, "END_ACCELERATION_FLOOR") != 0)
	{
		fscanf(pFile, "%s", aStr);

		if (strcmp(aStr, "POS") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector3(pFile, pos);
		}
		if (strcmp(aStr, "SIZE") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector2(pFile, size);
		}
		if (strcmp(aStr, "SPEED") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector2(pFile, speed);
		}
		if (strcmp(aStr, "TILING") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector2(pFile, tiling);
			bTiling = true;
		}
	}

	CAccelerationFloor* pFloor = CAccelerationFloor::Create(pos, size, speed);

	if (bTiling && pFloor)
	{
		pFloor->SetTextureTiling(tiling);
	}
}

void CGame::LoadCameraSetter(FILE * pFile)
{
	char aStr[1024] = {};
	D3DXVECTOR3 pos = Vec3Null;
	D3DXVECTOR3 size = Vec3Null;


	while (strcmp(aStr, "END_CAMERA_SETTER") != 0)
	{
		fscanf(pFile, "%s", aStr);

		if (strcmp(aStr, "POS") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector3(pFile, pos);
		}
		if (strcmp(aStr, "SIZE") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector3(pFile, size);
		}		
	}

	CCameraSetter::Create(pos, size, CPlayer::CAMERA_POS_BACK);
}

void CGame::LoadCheckpoint(FILE * pFile)
{
	char aStr[1024] = {};
	D3DXVECTOR3 pos = Vec3Null;
	float fRange = CCheckpoint::DEFAULT_RANGE;
	D3DXCOLOR normalCol = CCheckpoint::DEFAULT_NORMAL_COLOR;
	D3DXCOLOR triggeredCol = CCheckpoint::DEFAULT_ACTIVE_COLOR;

	while (strcmp(aStr, "END_CHECKPOINT") != 0)
	{
		fscanf(pFile, "%s", aStr);

		if (strcmp(aStr, "POS") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector3(pFile, pos);
		}
		if (strcmp(aStr, "SIZE") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%f", &fRange);
		}
		if (strcmp(aStr, "NORMAL_COLOR") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadColor(pFile, normalCol);
		}
		if (strcmp(aStr, "TRIGGERED_COLOR") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadColor(pFile, triggeredCol);
		}
	}

	CCheckpoint::Create(pos, fRange, normalCol, triggeredCol);
}

void CGame::LoadFallBoard(FILE * pFile)
{
	char aStr[1024] = {};
	D3DXVECTOR3 pos = Vec3Null;
	int nFallDelay = CFallBoard::DEFAULT_FALL_DELAY;

	while (strcmp(aStr, "END_FALLBOARD") != 0)
	{
		fscanf(pFile, "%s", aStr);

		if (strcmp(aStr, "POS") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector3(pFile, pos);
		}
		if (strcmp(aStr, "DELAY") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%d", &nFallDelay);
		}
	}

	CFallBoard::Create(pos, nFallDelay);
}

void CGame::LoadFirePipe(FILE * pFile)
{
	char aStr[1024] = {};
	D3DXVECTOR3 pos = Vec3Null;
	int nFireTime = CFirePipe::DEFAULT_FIRE_TIME;
	int nStartDelay = 0;

	while (strcmp(aStr, "END_FIRE_PIPE") != 0)
	{
		fscanf(pFile, "%s", aStr);

		if (strcmp(aStr, "POS") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector3(pFile, pos);
		}
		if (strcmp(aStr, "DELAY") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%d", &nFireTime);
		}
		if (strcmp(aStr, "START_DELAY") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%d", &nStartDelay);
		}
	}

	CFirePipe::Create(pos, nFireTime, nStartDelay);
}

void CGame::LoadFogbot(FILE * pFile)
{
	char aStr[1024] = {};
	D3DXVECTOR3 pos = Vec3Null;
	float fShadowHeight = 0.0f;
	bool bStalk = false;

	while (strcmp(aStr, "END_FOG_BOT") != 0)
	{
		fscanf(pFile, "%s", aStr);

		if (strcmp(aStr, "POS") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector3(pFile, pos);
		}
		if (strcmp(aStr, "SHADOW_HEIGHT") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%f", &fShadowHeight);
		}
		if (strcmp(aStr, "FOLLOW") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%s", aStr);

			if (strcmp(aStr, "YES") == 0)
			{
				bStalk = true;
			}
		}
	}

	if (!bStalk)
	{
		CFogbot::Create(pos, fShadowHeight);
	}
	else
	{
		CStalkingBot::Create(pos, fShadowHeight);
	}
}

void CGame::LoadPendulumClock(FILE * pFile)
{
	char aStr[1024] = {};
	D3DXVECTOR3 pos = Vec3Null;
	D3DXVECTOR3 rot = Vec3Null;
	float fShadowHeight = 0.0f;
	float fRange = CPendulumClock::DEFAULT_RANGE;

	while (strcmp(aStr, "END_CLOCK") != 0)
	{
		fscanf(pFile, "%s", aStr);

		if (strcmp(aStr, "POS") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector3(pFile, pos);
		}
		if (strcmp(aStr, "ROT") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector3(pFile, rot);
		}
		if (strcmp(aStr, "SHADOW_HEIGHT") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%f", &fShadowHeight);
		}
		if (strcmp(aStr, "RANGE") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%f", &fRange);
		}
	}

	CPendulumClock::Create(pos, rot, fShadowHeight, fRange);
}

void CGame::LoadGem(FILE * pFile)
{
	if (m_pGoal)
	{
		char aStr[1024] = {};
		D3DXVECTOR3 pos = Vec3Null;
		D3DXCOLOR col = ColorRed;
		float fShadowHeight = -199.9f;
		D3DXVECTOR3 newPos = Vec3Null;

		while (strcmp(aStr, "END_GEM") != 0)
		{
			fscanf(pFile, "%s", aStr);

			if (strcmp(aStr, "POS") == 0)
			{
				fscanf(pFile, "%s", aStr);

				LoadVector3(pFile, pos);
			}
			if (strcmp(aStr, "COLOR") == 0)
			{
				fscanf(pFile, "%s", aStr);

				LoadColor(pFile, col);
			}
			if (strcmp(aStr, "SHADOW_HEIGHT") == 0)
			{
				fscanf(pFile, "%s", aStr);
				fscanf(pFile, "%f", &fShadowHeight);
			}
			if (strcmp(aStr, "NEW_POS") == 0)
			{
				fscanf(pFile, "%s", aStr);

				LoadVector3(pFile, newPos);
			}
		}

		CGem::Create(pos, col, fShadowHeight, newPos, m_pGoal);
	}
}

void CGame::LoadIceWall(FILE * pFile)
{
	char aStr[1024] = {};
	D3DXVECTOR3 pos = Vec3Null;
	bool bRotate = false;

	while (strcmp(aStr, "END_ICE_WALL") != 0)
	{
		fscanf(pFile, "%s", aStr);

		if (strcmp(aStr, "POS") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector3(pFile, pos);
		}
		if (strcmp(aStr, "ROTATE") == 0)
		{
			fscanf(pFile, "%s", aStr);
			fscanf(pFile, "%s", aStr);

			if (strcmp(aStr, "YES") == 0)
			{
				bRotate = true;
			}
		}
	}

	CIceWall::Create(pos, bRotate);
}

void CGame::LoadGuideArrow(FILE * pFile)
{
	char aStr[1024] = {};
	D3DXVECTOR3 pos = Vec3Null;
	D3DXVECTOR3 rot = Vec3Null;

	while (strcmp(aStr, "END_GUIDE_ARROW") != 0)
	{
		fscanf(pFile, "%s", aStr);

		if (strcmp(aStr, "POS") == 0)
		{
			fscanf(pFile, "%s", aStr);

			LoadVector3(pFile, pos);
		}
		if (strcmp(aStr, "ROT") == 0)
		{
			fscanf(pFile, "%s", aStr);
			
			LoadVector3(pFile, rot);
		}
	}

	CGuideArrow::Create(pos, rot);
}
