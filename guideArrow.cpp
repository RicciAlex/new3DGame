//=============================================================================
//
// guideArrow.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "guideArrow.h"


//�R���X�g���N�^
CGuideArrow::CGuideArrow()
{

}

//�f�X�g���N�^
CGuideArrow::~CGuideArrow()
{

}

//����������
HRESULT CGuideArrow::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_3D::Init()))
	{
		return -1;
	}

	//�e�N�X�`���A�j���[�V�����p�̃p�����[�^�̐ݒ�
	SetTexture(CObject::TEXTURE_GUIDE_ARROW);
	SetTextureParameter(2, 2, 1, 45);
	SetSize(D3DXVECTOR2(25.0f, 25.0f));

	return S_OK;
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================




//��������
CGuideArrow* CGuideArrow::Create(const D3DXVECTOR3 pos)
{
	CGuideArrow* pArrow = new CGuideArrow;			//�C���X�^���X�𐶐�����

	if (FAILED(pArrow->Init()))
	{//����������
		return nullptr;
	}

	pArrow->SetPos(pos);			//�ʒu�̐ݒ�

	return pArrow;			//���������C���X�^���X��Ԃ�
}

CGuideArrow * CGuideArrow::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CGuideArrow* pArrow = new CGuideArrow;			//�C���X�^���X�𐶐�����

	if (FAILED(pArrow->Init()))
	{//����������
		return nullptr;
	}

	pArrow->SetPos(pos);			//�ʒu�̐ݒ�
	pArrow->SetStartingRot(rot);	//�����̐ݒ�

	return pArrow;			//���������C���X�^���X��Ԃ�
}
