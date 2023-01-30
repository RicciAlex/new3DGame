//=============================================================================
//
// spikeTrap.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef STALKING_BOT_H
#define STALKING_BOT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "fogBot.h"

//=============================================================================
//�O���錾
//=============================================================================


class CStalkingBot : public CFogbot
{
public:

	enum State
	{
		STATE_WAIT = 0,			//�ҋ@���
		STATE_FOLLOW,			//�ǂ���������
		STATE_CIRCLE,			//�~�`�ړ�
		STATE_STAR,				//���̌`�̈ړ�(���C�����)
		STATE_RUN,				//��������

		STATE_MAX
	};

	CStalkingBot();						//�R���X�g���N�^
	~CStalkingBot() override;			//�f�X�g���N�^
										
	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����

	//��������
	static CStalkingBot* Create(const D3DXVECTOR3 pos, const float fShadowHeight);
	static CStalkingBot* Create(const D3DXVECTOR3 pos, const float fShadowHeight, const float fStartAngle);

private:

	void StateUpdate(void);				//��Ԃɂ���Ă̍X�V����
	bool Activate(void);				//�A�N�e�B�u��ԂɂȂ������ǂ����̔���̏���
	void FollowPlayer(void);			//�v���C���[��ǂ������鏈��		
	void CirclePlayer(void);			//�v���C���[�𒆐S�ɂ��āA���]����
	void StarCircling(void);			//���̌`�ɓ�����
	void RunAway(void);					//�����鏈��

	static const float DEFAULT_APPROACHING_SPEED;				//�f�B�t�H���g�̒ǂ������鑬�x
	static const float DEFAULT_ANGLE_SPEED;						//�f�B�t�H���g�̉�]���x
	static const float DEFAULT_FIRST_COEFF;						//�f�B�t�H���g�̍ŏ��̃p�����[�^(�p�����g���b�N�������p)
	static const float DEFAULT_SECOND_COEFF;					//�f�B�t�H���g�̓�Ԗڂ̃p�����[�^(�p�����g���b�N�������p)
	static const float DEFAULT_AMPLITUDE;						//�f�B�t�H���g�̊g�嗦
	static const float DEFAULT_ACTIVATION_DISTANCE;				//�f�B�t�H���g�̃A�N�e�B�u��ԂɂȂ鋗��
	static const float DEFAULT_CIRCLE_RANGE;					//�f�B�t�H���g�̉~�`�̔��a
	static const float DEFAULT_MAX_STAR_ANGLE;					//�f�B�t�H���g�̍ő�p�x(���̊p�x�𒴂�����A�������ԂɂȂ�)
	static const float DEFAULT_RUN_DISTANCE;					//�f�B�t�H���g�̓����鋗��
	static const D3DXVECTOR3 DEFAULT_RELATIVE_POS;				//�f�B�t�H���g�̑��Έʒu

	D3DXVECTOR3 m_center;					//���S�_
	D3DXVECTOR3 m_move;						//���x
	float		m_fPresentAngle;			//���݂̊p�x
	float		m_fStarRange;				//���̌`�̓����̔��a

	State		m_state;					//���

};

#endif