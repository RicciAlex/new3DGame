//=============================================================================
//
// firstStage.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "firstStage.h"
#include "player.h"
#include "meshfield.h"
#include "inputKeyboard.h"
#include "application.h"
#include "goal.h"
#include "bg.h"
#include "nail.h"
#include "BoxHitbox.h"
#include "meshCube.h"
#include "button.h"
#include "ShurikenTrap.h"
#include "star.h"
#include "movingCube.h"
#include "triggerablePlatform.h"
#include "billboard.h"
#include "spikeTrap.h"
#include "object3D.h"
#include "accelerationFloor.h"
#include "cameraSetter.h"
#include "checkpoint.h"
#include "fallBoard.h"
#include "stalkingBot.h"
#include "sound.h"


#include "firePipe.h"
#include "fireEffect.h"
#include "fogBot.h"
#include "timer.h"
#include "PendulumClock.h"
#include "spawnTrigger.h"
#include "stalkingBot.h"
#include "PauseMenu.h"
#include "menuButton.h"
#include "icicle.h"
#include "guideArrow.h"

//�R���X�g���N�^
CFirstStage::CFirstStage()
{
	m_nCntSound = 0;
	m_nSoundDelay = 0;
}

//�f�X�g���N�^
CFirstStage::~CFirstStage()
{

}

