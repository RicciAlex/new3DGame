//=============================================================================
//
// magicCircleEffect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "magicCircleEffect.h"

//=============================================================================
//								�ÓI�ϐ��̏�����
//=============================================================================
const D3DXVECTOR2 CMagicCircleEffect::DEFAULT_SIZE = {100.0f, 100.0f};			//�f�B�t�H���g�̃T�C�Y


//�R���X�g���N�^
CMagicCircleEffect::CMagicCircleEffect()
{

}

//�f�X�g���N�^
CMagicCircleEffect::~CMagicCircleEffect()
{

}

//����������
HRESULT CMagicCircleEffect::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_3D::Init()))
	{
		return -1;
	}

	SetTexture(CObject::TEXTURE_MAGIC_CIRCLE_EFFECT);				//�e�N�X�`���̐ݒ�
	SetSize(DEFAULT_SIZE);											//�T�C�Y�̐ݒ�
	SetRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.0025f, 0.0f));		//��]�̐ݒ�
	SetStartingRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));		//�������̉�]�̐ݒ�

	return S_OK;
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CMagicCircleEffect* CMagicCircleEffect::Create(const D3DXVECTOR3 pos)
{
	CMagicCircleEffect* pEffect = new CMagicCircleEffect;				//�C���X�^���X�𐶐�����

	if (FAILED(pEffect->Init()))
	{//����������
		return nullptr;
	}

	pEffect->SetPos(pos);			//�ʒu�̐ݒ�

	return pEffect;					//���������C���X�^���X��Ԃ�
}