//=============================================================================
//
// fallBoard.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "fallBoard.h"
#include "BoxHitbox.h"
#include "application.h"
#include "sound.h"

//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================
const float CFallBoard::DEFAULT_FALL_ACCELERATION = -1.5f;										//�f�B�t�H���g�̗�������
const D3DXVECTOR3 CFallBoard::DEFAULT_BOARD_SIZE = D3DXVECTOR3(50.0f, 10.0f, 25.0f);			//�f�B�t�H���g�̃��f���T�C�Y

//�R���X�g���N�^
CFallBoard::CFallBoard()
{
	//�����o�[�ϐ����N���A����
	m_startingPos = Vec3Null;
	m_nCntFall = 0;
	m_nFallDelay = 0;
	m_fFallSpeed = 0.0f;
	m_bFall = false;

	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CFallBoard::~CFallBoard()
{
	
}

//����������
HRESULT CFallBoard::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ�������������
	m_startingPos = Vec3Null;
	m_nCntFall = 0;
	m_nFallDelay = DEFAULT_FALL_DELAY;
	m_fFallSpeed = 0.0f;
	m_bFall = false;

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CFallBoard::Uninit(void)
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
void CFallBoard::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	if (m_pHitbox)
	{
		m_pHitbox->SetPos(pos);

		if (m_pHitbox->GetCollisionState())
		{
			m_pHitbox->SetCollisionState(false);

			if (!m_bFall && m_fFallSpeed <= 0.0f)
			{
				m_bFall = true;
			}
		}
	}

	if (m_bFall)
	{
		m_nCntFall++;

		if (m_nCntFall < m_nFallDelay)
		{
			pos.x += 0.5f * sinf(D3DX_PI * 0.25f * m_nCntFall);
		}
		else
		{
			if (m_nCntFall == m_nFallDelay)
			{
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FALL_WHISTLE);
			}

			m_fFallSpeed += DEFAULT_FALL_ACCELERATION;

			if (pos.y <= m_startingPos.y - 1500.0f)
			{
				pos.x = m_startingPos.x;
				pos.y = m_startingPos.y - 1500.0f;

				m_bFall = false;
				m_fFallSpeed = 4.0f;
				m_nCntFall = 0;
			}
		}
	}

	pos.y += m_fFallSpeed;

	if (pos.y >= m_startingPos.y)
	{
		pos.y = m_startingPos.y;
		m_fFallSpeed = 0.0f;
	}

	SetPos(pos);
}




//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CFallBoard* CFallBoard::Create(const D3DXVECTOR3 pos)
{
	CFallBoard* pBoard = new CFallBoard;			//�C���X�^���X�𐶐�����

	if (FAILED(pBoard->Init()))
	{//����������
		return nullptr;
	}

	pBoard->SetPos(pos);			//�ʒu�̐ݒ�
	pBoard->m_startingPos = pos;	//���Ƃ̈ʒu�̐ݒ�

	pBoard->SetModel(CModel::MODEL_WOODEN_BOARD);		//���f���̐ݒ�
	pBoard->SetScale(2.0f);								//�X�P�[���̐ݒ�
	pBoard->SetShadowDraw(false);						//�e��`�悵�Ȃ��悤�ɐݒ肷��

	D3DXVECTOR3 size = D3DXVECTOR3(DEFAULT_BOARD_SIZE.x * 2.0f, DEFAULT_BOARD_SIZE.y * 2.0f, DEFAULT_BOARD_SIZE.z * 2.0f);		//�q�b�g�{�b�N�X�̃T�C�Y

	pBoard->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, size, CHitbox::TYPE_NEUTRAL, pBoard);		//�q�b�g�{�b�N�X�̐���

	return pBoard;				//���������C���X�^���X��Ԃ�
}

//��������
CFallBoard * CFallBoard::Create(const D3DXVECTOR3 pos, const int nFallDelay)
{
	CFallBoard* pBoard = new CFallBoard;			//�C���X�^���X�𐶐�����

	if (FAILED(pBoard->Init()))
	{//����������
		return nullptr;
	}

	pBoard->SetPos(pos);					//�ʒu�̐ݒ�
	pBoard->m_startingPos = pos;			//���Ƃ̈ʒu�̐ݒ�
	pBoard->m_nFallDelay = nFallDelay;		//��������܂ł̃t���[�����̐ݒ�

	pBoard->SetModel(CModel::MODEL_WOODEN_BOARD);		//���f���̐ݒ�
	pBoard->SetScale(2.0f);								//�X�P�[���̐ݒ�
	pBoard->SetShadowDraw(false);						//�e��`�悵�Ȃ��悤�ɐݒ肷��

	D3DXVECTOR3 size = D3DXVECTOR3(DEFAULT_BOARD_SIZE.x * 2.0f, DEFAULT_BOARD_SIZE.y * 2.0f, DEFAULT_BOARD_SIZE.z * 2.0f);		//�q�b�g�{�b�N�X�̃T�C�Y

	pBoard->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, size, CHitbox::TYPE_NEUTRAL, pBoard);		//�q�b�g�{�b�N�X�̐���

	return pBoard;				//���������C���X�^���X��Ԃ�
}
