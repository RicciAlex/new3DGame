//=============================================================================
//
// bgModel.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bgModel.h"


//�R���X�g���N�^
CBgModel::CBgModel()
{
	//�����o�[�ϐ����N���A����
	m_move = Vec3Null;
}

//�f�X�g���N�^
CBgModel::~CBgModel()
{

}

//����������
HRESULT CBgModel::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ�������������
	m_move = Vec3Null;

	return S_OK;
}

//�I������
void CBgModel::Uninit(void)
{
	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V����
void CBgModel::Update(void)
{
	if (D3DXVec3Length(&m_move) > 0.0f)
	{//���x��0�ł͂Ȃ�������

		D3DXVECTOR3 pos = GetPos();		//�ʒu�̎擾

		pos += m_move;					//�ʒu�̍X�V

		SetPos(pos);					//�ʒu�̐ݒ�
	}

	//��{�N���X�̍X�V����
	CModel::Update();
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CBgModel* Create(CModel::ModelType type, const D3DXVECTOR3 pos)
{
	CBgModel* pModel = new CBgModel;			//�C���X�^���X�𐶐�����

	if (FAILED(pModel->Init()))
	{//����������
		return nullptr;
	}

	pModel->SetModel(type);		//���f���̐ݒ�
	pModel->SetPos(pos);		//�ʒu�̐ݒ�

	return pModel;				//���������C���X�^���X��Ԃ�
}

//��������
CBgModel* CBgModel::Create(CModel::ModelType type, const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CBgModel* pModel = new CBgModel;			//�C���X�^���X�𐶐�����

	if (FAILED(pModel->Init()))
	{//����������
		return nullptr;
	}

	pModel->SetModel(type);		//���f���̐ݒ�
	pModel->SetPos(pos);		//�ʒu�̐ݒ�
	pModel->m_move = move;		//���x�̐ݒ�

	return pModel;				//���������C���X�^���X��Ԃ�
}