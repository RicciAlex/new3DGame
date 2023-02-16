//=============================================================================
//
// twisterEffect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "twisterEffect.h"


//=============================================================================
//								�ÓI�ϐ��̏�����
//=============================================================================
const int		  CTwisterEffect::DEFAULT_LIFE = 300;			//�f�B�t�H���g�̃��C�t
const D3DXCOLOR	  CTwisterEffect::DEFAULT_COLOR = { 0.0f, 0.5f, 0.6f, 0.5f };			//�f�B�t�H���g�̐F
const D3DXVECTOR2 CTwisterEffect::DEFAULT_SIZE = {10.0f, 10.0f};			//�f�B�t�H���g�̃T�C�Y


//�R���X�g���N�^
CTwisterEffect::CTwisterEffect()
{

}

//�f�X�g���N�^
CTwisterEffect::~CTwisterEffect()
{

}

//����������
HRESULT CTwisterEffect::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CEffect::Init()))
	{
		return -1;
	}

	SetTexture(CObject::TEXTURE_CIRCLE_EFFECT);				//�e�N�X�`���̐ݒ�
	SetLife(DEFAULT_LIFE);									//���C�t�̐ݒ�
	SetColor(DEFAULT_COLOR);								//�F�̐ݒ�
	SetSize(DEFAULT_SIZE);

	return S_OK;
}

//�I������
void CTwisterEffect::Uninit(void)
{
	//��{�N���X�̏I������
	CEffect::Uninit();
}

//�X�V����
void CTwisterEffect::Update(void)
{
	//��{�N���X�̍X�V����
	CEffect::Update();
}




//��������
CTwisterEffect* CTwisterEffect::Create(const D3DXVECTOR3 pos)
{
	CTwisterEffect* pEffect = new CTwisterEffect;		//�C���X�^���X�𐶐�����

	if (FAILED(pEffect->Init()))
	{//����������
		return nullptr;
	}

	pEffect->SetPos(pos);		//�ʒu�̐ݒ�

	return pEffect;				//���������C���X�^���X��Ԃ�
}