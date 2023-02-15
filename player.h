//=============================================================================
//
// player.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CModelPart;
class CAnimator;
class CCylinderHitbox;
class CBoxHitbox;
class CStarUI;

class CPlayer : public CObject
{
public:

	static const float		 DEFAULT_FALL_HEIGHT;						//���̍����̉��ɂ���Ǝ���
	static const D3DXVECTOR3 m_playerSize;								//�v���C���[�̃T�C�Y

	enum Parts
	{
		BODY = 0,								//��
		HEAD,									//��
		LEFT_ARM,								//���r
		LEFT_HAND,								//����
		RIGHT_ARM,								//�E�r
		RIGHT_HAND,								//�E��
		LEFT_LEG,								//����
		LEFT_FOOT,								//������
		RIGHT_LEG,								//�E��
		RIGHT_FOOT,								//�E����
		SAYA,									//��
		KATANA,									//��
		PARTS_MAX
	};

	enum STATE
	{
		STATE_NEUTRAL = 0,						//�j���[�g����
		STATE_RUNNING,							//����
		STATE_JUMP_START,
		STATE_JUMP,								//�W�����v
		STATE_ATTACK,							//�U��

		STATE_MAX								
	};

	enum PlayerColor
	{
		PLAYER_RED = 0,							//��
		PLAYER_GREEN,							//��
		PLAYER_BLUE,							//��
		PLAYER_YELLOW,							//��
		PLAYER_MAGENTA,							//�}�[���^
		PLAYER_CYAN,							//�V�A��
		PLAYER_BLACK,							//��
		PLAYER_WHITE,							//��

		PLAYER_COLOR_MAX
	};

	enum CAMERA_POS
	{
		CAMERA_POS_NORMAL = 0,
		CAMERA_POS_BACK,

		CAMERA_POS_MAX
	};

	CPlayer();															//�R���X�g���N�^
	~CPlayer() override;												//�f�X�g���N�^

	HRESULT Init(void) override;										//����������
	void Uninit(void) override;											//�I������
	void Update(void) override;											//�X�V����
	void Draw(void) override;											//�`�揈��

	void AddStar(void);													//��1�̉��Z����

	void SetPos(const D3DXVECTOR3 pos) override;						//�ʒu�̐ݒ菈��
	void SetRot(const D3DXVECTOR3 rot);									//�����̐ݒ菈��
	void SetLanded(void);												//���n���Ă��邩�ǂ����̐ݒ菈��
	void SetMove(const D3DXVECTOR3 move);								//���x�̐ݒ菈��
	void SetTargetCameraPos(CAMERA_POS pos);							//�J�����̖ړI�̈ʒu�̐ݒ菈��
	void SetRespawnPoint(const D3DXVECTOR3 pos);						//���X�|�[���̈ʒu�̐ݒ菈��
	void SetCameraAnim(const bool bAnim);								//�J�����A�j���[�V�����̐ݒ菈��

	const D3DXVECTOR3 GetPos(void) override;							//�ʒu�̎擾����
	const D3DXVECTOR3 GetLastPos(void);									//�O��̈ʒu�̎擾����
	const D3DXVECTOR3 GetMove(void);									//���x�̎擾����
	const bool GetLanded(void);											//���n���Ă��邩�ǂ����̎擾����

	static CPlayer* Create(const D3DXVECTOR3 pos,int nCntPlayer);		//��������
	static D3DXCOLOR* GetPlayerColors(void);							//�v���C���[�̐F�̎擾����

	void PlayerController(int nCntPlayer);								//�v���C���[�̃L�[����
	void SetFriction(const float fFriction);

private:

	void TransformUpdate(void);
	void UpdateRotation(void);
	void UpdateHitbox(void);
	void UpdateAnimation(void);
	void FieldUpdate(void);
	void RespawnPlayer(void);
	void HitboxEffectUpdate(void);
	void UpdatePlayerCamera(void);
	void MoveCamera(void);

	static const D3DXVECTOR3 m_baseCameraPos;							//���ʂ̃J�����̈ʒu
	static const D3DXVECTOR3 m_baseFocalPointPos;						//���ʂ̒����_�̈ʒu
	static const D3DXVECTOR3 m_BackCameraPos;							//���̃J�����̈ʒu
	static D3DXCOLOR m_playerColor[PLAYER_COLOR_MAX];					//�v���C���[�̐F
	static const float m_MaxWalkingSpeed;								//�ő�̕����X�s�[�h
	static const float m_AccelerationCoeff;								//�����W��
	static const float JUMP_SPEED;										//�W�����v��
	static const float MAX_FALL_SPEED;									//�ő�̗����X�s�[�h
	static const float GRAVITY_ACCELERATION;							//�d��
	static const int   ATTACK_TIME;										//�U������

	D3DXVECTOR3 m_pos;													//�ʒu
	D3DXVECTOR3 m_LastPos;												//�O��̈ʒu
	D3DXVECTOR3 m_move;													//���x
	D3DXVECTOR3 m_rot;													//����
	D3DXVECTOR3 m_DestRot;												//�ړI�̊p�x
	D3DXVECTOR3 m_cameraPos;											//�J�����̑��Έʒu
	D3DXVECTOR3 m_cameraTarget;											//�J�����̖ړI�̈ʒu
	D3DXVECTOR3 m_respawnPoint;											//���X�|�[���̈ʒu
	D3DXMATRIX  m_mtxWorld;												//���[���h�}�g���b�N�X
	int			m_nInvincibilityCnt;									//���G��Ԃ̃J�E���^�[
	int			m_nCntAttack;											//�U���J�E���^�[
	int			m_nIdxPlayer;											//�v���C���[�ԍ�
	float		m_fFrictionCoeff;										//���C�W��
	bool		m_bJump;												//�W�����v���Ă��邩�ǂ���
	bool		m_bLanded;												//���n���Ă��邩�ǂ���
	bool		m_bMoving;												//�ړ����Ă��邩�ǂ���
	bool		m_bRot;													//��]�������ǂ���
	bool		m_bHit;													//�����������ǂ���
	bool		m_bAttacking;											//�A�^�b�N�������ǂ���
	bool		m_bFall;												//�������Ă��邩�ǂ���
	bool		m_bMoveCamera;											//�J�����̈ʒu���X�V���邩�ǂ���
	bool		m_bCameraAnim;											//�J�����A�j���[�V�������ł��邩�ǂ���

	STATE m_State;														//�v���C���[�̏��

	CModelPart* m_pModel[PARTS_MAX];									//���f���ւ̃|�C���^
	CAnimator* m_pAnimator;												//�A�j���[�^�[�ւ̃|�C���^
	CCylinderHitbox* m_pHitbox;											//�q�b�g�{�b�N�X
	CBoxHitbox* m_pAttackHitbox;										//�U���̃q�b�g�{�b�N�X
	CStarUI*	m_pUI;													//UI�ւ̃|�C���^
};

#endif