//=============================================================================
//
// spikeTrap.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "stalkingBot.h"
#include "player.h"
#include "application.h"
#include "game.h"


//=============================================================================
//								�ÓI�ϐ��̏�����
//=============================================================================
const float		  CStalkingBot::DEFAULT_APPROACHING_SPEED = 10.0f;				//�f�B�t�H���g�̒ǂ������鑬�x
const float		  CStalkingBot::DEFAULT_ANGLE_SPEED = D3DX_PI * 0.01f;			//�f�B�t�H���g�̉�]���x
const float		  CStalkingBot::DEFAULT_FIRST_COEFF = 5.0f;						//�f�B�t�H���g�̍ŏ��̃p�����[�^(�p�����g���b�N�������p)
const float		  CStalkingBot::DEFAULT_SECOND_COEFF = 3.0f;					//�f�B�t�H���g�̓�Ԗڂ̃p�����[�^(�p�����g���b�N�������p)
const float		  CStalkingBot::DEFAULT_AMPLITUDE = 30.0f;						//�f�B�t�H���g�̊g�嗦
const float		  CStalkingBot::DEFAULT_ACTIVATION_DISTANCE = 1000.0f;			//�f�B�t�H���g�̃A�N�e�B�u��ԂɂȂ鋗��
const float	      CStalkingBot::DEFAULT_CIRCLE_RANGE = 200.0f;					//�f�B�t�H���g�̉~�`�̔��a
const float		  CStalkingBot::DEFAULT_MAX_STAR_ANGLE = D3DX_PI * 12.0f;		//�f�B�t�H���g�̍ő�p�x(���̊p�x�𒴂�����A�������ԂɂȂ�)
const float		  CStalkingBot::DEFAULT_RUN_DISTANCE = 3000.0f;					//�f�B�t�H���g�̓����鋗��
const D3DXVECTOR3 CStalkingBot::DEFAULT_RELATIVE_POS = {0.0f, 50.0f, 0.0f};		//�f�B�t�H���g�̑��Έʒu


//�R���X�g���N�^
CStalkingBot::CStalkingBot()
{
	//�����o�[�ϐ����N���A����
	m_center = Vec3Null;
	m_move = Vec3Null;
	m_fPresentAngle = 0.0f;
	m_fStarRange = 0.0f;

	m_state = (State)0;
}

//�f�X�g���N�^
CStalkingBot::~CStalkingBot()
{

}

//����������
HRESULT CStalkingBot::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CFogbot::Init()))
	{
		return -1;
	}
	
	//�����o�[�ϐ�������������
	m_center = Vec3Null;
	m_move = Vec3Null;
	m_fPresentAngle = 0.0f;
	m_fStarRange = DEFAULT_CIRCLE_RANGE / DEFAULT_FIRST_COEFF;

	m_state = (State)0;

	return S_OK;
}

//�I������
void CStalkingBot::Uninit(void)
{
	//��{�N���X�̏I������
	CFogbot::Uninit();
}

