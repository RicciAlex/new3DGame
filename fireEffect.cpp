//=============================================================================
//
// fireEffect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "fireEffect.h"

//=============================================================================
//								�ÓI�ϐ��̏�����
//=============================================================================
const D3DXVECTOR2 CFireEffect::DEFAULT_SIZE = {10.0f, 10.0f};
const D3DXVECTOR2 CFireEffect::DEFAULT_DELTA_SIZE = {0.01f, 0.01f};
const int		  CFireEffect::DEFAULT_LIFE = 60;
const D3DXCOLOR   CFireEffect::DEFAULT_COLOR = { 0.9f, 0.25f, 0.05f, 0.25f };
const D3DXCOLOR	  CFireEffect::DEFAULT_DELTA_COLOR = { 0.01f, 0.002f, 0.0f, 0.0f };


//�R���X�g���N�^
CFireEffect::CFireEffect()
{

}

//�f�X�g���N�^
CFireEffect::~CFireEffect()
{

}

//����������
HRESULT CFireEffect::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CEffect::Init()))
	{
		return -1;
	}

	SetTexture(CObject::TEXTURE_CIRCLE_EFFECT);				//�e�N�X�`���̐ݒ�
	SetSize(DEFAULT_SIZE);									//�T�C�Y�̐ݒ�
	SetLife(DEFAULT_LIFE);									//���C�t�̐ݒ�
	SetColor(DEFAULT_COLOR);								//�F�̐ݒ�

	return S_OK;
}

//�I������
void CFireEffect::Uninit(void)
{
	//��{�N���X�̏I������
	CEffect::Uninit();
}

//�X�V����
void CFireEffect::Update(void)
{
	D3DXVECTOR2 size = GetSize();

	if (size.x > DEFAULT_DELTA_SIZE.x)
	{
		size.x -= DEFAULT_DELTA_SIZE.x;
	}
	if (size.y > DEFAULT_DELTA_SIZE.y)
	{
		size.y -= DEFAULT_DELTA_SIZE.y;
	}

	SetSize(size);

	D3DXCOLOR col = GetColor();

	if (col.r > DEFAULT_DELTA_COLOR.r)
	{
		col.r -= DEFAULT_DELTA_COLOR.r;
	}
	if (col.g > DEFAULT_DELTA_COLOR.g)
	{
		col.g -= DEFAULT_DELTA_COLOR.g;
	}
	if (col.b > DEFAULT_DELTA_COLOR.b)
	{
		col.b -= DEFAULT_DELTA_COLOR.b;
	}
	if (col.a > DEFAULT_DELTA_COLOR.a)
	{
		col.a -= DEFAULT_DELTA_COLOR.a;
	}

	SetColor(col);

	//��{�N���X�̍X�V����
	CEffect::Update();
}





//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================




//��������
CFireEffect* CFireEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CFireEffect* pEffect = new CFireEffect;				//�C���X�^���X�𐶐�����

	if (FAILED(pEffect->Init()))
	{//����������
		return nullptr;
	}

	pEffect->SetPos(pos);				//�ʒu�̐ݒ�
	pEffect->SetMove(move);				//���x�̐ݒ�

	return pEffect;						//���������C���X�^���X��Ԃ�
}