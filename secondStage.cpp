//=============================================================================
//
// secondStage.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "secondStage.h"
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
#include "iceWall.h"

//�R���X�g���N�^
CSecondStage::CSecondStage()
{

}

//�f�X�g���N�^
CSecondStage::~CSecondStage()
{

}

//����������
HRESULT CSecondStage::Init(void)
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

	SetPlayer(pPlayer);

	CObject_3D* pObj3D = CObject_3D::Create();

	pObj3D->SetPos(D3DXVECTOR3(0.0f, -1100.0f, 0.0f));
	pObj3D->SetSize(D3DXVECTOR2(10000.0f, 10000.0f));
	pObj3D->SetTexture(CObject::TEXTURE_ICE);
	pObj3D->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
	pObj3D->SetTextureTiling(10.0f);

	LoadMap("data\\STAGESET\\MapData\\SecondStage.txt", CObject::TEXTURE_SNOW);

	/*CModel* pModel = nullptr;

	pModel = CModel::Create(CModel::MODEL_ICE_FRAGMENT_1, D3DXVECTOR3(-39.0f, -135.0f, 200.0f));
	pModel->SetScale(4.0f);
	pModel->SetShadowDraw(false);
	pModel = CModel::Create(CModel::MODEL_ICE_FRAGMENT_2, D3DXVECTOR3(39.0f, -150.0f, 200.0f));
	pModel->SetScale(4.0f);
	pModel->SetShadowDraw(false);
	pModel = CModel::Create(CModel::MODEL_ICE_FRAGMENT_3, D3DXVECTOR3(41.0f, -26.0f, 200.0f));
	pModel->SetScale(4.0f);
	pModel->SetShadowDraw(false);
	pModel = CModel::Create(CModel::MODEL_ICE_FRAGMENT_4, D3DXVECTOR3(-40.0f, -30.0f, 200.0f));
	pModel->SetScale(4.0f);
	pModel->SetShadowDraw(false);
	pModel = CModel::Create(CModel::MODEL_ICE_FRAGMENT_5, D3DXVECTOR3(0.0f, 78.0f, 200.0f));
	pModel->SetScale(4.0f);
	pModel->SetShadowDraw(false);*/

	CIceWall::Create(D3DXVECTOR3(0.0f, -200.0f, 200.0f), false);
	CIceWall::Create(D3DXVECTOR3(-400.0f, -200.0f, 200.0f), true);

	return S_OK;
}

//�I������
void CSecondStage::Uninit(void)
{
	//��{�N���X�̏I������
	CGame::Uninit();
}

//�X�V����
void CSecondStage::Update(void)
{
	//��{�N���X�̍X�V����
	CGame::Update();

#ifdef _DEBUG

	if (CInputKeyboard::GetKeyboardTrigger(DIK_O))
	{
		CApplication::SetFade(CApplication::MODE_RESULTS);
	}

	if (CInputKeyboard::GetKeyboardTrigger(DIK_T))
	{
		CIcicle::Create(D3DXVECTOR3(200.0f, -200.0f, 200.0f));
	}

#endif // DEBUG

}




//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================


//��������
CSecondStage* CSecondStage::Create(void)
{
	CSecondStage* pStage = new CSecondStage;		//�C���X�^���X�𐶐�����

	if (FAILED(pStage->Init()))
	{//����������
		return nullptr;
	}

	return pStage;								//���������C���X�^���X��Ԃ�
}