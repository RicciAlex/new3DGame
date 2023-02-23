//=============================================================================
//
// bossStage.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bossStage.h"
#include "player.h"
#include "boss.h"
#include "application.h"
#include "rendering.h"

#include "inputKeyboard.h"
#include "cannon.h"



//�R���X�g���N�^
CBossStage::CBossStage()
{

}

//�f�X�g���N�^
CBossStage::~CBossStage()
{
	
}


//����������
HRESULT CBossStage::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CGame::Init()))
	{
		return -1;
	}

	CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(100.0f, -200.0f, 550.0f), 0);
	//CPlayer* pPlayer = CPlayer::Create(D3DXVECTOR3(6000.0f, -200.0f, 1100.0f), 0);

	if (!pPlayer)
	{
		return -1;
	}

	SetPlayer(pPlayer);

	CObject_3D* pObj3D = CObject_3D::Create();

	pObj3D->SetPos(D3DXVECTOR3(0.0f, -1100.0f, 0.0f));
	pObj3D->SetSize(D3DXVECTOR2(15000.0f, 15000.0f));
	pObj3D->SetTexture(CObject::TEXTURE_ICE);
	pObj3D->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
	pObj3D->SetTextureTiling(15.0f);

	LoadMap("data\\STAGESET\\MapData\\BossStage.txt", CObject::TEXTURE_SNOW);

	CBoss* pBoss = CBoss::Create();
	
	CCannon::Create(D3DXVECTOR3(-4575.0f, -200.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.05f, 0.0f), D3DXVECTOR3(-4325.0f, -200.0f, 0.0f), pBoss);
	CCannon::Create(D3DXVECTOR3(4825.0f, -200.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.05f, 0.0f), D3DXVECTOR3(4575.0f, -200.0f, 0.0f), pBoss);
	CCannon::Create(D3DXVECTOR3(-1125.0f, -200.0f, 2875.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.05f, 0.0f), D3DXVECTOR3(-1125.0f, -200.0f, 2625.0f), pBoss);
	CCannon::Create(D3DXVECTOR3(1325.0f, -200.0f, 3975.0f), D3DXVECTOR3(0.0f, -D3DX_PI * 0.05f, 0.0f), D3DXVECTOR3(1325.0f, -200.0f, 3725.0f), pBoss);

	return S_OK;
}

//�I������
void CBossStage::Uninit(void)
{
	//��{�N���X�̏I������
	CGame::Uninit();
}

//�X�V����
void CBossStage::Update(void)
{
	//��{�N���X�̍X�V����
	CGame::Update();
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CBossStage* CBossStage::Create(void)
{
	CBossStage* pStage = new CBossStage;		//�C���X�^���X�𐶐�����

	if (FAILED(pStage->Init()))
	{//����������

		return nullptr;
	}

	return pStage;		//���������C���X�^���X��Ԃ�
}