//����������
HRESULT CFirstStage::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CGame::Init()))
	{
		return -1;
	}

	CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, -200.0f, 0.0f), 0);

	if (!pPlayer)
	{
		return -1;
	}

	m_nCntSound = CObject::random(0, DEFAULT_MIN_SOUND_DELAY);
	m_nSoundDelay = CObject::random(DEFAULT_MIN_SOUND_DELAY, DEFAULT_MAX_SOUND_DELAY);

	SetPlayer(pPlayer);

	CObject_3D* pObj3D = CObject_3D::Create();

	pObj3D->SetPos(D3DXVECTOR3(0.0f, -1100.0f, 0.0f));
	pObj3D->SetSize(D3DXVECTOR2(10000.0f, 10000.0f));
	pObj3D->SetTexture(CObject::TEXTURE_GEAR_BG);
	pObj3D->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
	pObj3D->SetTextureTiling(10.0f);

	CSpawnTrigger* pSpwnTrigger = CSpawnTrigger::Create();

	CNail* pNail = nullptr;

	CTriggerablePlatform* pTrigger = CTriggerablePlatform::Create(D3DXVECTOR3(2050.0f, 350.0f, 0.0f),
		D3DXVECTOR3(-4700.0f, -200.0f, -1750.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 150.0f);

	CSpikeTrap* pSpike = nullptr;

	pSpwnTrigger->AddTriggerPlatform(pTrigger);

	for (int nCnt = 0; nCnt < 6; nCnt++)
	{
		pSpike = CSpikeTrap::Create(D3DXVECTOR3(-2800.0f + (200.0f * nCnt), -199.9f, -1950.0f), 2.0f, 60, 0);
		pSpwnTrigger->AddObject(pSpike, -199.9f);
		
		pSpike = CSpikeTrap::Create(D3DXVECTOR3(-2800.0f + (200.0f * nCnt), -199.9f, -1750.0f), 2.0f, 60, 0);
		pSpwnTrigger->AddObject(pSpike, -199.9f);
		
		pSpike = CSpikeTrap::Create(D3DXVECTOR3(-2800.0f + (200.0f * nCnt), -199.9f, -1550.0f), 2.0f, 60, 0);
		pSpwnTrigger->AddObject(pSpike, -199.9f);

		pSpike = CSpikeTrap::Create(D3DXVECTOR3(-2700.0f + (200.0f * nCnt), -199.9f, -1850.0f), 2.0f, 60, 0);
		pSpwnTrigger->AddObject(pSpike, -199.9f);

		pSpike = CSpikeTrap::Create(D3DXVECTOR3(-2700.0f + (200.0f * nCnt), -199.9f, -1650.0f), 2.0f, 60, 0);
		pSpwnTrigger->AddObject(pSpike, -199.9f);
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		pNail = CNail::Create(D3DXVECTOR3(-1100.0f, -199.9f, -1950.0f + (500.0f * nCnt)));
		pSpwnTrigger->AddObject(pNail, -199.9f);

		pNail = CNail::Create(D3DXVECTOR3(-1250.0f, -199.9f, -1950.0f + (500.0f * nCnt)));
		pSpwnTrigger->AddObject(pNail, -199.9f);

		pNail = CNail::Create(D3DXVECTOR3(-1400.0f, -199.9f, -1950.0f + (500.0f * nCnt)));
		pSpwnTrigger->AddObject(pNail, -199.9f);

		pNail = CNail::Create(D3DXVECTOR3(-1175.0f, -199.9f, -1750.0f + (500.0f * nCnt)));
		pSpwnTrigger->AddObject(pNail, -199.9f);

		pNail = CNail::Create(D3DXVECTOR3(-1325.0f, -199.9f, -1750.0f + (500.0f * nCnt)));
		pSpwnTrigger->AddObject(pNail, -199.9f);

		pSpike = CSpikeTrap::Create(D3DXVECTOR3(-1050.0f, -199.9f, -1550.0f + (500.0f * nCnt)), 2.0f, CObject::random(15, 45), 0);
		pSpwnTrigger->AddObject(pSpike, -199.9f);

		pSpike = CSpikeTrap::Create(D3DXVECTOR3(-1130.0f, -199.9f, -1550.0f + (500.0f * nCnt)), 2.0f, CObject::random(15, 45), 0);
		pSpwnTrigger->AddObject(pSpike, -199.9f);

		pSpike = CSpikeTrap::Create(D3DXVECTOR3(-1210.0f, -199.9f, -1550.0f + (500.0f * nCnt)), 2.0f, CObject::random(15, 45), 0);
		pSpwnTrigger->AddObject(pSpike, -199.9f);

		pSpike = CSpikeTrap::Create(D3DXVECTOR3(-1290.0f, -199.9f, -1550.0f + (500.0f * nCnt)), 2.0f, CObject::random(15, 45), 0);
		pSpwnTrigger->AddObject(pSpike, -199.9f);

		pSpike = CSpikeTrap::Create(D3DXVECTOR3(-1370.0f, -199.9f, -1550.0f + (500.0f * nCnt)), 2.0f, CObject::random(15, 45), 0);
		pSpwnTrigger->AddObject(pSpike, -199.9f);

		pSpike = CSpikeTrap::Create(D3DXVECTOR3(-1450.0f, -199.9f, -1550.0f + (500.0f * nCnt)), 2.0f, CObject::random(15, 45), 0);
		pSpwnTrigger->AddObject(pSpike, -199.9f);
	}

	CGoldStar* pStar = CGoldStar::Create(D3DXVECTOR3(-2400.0f, -199.9f, -1650.0f));
	pStar->SetShadowDraw(false);
	pSpwnTrigger->AddObject(pStar, -150.0f);

	pStar = CGoldStar::Create(D3DXVECTOR3(-1200.0f, -199.9f, -1350.0f));
	pStar->SetShadowDraw(false);
	pSpwnTrigger->AddObject(pStar, -150.0f);

	pStar = CGoldStar::Create(D3DXVECTOR3(-1325.0f, -199.9f, -425.0f));
	pStar->SetShadowDraw(false);
	pSpwnTrigger->AddObject(pStar, -150.0f);

	LoadMap("data\\STAGESET\\MapData\\FirstStage.txt", CObject::TEXTURE_IRON);

	//CGuideArrow* pArrow = CGuideArrow::Create(D3DXVECTOR3(800.0f, 120.1f, -125.0f));
	////pArrow->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, D3DX_PI * 0.5f, D3DX_PI * 0.0f));
	//CGuideArrow::Create(D3DXVECTOR3(1300.0f, 120.1f, -125.0f));
	////pArrow->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));

	pPlayer->SetStarNumber(pPlayer->GetStarNumber() + 3);

	return S_OK;
}

//�I������
void CFirstStage::Uninit(void)
{
	//��{�N���X�̏I������
	CGame::Uninit();
}

//�X�V����
void CFirstStage::Update(void)
{
	//��{�N���X�̍X�V����
	CGame::Update();

	m_nCntSound++;

	if (m_nCntSound >= m_nSoundDelay)
	{
		m_nSoundDelay = CObject::random(DEFAULT_MIN_SOUND_DELAY, DEFAULT_MAX_SOUND_DELAY);

		m_nCntSound = 0;

		CApplication::GetSound()->Play((CSound::SOUND_LABEL)CObject::random(CSound::SOUND_LABEL_SE_AMBIENT_1, CSound::SOUND_LABEL_SE_AMBIENT_3));
	}
}




//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================


//��������
CFirstStage* CFirstStage::Create(void)
{
	CFirstStage* pStage = new CFirstStage;		//�C���X�^���X�𐶐�����

	if (FAILED(pStage->Init()))
	{//����������
		return nullptr;
	}

	return pStage;								//���������C���X�^���X��Ԃ�
}