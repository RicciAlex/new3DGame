//=============================================================================
//
// boss.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "boss.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "sound.h"
#include "icicle.h"


#include "inputKeyboard.h"


//=============================================================================
//								�ÓI�ϐ��̏�����
//=============================================================================
const D3DXVECTOR3 CBoss::DEFAULT_POS = { 0.0f, 200.0f, 2775.0f };			//�f�B�t�H���g�̈ʒu



//�R���X�g���N�^
CBoss::CBoss()
{
	//�����o�[�ϐ����N���A����
	m_targetPos = Vec3Null;
	m_nCntAttack = 0;
}

//�f�X�g���N�^
CBoss::~CBoss()
{

}

//����������
HRESULT CBoss::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	SetModel(CModel::MODEL_BOSS_EYES);
	SetPos(DEFAULT_POS);
	SetShadowDraw(false);
	SetScale(4);
	SetDrawDistance(5000.0f);

	return S_OK;
}

//�I������
void CBoss::Uninit(void)
{
	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V����
void CBoss::Update(void)
{
	D3DXVECTOR3 playerPos = CApplication::GetGame()->GetPlayer()->GetPos();
	SetPos(playerPos + DEFAULT_POS);

	//��{�N���X�̍X�V����
	CModel::Update();

	m_nCntAttack++;

	if (m_nCntAttack == 60)
	{
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ROAR);
	}
	else if (m_nCntAttack == 130)
	{
		m_targetPos = playerPos;
	}
	if (m_nCntAttack >= 150)
	{
		m_nCntAttack = 0;

		CIcicle::Create(m_targetPos);
	}
}




//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================




//��������
CBoss* CBoss::Create(void)
{
	CBoss* pBoss = new CBoss;			//�C���X�^���X�𐶐�����


	if (FAILED(pBoss->Init()))
	{//����������
		return nullptr;
	}

	return pBoss;						//���������C���X�^���X��Ԃ�
}