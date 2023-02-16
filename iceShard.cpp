//=============================================================================
//
// iceShard.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "iceShard.h"

//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================
const float CIceShard::DEFAULT_GRAVITY_ACCELERATION = -0.8f;		//�d��


//�R���X�g���N�^
CIceShard::CIceShard()
{
	//�����o�[�ϐ����N���A����
	m_move = Vec3Null;
}

//�f�X�g���N�^
CIceShard::~CIceShard()
{

}

//����������
HRESULT CIceShard::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CModel::Init()))
	{
		return -1;
	}	

	m_nCntLife = DEFAULT_LIFE;				//���C�t�̐ݒ�
	SetModel(CModel::MODEL_ICE_SHARD);		//���f���̐ݒ�
	StartRotation(D3DXVECTOR3(D3DX_PI * 0.00025f * (float)random(-500, 500), D3DX_PI * 0.00025f * (float)random(-500, 500), 0.0f));

	return S_OK;
}

//�I������
void CIceShard::Uninit(void)
{
	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V����
void CIceShard::Update(void)
{
	//���C�t�̍X�V����
	m_nCntLife--;

	if (m_nCntLife <= 0)
	{
		Release();
		return;
	}

	m_move.y += DEFAULT_GRAVITY_ACCELERATION;
	SetPos(GetPos() + m_move);

	//��{�N���X�̍X�V����
	CModel::Update();
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CIceShard* CIceShard::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CIceShard* pShard = new CIceShard;		//�C���X�^���X�𐶐�����

	if (FAILED(pShard->Init()))
	{//����������
		return nullptr;
	}

	pShard->SetPos(pos);			//�ʒu�̐ݒ�
	pShard->m_move = move;			//���x�̐ݒ�
	pShard->SetShadowDraw(false);	//�e��`�悵�Ȃ��悤�ɐݒ肷��

	return pShard;					//���������C���X�^���X��Ԃ�
}
