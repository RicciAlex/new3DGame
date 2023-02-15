//=============================================================================
//
// icicle.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "icicle.h"
#include "CylinderHitbox.h"


//=============================================================================
//								�ÓI�ϐ��̏�����	
//=============================================================================
const D3DXVECTOR3 CIcicle::DEFAULT_DAMAGE_HITBOX_SIZE = {25.0f, 50.0f, 25.0f };			//�f�B�t�H���g�̃_���[�W��^����q�b�g�{�b�N�X�̃T�C�Y
const D3DXVECTOR3 CIcicle::DEFAULT_BODY_HITBOX_SIZE = {25.0f, 125.0f, 25.0f};			//�f�B�t�H���g�̃_���[�W��^���Ȃ��q�b�g�{�b�N�X�̃T�C�Y
const float		  CIcicle::DEFAULT_STARTING_SCALE = 0.1f;								//�f�B�t�H���g�̏��߂̃X�P�[��
const float		  CIcicle::DEFAULT_MAX_SCALE = 2.5f;									//�f�B�t�H���g�̍ő�̃X�P�[��
const float		  CIcicle::DEFAULT_SCALE_INCREMENT = 0.1f;								//���Z����Ă���X�P�[���̒l
const float		  CIcicle::DEFAULT_APLHA_INCREMENT = 0.02f;								//���Z����Ă��郿�l�̒l
const int		  CIcicle::DEFAULT_DELAY = 120;											//�f�B�t�H���g�̃f�B���C


//�R���X�g���N�^
CIcicle::CIcicle()
{
	//��{�N���X���N���A����
	m_nDelay = 0;
	m_nCntDelay = 0;
	m_fAlpha = 0.0f;

	m_pDamageHitbox = nullptr;
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CIcicle::~CIcicle()
{

}

//����������
HRESULT CIcicle::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	m_nDelay = DEFAULT_DELAY;
	m_fAlpha = 1.0f;
	SetPriority(4);

	return S_OK;
}

//�I������
void CIcicle::Uninit(void)
{
	//�q�b�g�{�b�N�X�̏I������
	if (m_pDamageHitbox)
	{//null�`�F�b�N

		m_pDamageHitbox->Release();			//���������������
		m_pDamageHitbox = nullptr;			//�|�C���^��null�ɂ���
	}
	if (m_pHitbox)
	{//null�`�F�b�N

		m_pHitbox->Release();				//���������������
		m_pHitbox = nullptr;				//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CModel::Uninit();
}

//�X�V����
void CIcicle::Update(void)
{
	float fScale = GetScale();		//�X�P�[���̎擾

	if (fScale < DEFAULT_MAX_SCALE)
	{
		fScale += DEFAULT_SCALE_INCREMENT;

		SetScale(fScale);
	}
	else
	{
		m_nCntDelay++;

		if (m_nCntDelay >= DEFAULT_DELAY)
		{
			if (m_fAlpha > 0.0f)
			{
				m_fAlpha -= DEFAULT_APLHA_INCREMENT;

				SetModelColor(0, D3DXCOLOR(0.8f, 0.8f, 0.8f, m_fAlpha));
			}
			else
			{
				Release();
				return;
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
CIcicle* CIcicle::Create(const D3DXVECTOR3 pos)
{
	CIcicle* pIcicle = new CIcicle;				//�C���X�^���X�𐶐�����

	//����������
	if (FAILED(pIcicle->Init()))
	{
		return nullptr;
	}

	pIcicle->SetPos(pos);							//�ʒu�̐ݒ�
	pIcicle->SetModel(CModel::MODEL_ICICLE);		//���f���̐ݒ�
	pIcicle->SetScale(DEFAULT_STARTING_SCALE);		//�X�P�[���̐ݒ�
	pIcicle->SetShadowDraw(false);					//�e��`�悵�Ȃ��悤�ɐݒ肷��

	//�q�b�g�{�b�N�X�̐�������
	pIcicle->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, DEFAULT_BODY_HITBOX_SIZE, CHitbox::TYPE_NEUTRAL, pIcicle);
	pIcicle->m_pDamageHitbox = CCylinderHitbox::Create(pos + D3DXVECTOR3(0.0f, DEFAULT_BODY_HITBOX_SIZE.y, 0.0f), Vec3Null, 
									DEFAULT_DAMAGE_HITBOX_SIZE, CHitbox::TYPE_OBSTACLE, -1, pIcicle, CHitbox::EFFECT_BOUNCE);

	return pIcicle;
}