//�X�V����
void CStalkingBot::Update(void)
{
	//��{�N���X�̍X�V����
	CFogbot::Update();

	//��Ԃɂ���Ă̍X�V����
	StateUpdate();
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CStalkingBot* CStalkingBot::Create(const D3DXVECTOR3 pos, const float fShadowHeight)
{
	CStalkingBot* pBot = new CStalkingBot;			//�C���X�^���X�𐶐�����

	//����������
	if (FAILED(pBot->Init()))
	{
		return nullptr;
	}

	pBot->CreateDefaultBot();				//�f�B�t�H���g�̃{�b�g�̐�������

	pBot->SetPos(pos);						//�ʒu�̐ݒ�
	pBot->SetShadowHeight(fShadowHeight);	//�e��Y���W�̐ݒ�

	return pBot;							//���������C���X�^���X��Ԃ�
}

CStalkingBot* CStalkingBot::Create(const D3DXVECTOR3 pos, const float fShadowHeight, const float fStartAngle)
{
	CStalkingBot* pBot = new CStalkingBot;			//�C���X�^���X�𐶐�����

													//����������
	if (FAILED(pBot->Init()))
	{
		return nullptr;
	}

	pBot->CreateDefaultBot();				//�f�B�t�H���g�̃{�b�g�̐�������

	pBot->SetPos(pos);						//�ʒu�̐ݒ�
	pBot->SetShadowHeight(fShadowHeight);	//�e��Y���W�̐ݒ�


	return pBot;							//���������C���X�^���X��Ԃ�
}



//=============================================================================
//
//								�v���C�x�[�g�֐�
//
//=============================================================================




//��Ԃɂ���Ă̍X�V����
void CStalkingBot::StateUpdate(void)
{
	switch (m_state)
	{

	case CStalkingBot::STATE_WAIT:

	{
		Activate();				//�A�N�e�B�u��ԂɂȂ������ǂ����̔���̏���
	}

		break;

	case CStalkingBot::STATE_FOLLOW:

	{
		FollowPlayer();			//�v���C���[��ǂ�������
	}

		break;

	case CStalkingBot::STATE_CIRCLE:

	{
		CirclePlayer();			//�v���C���[�𒆐S�ɂ��āA���]����
	}

		break;

	case CStalkingBot::STATE_STAR:

	{
		StarCircling();			//���̌`�ɓ�����
	}

		break;

	case CStalkingBot::STATE_RUN:

	{
		RunAway();				//�����鏈��
	}

		break;
	
	default:
		break;
	}
}

//�A�N�e�B�u��ԂɂȂ������ǂ����̔���̏���
bool CStalkingBot::Activate(void)
{
	D3DXVECTOR3 playerPos = CApplication::GetGame()->GetPlayer()->GetPos();		//�v���C���[�̈ʒu�̎擾
	D3DXVECTOR3 distance = playerPos - GetPos();								//�v���C���[�Ƃ̋������v�Z����

	if (D3DXVec3Length(&distance) <= DEFAULT_ACTIVATION_DISTANCE)
	{
		D3DXVECTOR3 move = Vec3Null;			//���x

		m_state = STATE_FOLLOW;					//�ǂ��������Ԃɂ���

		//���x�̌v�Z�Ɛݒ�
		D3DXVec3Normalize(&move, &distance);
		move.x *= DEFAULT_APPROACHING_SPEED;
		move.y *= DEFAULT_APPROACHING_SPEED;
		move.z *= DEFAULT_APPROACHING_SPEED;

		m_move = move;

		return true;
	}

	return false;
}

//�v���C���[��ǂ������鏈��
void CStalkingBot::FollowPlayer(void)
{
	SetPos(GetPos() + m_move);					//�ʒu�̍X�V�Ɛݒ�

	D3DXVECTOR3 playerPos = CApplication::GetGame()->GetPlayer()->GetPos();		//�v���C���[�̈ʒu�̎擾
	D3DXVECTOR3 distance = GetPos() - playerPos;								//�v���C���[�Ƃ̋������v�Z����

	if (D3DXVec3Length(&distance) <= DEFAULT_CIRCLE_RANGE)
	{
		D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);		//�P�ʃx�N�g��
		D3DXVECTOR3 N = Vec3Null;								//���K����������
		float fAngle = 0.0f;									//�͂��߂̎��̊p�x

		m_move = Vec3Null;								//���x��0�ɂ���
		m_state = STATE_CIRCLE;							//��Ԃ��X�V����
		m_center = playerPos + DEFAULT_RELATIVE_POS;	//���S�_��ݒ肷��

		distance.y = 0.0f;
		D3DXVec3Normalize(&N, &distance);				//���K����������
		float fDot = D3DXVec3Dot(&unit, &N);
		fAngle = acosf(fDot);			//�P�ʃx�N�g���ƓG����v���C���[�܂ł̃x�N�g���̊Ԃ̊p�x���v�Z����

		if (playerPos.z > GetPos().z)
		{//�K�v��������A���K������

			fAngle *= -1.0f;
		}

		m_fPresentAngle = fAngle;

		ForceActivation();		//�p�[�e�B�N�����A�N�e�B�u��Ԃɂ���
	}
	else
	{
		D3DXVECTOR3 move = Vec3Null;			//���x

		m_state = STATE_FOLLOW;					//�ǂ��������Ԃɂ���

		//���x�̌v�Z�Ɛݒ�
		D3DXVec3Normalize(&move, &distance);
		move.x *= -DEFAULT_APPROACHING_SPEED;
		move.y = 0.0f;
		move.z *= -DEFAULT_APPROACHING_SPEED;

		m_move = move;
	}
}

