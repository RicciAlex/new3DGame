//=============================================================================
//
// fogEffect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "fogEffect.h"

//=============================================================================
//									�ÓI�ϐ��̏�����
//=============================================================================
const D3DXVECTOR2 CFogEffect::DEFAULT_SIZE = D3DXVECTOR2(10.0f, 10.0f);
const int		  CFogEffect::DEFAULT_LIFE = 90;
const D3DXCOLOR   CFogEffect::DEFAULT_COLOR = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.5f);


//�R���X�g���N�^
CFogEffect::CFogEffect()
{

}

//�f�X�g���N�^
CFogEffect::~CFogEffect()
{

}

//����������
HRESULT CFogEffect::Init(void)
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

	m_fAcceleration = (float)random(-100, 100) * 0.00075f;

	return S_OK;
}

//�I������
void CFogEffect::Uninit(void)
{
	//��{�N���X�̏I������
	CEffect::Uninit();
}

//�X�V����
void CFogEffect::Update(void)
{
	D3DXVECTOR3 move = GetMove();

	move.x += m_fAcceleration;

	SetMove(move);

	//��{�N���X�̍X�V����
	CEffect::Update();
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CFogEffect* CFogEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CFogEffect* pEffect = new CFogEffect;				//�C���X�^���X�𐶐�����

	if (FAILED(pEffect->Init()))
	{//����������
		return nullptr;
	}

	pEffect->SetPos(pos);				//�ʒu�̐ݒ�
	pEffect->SetMove(move);				//���x�̐ݒ�

	return pEffect;						//���������C���X�^���X��Ԃ�
}