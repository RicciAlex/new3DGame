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

class CPlayer : public CObject
{
public:

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
		STATE_DAMAGE,							//�_���[�W
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

	CPlayer();															//�R���X�g���N�^
	~CPlayer() override;												//�f�X�g���N�^

	HRESULT Init(void) override;										//����������
	void Uninit(void) override;											//�I������
	void Update(void) override;											//�X�V����
	void Draw(void) override;											//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override { m_pos = pos; }		//�ʒu�̐ݒ菈��
	void SetRot(const D3DXVECTOR3 rot) { m_rot = rot; }					//�ʒu�̐ݒ菈��

	//const D3DXVECTOR2 GetSize(void) override { return Vec2Null; }		//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override { return m_pos; }			//�ʒu�̎擾����

	static CPlayer* Create(const D3DXVECTOR3 pos,int nCntPlayer);		//��������
	static D3DXCOLOR* GetPlayerColors(void);							//�v���C���[�̐F�̎擾����

	void PlayerController(int nCntPlayer);								//�v���C���[�̃L�[����
	void SetFriction(const float fFriction);

private:

	void RespawnPlayer(void);
	void HitboxEffectUpdate(void);

	static D3DXCOLOR m_playerColor[PLAYER_COLOR_MAX];					//�v���C���[�̐F
	static const float m_MaxWalkingSpeed;								//�ő�̕����X�s�[�h
	static const float m_AccelerationCoeff;								//�����W��

	D3DXVECTOR3 m_pos;													//�ʒu
	D3DXVECTOR3 m_move;													//���x
	D3DXVECTOR3 m_rot;													//����
	D3DXVECTOR3 m_DestRot;												//�ړI�̊p�x
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

	STATE m_State;														//�v���C���[�̏��

	CModelPart* m_pModel[PARTS_MAX];									//���f���ւ̃|�C���^
	CAnimator* m_pAnimator;												//�A�j���[�^�[�ւ̃|�C���^
	CCylinderHitbox* m_pHitbox;											//�q�b�g�{�b�N�X
};

#endif