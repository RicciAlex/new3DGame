//=============================================================================
//
// spikeTrap.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "stalkingBot.h"


//=============================================================================
//								�ÓI�ϐ��̏�����
//=============================================================================
const float		  CStalkingBot::DEFAULT_APPROACHING_SPEED = 15.0f;				//�f�B�t�H���g�̒ǂ������鑬�x
const float		  CStalkingBot::DEFAULT_ANGLE_SPEED = D3DX_PI * 0.01f;			//�f�B�t�H���g�̉�]���x
const float		  CStalkingBot::DEFAULT_FIRST_COEFF = 3.0f;						//�f�B�t�H���g�̍ŏ��̃p�����[�^(�p�����g���b�N�������p)
const float		  CStalkingBot::DEFAULT_SECOND_COEFF = 5.0f;					//�f�B�t�H���g�̓�Ԗڂ̃p�����[�^(�p�����g���b�N�������p)
const float		  CStalkingBot::DEFAULT_AMPLITUDE = 10.0f;						//�f�B�t�H���g�̊g�嗦
const D3DXVECTOR3 CStalkingBot::DEFAULT_RELATIVE_POS = {0.0f, 50.0f, 0.0f};		//�f�B�t�H���g�̑��Έʒu


//�R���X�g���N�^
CStalkingBot::CStalkingBot()
{

}

//�f�X�g���N�^
CStalkingBot::~CStalkingBot()
{

}

//����������
HRESULT CStalkingBot::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CFogbot::Init()))
	{
		return -1;
	}

	return S_OK;
}

//�I������
void CStalkingBot::Uninit(void)
{
	//��{�N���X�̏I������
	CFogbot::Uninit();
}

//�X�V����
void CStalkingBot::Update(void)
{
	//��{�N���X�̍X�V����
	CFogbot::Update();
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CStalkingBot* CStalkingBot::Create(const D3DXVECTOR3 pos, const float fShadowHeight)
{
	CStalkingBot* pBot = new CStalkingBot;			//�C���X�^���X�𐶐�����

	//����������
	if (FAILED(pBot->Init()))
	{
		return nullptr;
	}

	pBot->CreateDefaultBot();				//�f�B�t�H���g�̃{�b�g�̐�������

	pBot->SetPos(pos);						//�ʒu�̐ݒ�
	pBot->SetShadowHeight(fShadowHeight);	//�e��Y���W�̐ݒ�


	return pBot;							//���������C���X�^���X��Ԃ�
}

CStalkingBot* CStalkingBot::Create(const D3DXVECTOR3 pos, const float fShadowHeight, const float fStartAngle)
{
	CStalkingBot* pBot = new CStalkingBot;			//�C���X�^���X�𐶐�����

													//����������
	if (FAILED(pBot->Init()))
	{
		return nullptr;
	}

	pBot->CreateDefaultBot();				//�f�B�t�H���g�̃{�b�g�̐�������

	pBot->SetPos(pos);						//�ʒu�̐ݒ�
	pBot->SetShadowHeight(fShadowHeight);	//�e��Y���W�̐ݒ�


	return pBot;							//���������C���X�^���X��Ԃ�
}