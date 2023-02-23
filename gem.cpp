//=============================================================================
//
// gem.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "gem.h"
#include "BoxHitbox.h"
#include "application.h"
#include "game.h"
#include "goal.h"
#include "sound.h"


//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================
const float CGem::DEFAULT_SCALE = 1.75f;			//�f�B�t�H���g�̃X�P�[���̌W��
const D3DXVECTOR3 CGem::DEFAULT_ROTATION = { 0.0f, -D3DX_PI * 0.005f, 0.0f };		//�f�B�t�H���g�̉�]���x
const D3DXVECTOR3 CGem::DEFAULT_SIZE = { 25.0f, 50.0f, 25.0f };		//�f�B�t�H���g�̃T�C�Y


//�R���X�g���N�^
CGem::CGem()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CGem::~CGem()
{

}

//����������
HRESULT CGem::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CModel::Init()))
	{
		return 1;
	}

	SetModel(CModel::MODEL_JEWEL);			//���f���̐ݒ�
	SetScale(DEFAULT_SCALE);				//�X�P�[���̐ݒ�
	StartRotation(DEFAULT_ROTATION);		//��]�̐ݒ�

	return S_OK;
}

//�I������
void CGem::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox)
	{//null�`�F�b�N

		m_pHitbox->Release();		//���������������
		m_pHitbox = nullptr;		//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V����
void CGem::Update(void)
{
	//��{�N���X�̍X�V����
	CModel::Update();

	if (m_pHitbox)
	{
		if (m_pHitbox->GetCollisionState())
		{
			if (D3DXVec3Length(&m_newPos) > 0.0f)
			{
				m_pHitbox->Release();
				m_pHitbox = nullptr;

				SetPos(m_newPos);
				SetScale(0.8f);
				SetShadowDraw(false);
				CApplication::GetGame()->GetGoal()->SubtractGem();
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_GEM);
			}
			else
			{
				Release();
				return;
			}
		}
	}
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CGem * CGem::Create(const D3DXVECTOR3 pos)
{
	CGem* pGem = new CGem;			//�C���X�^���X�𐶐�����

	if (FAILED(pGem->Init()))
	{//����������
		return nullptr;
	}

	pGem->SetPos(pos);				//�ʒu�̐ݒ�

	//�q�b�g�{�b�N�X�̐�������
	pGem->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, D3DXVECTOR3(DEFAULT_SIZE), CHitbox::TYPE_VANISHING, pGem, 1);

	if (pGem->m_pHitbox)
	{//null�`�F�b�N
		pGem->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);	//�v���C���[�̃q�b�g�{�b�N�X�Əd�Ȃ邱�Ƃ��ł���悤�ɂ���
	}

	CApplication::GetGame()->GetGoal()->AddGem();

	return pGem;					//���������C���X�^���X��Ԃ�
}

CGem * CGem::Create(const D3DXVECTOR3 pos, const D3DXCOLOR col)
{
	CGem* pGem = new CGem;			//�C���X�^���X�𐶐�����

	if (FAILED(pGem->Init()))
	{//����������
		return nullptr;
	}

	pGem->SetPos(pos);				//�ʒu�̐ݒ�
	pGem->SetModelColor(1, col);	//�F�̐ݒ�

	//�q�b�g�{�b�N�X�̐�������
	pGem->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, D3DXVECTOR3(DEFAULT_SIZE), CHitbox::TYPE_VANISHING, pGem, 1);

	if (pGem->m_pHitbox)
	{//null�`�F�b�N
		pGem->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);	//�v���C���[�̃q�b�g�{�b�N�X�Əd�Ȃ邱�Ƃ��ł���悤�ɂ���
	}

	CApplication::GetGame()->GetGoal()->AddGem();

	return pGem;					//���������C���X�^���X��Ԃ�
}

CGem * CGem::Create(const D3DXVECTOR3 pos, const D3DXCOLOR col, const float fShadowHeight)
{
	CGem* pGem = new CGem;			//�C���X�^���X�𐶐�����

	if (FAILED(pGem->Init()))
	{//����������
		return nullptr;
	}

	pGem->SetPos(pos);				//�ʒu�̐ݒ�
	pGem->SetModelColor(1, col);	//�F�̐ݒ�
	pGem->SetShadowHeight(fShadowHeight);		//�e��Y���W�̐ݒ�

	//�q�b�g�{�b�N�X�̐�������
	pGem->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, D3DXVECTOR3(DEFAULT_SIZE), CHitbox::TYPE_VANISHING, pGem, 1);

	if (pGem->m_pHitbox)
	{//null�`�F�b�N
		pGem->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);	//�v���C���[�̃q�b�g�{�b�N�X�Əd�Ȃ邱�Ƃ��ł���悤�ɂ���
	}

	CApplication::GetGame()->GetGoal()->AddGem();

	return pGem;					//���������C���X�^���X��Ԃ�
}

CGem * CGem::Create(const D3DXVECTOR3 pos, const D3DXCOLOR col, const float fShadowHeight, const D3DXVECTOR3 newPos, CGoal* pGoal)
{
	CGem* pGem = new CGem;			//�C���X�^���X�𐶐�����

	if (FAILED(pGem->Init()))
	{//����������
		return nullptr;
	}

	pGem->SetPos(pos);				//�ʒu�̐ݒ�
	pGem->SetModelColor(1, col);	//�F�̐ݒ�
	pGem->SetShadowHeight(fShadowHeight);		//�e��Y���W�̐ݒ�
	pGem->m_newPos = newPos;		//�V�����ʒu�̐ݒ�

												//�q�b�g�{�b�N�X�̐�������
	pGem->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, D3DXVECTOR3(DEFAULT_SIZE), CHitbox::TYPE_VANISHING, pGem, 1);

	if (pGem->m_pHitbox)
	{//null�`�F�b�N
		pGem->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);	//�v���C���[�̃q�b�g�{�b�N�X�Əd�Ȃ邱�Ƃ��ł���悤�ɂ���
	}

	pGoal->AddGem();

	return pGem;					//���������C���X�^���X��Ԃ�
}