//�v���C���[�𒆐S�ɂ��āA���]����
void CStalkingBot::CirclePlayer(void)
{
	D3DXVECTOR3 pos = GetPos();					//�ʒu�̎擾
	D3DXVECTOR3 playerPos = CApplication::GetGame()->GetPlayer()->GetPos();		//�v���C���[�̈ʒu�̎擾

	m_center = playerPos + DEFAULT_RELATIVE_POS;	//���S�_�̍X�V

	m_fPresentAngle += DEFAULT_ANGLE_SPEED;			//���݂̊p�x�̍X�V

	//�ʒu�̍X�V�Ɛݒ�
	pos.x = m_center.x + (DEFAULT_CIRCLE_RANGE) * cosf(m_fPresentAngle);
	pos.z = m_center.z + (DEFAULT_CIRCLE_RANGE) * sinf(m_fPresentAngle);

	if (D3DX_PI * 2.0f - m_fPresentAngle < DEFAULT_ANGLE_SPEED)
	{//���܂����Ƃ���ɂ�����

		m_fPresentAngle = 0.0f;	//���݂̊p�x��0�ɖ߂�
		m_state = STATE_STAR;	//��Ԃ��X�V����
	}

	SetPos(pos);
	
}

//���̌`�ɓ�����
void CStalkingBot::StarCircling(void)
{
	D3DXVECTOR3 pos = GetPos();					//�ʒu�̎擾
	D3DXVECTOR3 playerPos = CApplication::GetGame()->GetPlayer()->GetPos();		//�v���C���[�̈ʒu�̎擾

	m_center = playerPos + DEFAULT_RELATIVE_POS;	//���S�_�̍X�V

	m_fPresentAngle += 2.0f * DEFAULT_ANGLE_SPEED;			//���݂̊p�x�̍X�V

	float a = DEFAULT_FIRST_COEFF;		//�p�����g���b�N�������p�̌W���̐ݒ�(�f�B�t�H���g�l)
	float b = DEFAULT_SECOND_COEFF;		//�p�����g���b�N�������p�̌W���̐ݒ�(�f�B�t�H���g�l)

	float x = ((a - b) * cosf(m_fPresentAngle)) + (b * cosf(((a - b) / b) * m_fPresentAngle));
	float y = ((a - b) * sinf(m_fPresentAngle)) - (b * sinf(((a - b) / b) * m_fPresentAngle));

	//�ʒu�̍X�V�Ɛݒ�
	pos.x = m_center.x + (m_fStarRange) * x;
	pos.z = m_center.z + (m_fStarRange) * y;

	SetPos(pos);

	if (m_fPresentAngle >= DEFAULT_MAX_STAR_ANGLE)
	{//�ő�p�x�𒴂�����

		m_fPresentAngle = 0;			//���݂̊p�x��0�ɖ߂�
		m_state = STATE_RUN;			//��Ԃ̍X�V
		
		//���x�̌v�Z�Ɛݒ�
		D3DXVECTOR3 move = pos - playerPos;
		D3DXVec3Normalize(&move, &move);
		move.x *= DEFAULT_APPROACHING_SPEED;
		move.z *= DEFAULT_APPROACHING_SPEED;

		m_move = move;

		Deactivate();					//�p�[�e�B�N�����A�N�e�B�u�ł͂Ȃ���Ԃɂ���
	}
}

//�����鏈��
void CStalkingBot::RunAway(void)
{
	D3DXVECTOR3 pos = GetPos();					//�ʒu�̎擾
	D3DXVECTOR3 playerPos = CApplication::GetGame()->GetPlayer()->GetPos();		//�v���C���[�̈ʒu�̎擾

	pos += m_move;				//�ʒu�̍X�V

	D3DXVECTOR3 distance = playerPos - pos;			//�v���C���[�Ƃ̋����̌v�Z

	if (D3DXVec3Length(&distance) >= DEFAULT_RUN_DISTANCE)
	{
		Release();				//�C���X�^���X��j������
		return;
	}

	SetPos(pos);
}
