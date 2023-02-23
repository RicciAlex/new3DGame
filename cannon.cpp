//=============================================================================
//
// cannon.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "cannon.h"
#include "button.h"
#include "BoxHitbox.h"
#include "cannonBullet.h"
#include "boss.h"
#include "application.h"
#include "sound.h"


//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================
const D3DXVECTOR3 CCannon::HITBOX_SIZE = { 90.0f, 125.0f, 125.0f };			//�q�b�g�{�b�N�X�̃T�C�Y


//�R���X�g���N�^
CCannon::CCannon()
{
	//�����o�[�ϐ����N���A����
	m_bFired = false;

	m_pButton = nullptr;
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CCannon::~CCannon()
{

}

//����������
HRESULT CCannon::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	SetModel(CModel::MODEL_CANNON);

	return S_OK;
}

//�I������
void CCannon::Uninit(void)
{
	//�{�^���̔j������
	if(m_pButton)
	{//null�`�F�b�N
		m_pButton->Release();		//���������������
		m_pButton = nullptr;		//�|�C���^��null�ɂ���
	}

	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox)
	{//null�`�F�b�N
		m_pHitbox->Release();		//���������������
		m_pHitbox = nullptr;		//�|�C���^��null�ɂ���
	}

	if (m_pBoss)
	{//null�`�F�b�N
		m_pBoss = nullptr;			//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V����
void CCannon::Update(void)
{
	if (m_pButton && m_pBoss)
	{
		if (!m_bFired)
		{
			if (m_pButton->GetTrigger())
			{
				CCannonBullet::Create(GetPos(), m_pBoss);			//�e�̐���
				m_bFired = true;
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CANNON);
			}
		}
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
CCannon* CCannon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 buttonPos, CBoss* pBoss)
{
	CCannon* pCannon = new CCannon;			//�C���X�^���X�𐶐�����

	if (FAILED(pCannon->Init()))
	{//����������

		return nullptr;
	}

	pCannon->SetPos(pos);		//�ʒu�̐ݒ�
	pCannon->SetRot(rot);		//�����̐ݒ�
	pCannon->SetShadowHeight(pos.y + 0.1f);		//�e�̈ʒu�̐ݒ�
	pCannon->m_pBoss = pBoss;	//�{�X�ւ̃|�C���^�̐ݒ�

	pCannon->m_pButton = CButton::Create(buttonPos, true);			//�{�^���𐶐�����

	pCannon->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, HITBOX_SIZE, CHitbox::TYPE_NEUTRAL, pCannon);		//�q�b�g�{�b�N�X�̐���

	return pCannon;				//���������C���X�^���X��Ԃ�
}