//=============================================================================
//
// triggerablePlatform.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "triggerablePlatform.h"
#include "button.h"
#include "movingCube.h"

//�R���X�g���N�^
CTriggerablePlatform::CTriggerablePlatform()
{
	//�����o�[�ϐ����N���A����
	m_move = Vec3Null;
	m_bTriggered = false;

	m_pButton = nullptr;
	m_pPlatform = nullptr;
}

//�f�X�g���N�^
CTriggerablePlatform::~CTriggerablePlatform()
{

}

//����������
HRESULT CTriggerablePlatform::Init(void)
{
	//�����o�[�ϐ�������������
	m_move = Vec3Null;
	m_bTriggered = false;

	m_pButton = nullptr;
	m_pPlatform = nullptr;

	return S_OK;
}

//�I������
void CTriggerablePlatform::Uninit(void)
{
	//�{�^���̔j��
	if (m_pButton)
	{//null�`�F�b�N
		m_pButton->Release();		//���������������
		m_pButton = nullptr;		//�|�C���^��null�ɂ���
	}

	//�v���b�g�t�H�[���̔j��
	if (m_pButton)
	{//null�`�F�b�N
		m_pButton->Release();		//���������������
		m_pButton = nullptr;		//�|�C���^��null�ɂ���
	}
}

//�X�V����
void CTriggerablePlatform::Update(void)
{
	if (m_pButton && m_pPlatform)
	{//null�`�F�b�N

		if (!m_bTriggered)
		{//�{�^�����܂�������Ă��Ȃ��ꍇ

			if (m_pButton->GetTrigger())
			{//�{�^���������ꂽ��

				m_bTriggered = true;				//�����ꂽ��Ԃɂ���

				m_pPlatform->SetMove(m_move);		//�v���b�g�t�H�[���̑��x��ݒ肷��
			}
		}
	}
}

//�`�揈��
void CTriggerablePlatform::Draw(void)
{

}

//�ʒu�̐ݒ菈��
void CTriggerablePlatform::SetPos(const D3DXVECTOR3 pos)
{
	if (m_pPlatform)
	{//null�`�F�b�N
		m_pPlatform->SetPos(pos);
	}
}

//���̈ʒu�̐ݒ菈��
void CTriggerablePlatform::SetOriginalPos(const D3DXVECTOR3 oPos)
{
	if (m_pPlatform)
	{//�v���b�g�t�H�[����null�`�F�b�N
				
		m_pPlatform->SetOriginalPos(oPos);
	}
}

//�{�^���̈ʒu�̐ݒ菈��
void CTriggerablePlatform::SetButtonPos(const D3DXVECTOR3 pos)
{
	if (m_pButton)
	{//null�`�F�b�N
		m_pButton->SetPos(pos);
	}
}

//�ʒu�̎擾����
const D3DXVECTOR3 CTriggerablePlatform::GetPos(void)
{
	if (m_pPlatform)
	{//null�`�F�b�N
		return m_pPlatform->GetPos();
	}

	return Vec3Null;
}

//�{�^���̈ʒu�̎擾����
const D3DXVECTOR3 CTriggerablePlatform::GetButtonPos(void)
{
	if (m_pButton)
	{//null�`�F�b�N
		return m_pButton->GetPos();
	}

	return Vec3Null;
}



//=============================================================================
//
// triggerablePlatform.cpp
// Author : Ricci Alex
//
//=============================================================================


//��������
CTriggerablePlatform* CTriggerablePlatform::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 buttonPos, const D3DXVECTOR3 move, const float fRange)
{
	CTriggerablePlatform* pObj = new CTriggerablePlatform;		//�C���X�^���X�𐶐�����

	if(FAILED(pObj->Init()))
	{//����������
		return nullptr;
	}

	pObj->m_move = move;			//�{�^���������ꂽ��̑��x�̐ݒ�
	pObj->m_pPlatform = CMovingCube::Create(pos, Vec3Null, fRange);		//�v���b�g�t�H�[���̐���

	if (!pObj->m_pPlatform)
	{//�����ł��Ȃ�������Anull��Ԃ�

		pObj->Release();

		return nullptr;
	}

	pObj->m_pButton = CButton::Create(buttonPos);			//�{�^���̐���

	if (!pObj->m_pButton)
	{//�����ł��Ȃ�������Anull��Ԃ�

		pObj->Release();

		return nullptr;
	}

	pObj->m_pButton->SetTriggerableOnce(true);				//��񂾂��������Ƃ��ł��邱�Ƃɂ���

	return pObj;					//���������C���X�^���X��Ԃ�
}