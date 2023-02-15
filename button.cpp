//=============================================================================
//
// button.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "button.h"
#include "CylinderHitbox.h"
#include "application.h"
#include "sound.h"

//�R���X�g���N�^
CButton::CButton()
{
	//�����o�[�ϐ����N���A����
	m_originalPos = Vec3Null;
	m_normalCol = ColorNull;
	m_triggeredCol = ColorNull;
	m_bTriggered = false;
	m_bOnce = false;
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CButton::~CButton()
{

}


//����������
HRESULT CButton::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ�������������
	m_originalPos = Vec3Null;
	m_normalCol = ColorRed;
	m_triggeredCol = ColorGreen;
	m_bTriggered = false;
	m_bOnce = false;
	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CButton::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j��
	if (m_pHitbox)
	{//null�`�F�b�N
		m_pHitbox->Release();		//���������������
		m_pHitbox = false;			//�|�C���^��null�ɂ���
	}
}

//�X�V����
void CButton::Update(void)
{
	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox)
	{//null�`�F�b�N

		if (!m_bOnce)
		{
			if (m_pHitbox->GetCollisionState())
			{//�����Ɠ���������

				m_pHitbox->SetCollisionState(false);			//�����Ă��Ȃ���Ԃɖ߂�

				m_bTriggered = true;				//�����ꂽ��Ԃɂ���
				SetModelColor(0, m_triggeredCol);	//�F��ύX����
				SetPos(m_originalPos + D3DXVECTOR3(0.0f, -9.0f, 0.0f));			//�ʒu���X�V����

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BUTTON);
			}
			else
			{//�����Ă��Ȃ���Ԃ�������

				m_bTriggered = false;				//������Ă��Ȃ���Ԃɖ߂�
				SetModelColor(0, m_normalCol);		//�F��ύX����
				SetPos(m_originalPos);				//�ʒu���X�V����
			}
		}
		else
		{//��񂾂��������Ƃ��ł�����

			if (!m_bTriggered)
			{//�܂�������Ă��Ȃ���Ԃ�������

				if (m_pHitbox->GetCollisionState())
				{//�����Ɠ���������

					m_pHitbox->SetCollisionState(false);			//�����Ă��Ȃ���Ԃɖ߂�

					m_bTriggered = true;				//�����ꂽ��Ԃɂ���
					SetModelColor(0, m_triggeredCol);	//�F��ύX����
					SetPos(m_originalPos + D3DXVECTOR3(0.0f, -9.0f, 0.0f));			//�ʒu���X�V����

					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BUTTON);
				}
			}
		}
	}
}

//��񂾂��������Ƃ��ł��邩�ǂ����̐ݒ菈��
void CButton::SetTriggerableOnce(const bool bOnce)
{
	m_bOnce = bOnce;
}

//�����ꂽ���ǂ����̎擾����
bool CButton::GetTrigger(void)
{
	return m_bTriggered;
}




//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CButton* CButton::Create(const D3DXVECTOR3 pos)
{
	CButton* pButton = new CButton;					//�C���X�^���X�𐶐�����

	if (FAILED(pButton->Init()))
	{//����������
		return nullptr;
	}

	pButton->SetPos(pos);							//�ʒu�̐ݒ�
	pButton->m_originalPos = pos;					//���̈ʒu�̐ݒ�
	pButton->SetModel(CModel::MODEL_BUTTON);		//���f���̐ݒ�
	pButton->m_normalCol = ColorRed;				//���ʂ̐F�̐ݒ�
	pButton->m_triggeredCol = ColorGreen;			//�����ꂽ��̐F�̐ݒ�
	pButton->SetShadowDraw(false);					//�e��`�悵�Ȃ��悤�ɂ���

	//�q�b�g�{�b�N�X�̐���
	pButton->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(50.0f, 10.0f, 50.0f), CHitbox::TYPE_BUTTON, pButton);
	pButton->m_pHitbox->IgnoreAllCollision();
	pButton->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);

	return pButton;									//���������C���X�^���X��Ԃ�
}	

//��������
CButton* CButton::Create(const D3DXVECTOR3 pos, const D3DXCOLOR normalCol, const D3DXCOLOR pressedCol)
{
	CButton* pButton = new CButton;					//�C���X�^���X�𐶐�����

	if (FAILED(pButton->Init()))
	{//����������
		return nullptr;
	}

	pButton->SetPos(pos);							//�ʒu�̐ݒ�
	pButton->m_originalPos = pos;					//���̈ʒu�̐ݒ�
	pButton->SetModel(CModel::MODEL_BUTTON);		//���f���̐ݒ�
	pButton->SetModelColor(0, normalCol);			//�F�̐ݒ�
	pButton->m_normalCol = normalCol;				//���ʂ̐F�̐ݒ�
	pButton->m_triggeredCol = pressedCol;			//�����ꂽ��̐F�̐ݒ�
	pButton->SetShadowDraw(false);					//�e��`�悵�Ȃ��悤�ɂ���

	//�q�b�g�{�b�N�X�̐���
	pButton->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(50.0f, 10.0f, 50.0f), CHitbox::TYPE_BUTTON, pButton);
	pButton->m_pHitbox->IgnoreAllCollision();
	pButton->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);

	return pButton;									//���������C���X�^���X��Ԃ�
}