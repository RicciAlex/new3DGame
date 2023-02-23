//=============================================================================
//
// boss.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _BOSS_H_
#define _BOSS_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================



class CBoss : public CModel
{
public:
	CBoss();						//�R���X�g���N�^
	~CBoss() override;				//�f�X�g���N�^
									
	HRESULT Init(void) override;	//����������
	void Uninit(void) override;		//�I������
	void Update(void) override;		//�X�V����
	void Draw(void) override;		//�`�揈��
	
	void DealDamage(void);					//�_���[�W���󂯂鏈��
	void DealDamage(const int nDamage);		//�_���[�W���󂯂鏈��

	static CBoss* Create(void);		//��������

private:

	enum STATE
	{
		STATE_SPAWN = 0,
		STATE_ATTACK,
		STATE_DAMAGE,
		STATE_DEATH,

		STATE_MAX
	};

	enum BOSS_ATTACK
	{
		ATTACK_ICICLE = 0,
		ATTACK_BOULDER,
		ATTACK_TWISTER,

		ATTACK_MAX
	};

	void UpdateState(void);									//��Ԃɂ���Ă̍X�V����
	void SelectAttack(const D3DXVECTOR3 &playerPos);		//�U���̐ݒ菈��
	void SetIcicleAttack(const D3DXVECTOR3 &playerPos);		//Icicle�U���̐ݒ菈��
	void SetBoulderAttack(const D3DXVECTOR3 &playerPos);	//Boulder�U���̐ݒ菈��
	void SetTwisterAttack(const D3DXVECTOR3 &playerPos);	//Twister�U���̐ݒ菈��
	void UpdateAttack(const D3DXVECTOR3 &playerPos);		//���݂̍U���̍X�V����
	void IcicleUpdate(const D3DXVECTOR3 &playerPos);		//Icicle�U���̍X�V����	
	void BoulderUpdate(const D3DXVECTOR3 &playerPos);		//Boulder�U���̍X�V����

	static const D3DXVECTOR3 DEFAULT_POS;			//�f�B�t�H���g�̈ʒu
	static const int DEFAULT_LIFE;					//�f�B�t�H���g�̗̑�
	static const int DEFAULT_INVULNERABILITY_FRAMES;	//�f�B�t�H���g�̖��G��ԃt���[����
	static const int DEFAULT_SPAWN_FRAMES;			//�f�B�t�H���g�̃X�|�[���t���[����
	static const int DEFAULT_DESPAWN_TIME;			//�f�B�t�H���g�̃f�B�X�|�[���t���[����
	static const float DEFAULT_DESPAWN_SPEED;		//�f�B�t�H���g�̃f�B�X�|�[�����x

	//=======================================================================================
	//Icicle�U��
	static const int DEFAULT_ICICLE_COOLDOWN;		//�f�B�t�H���g��Icicle�U���̃N�[���_�E��
	static const int ICICLE_ROAR_DELAY;				//�����̃f�B���C
	static const int SET_TARGET_DELAY;				//�ړI�̈ʒu�̐ݒ�̃f�B���C
	static const int ICICLE_ATTACK_DELAY;			//�U���܂ł̃f�B���C
	//=======================================================================================
	//=======================================================================================
	//Boulder�U��
	static const int DEFAULT_BOULDER_COOLDOWN;				//�f�B�t�H���g��Boulder�U���̃N�[���_�E��
	static const int THROWN_BOULDER_NUMBER;					//��������̐�
	static const int THROW_DELAY;							//������Ԃ̃f�B���C
	static const D3DXVECTOR3 BOULDER_SPAWN_RELATIVE_POS;	//Boulder�U���̃X�|�[���̑��Έʒu
	//=======================================================================================
	//=======================================================================================
	//Twister�U��
	static const int DEFAULT_TWISTER_COOLDOWN;		//�f�B�t�H���g��Twister�U���̃N�[���_�E��
	static const float DEFAULT_TWISTER_DISTANCE;	//�X�|�[������v���C���[�܂ł̋���
	//=======================================================================================


	D3DXVECTOR3 m_targetPos;	//�U���̈ʒu
	BOSS_ATTACK m_presentAttack;	//���݂̍U��
	STATE m_state;				//���
	int m_nCntAttack;			//�U���J�E���^�[
	int m_nCntCooldown;			//�N�[���_�E���̃J�E���^�[
	int m_nCntDamage;			//�_���[�W�̃J�E���^�[
	int m_nLife;				//�̗�
	float m_fRelativeTranslation;				//���Έړ�

};


#endif