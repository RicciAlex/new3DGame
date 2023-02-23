//=============================================================================
//
// fogbot.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _FOGBOT_H
#define _FOGBOT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CFogParticle;
class CBoxHitbox;


class CFogbot : public CModel
{
public:
	CFogbot();								//�R���X�g���N�^
	~CFogbot() override;					//�f�X�g���N�^

	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	void Update(void) override;				//�X�V����

	static CFogbot* Create(const D3DXVECTOR3 pos, const float shadowPos);		//��������

protected:

	void CreateDefaultBot(void);			//�f�B�t�H���g�̃{�b�g�̐�������(�h���N���X�p)
	void ForceActivation(void);				//�����I�ɃA�N�e�B�u�ɂ���
	void Deactivate(void);					//�A�N�e�B�u�ł͂Ȃ���Ԃɂ���

private:
	
	void UpdateParticle(void);

	static const float DEFAULT_VIEW_RANGE;	//�f�B�t�H���g�̌�����͈͂̔��a
	static D3DXVECTOR3 DEFAULT_PARTICLE_RELATIVE_POS;		//�p�[�e�B�N���̃f�B�t�H���g�̑��Έʒu
	static const float DEFAULT_FRAME_ANGLE;	//�A�j���[�V�����p�̊p�x
	static const float DEFAULT_ANIM_AMPLITUDE;
	static const float DEFAULT_GRAVITY_ACCELERATION;	//�d�͉����x
	static const D3DXVECTOR3 DEFAULT_HITBOX_SIZE;		//�q�b�g�{�b�N�X�̃f�B�t�H���g�T�C�Y
	static const float DEFAULT_DESPAWN_HEIGHT;			//�f�B�t�H���g�̃f�B�X�|�[����Y���W

	D3DXVECTOR3 m_deathSpeed;				//���S������̃X�s�[�h
	int   m_nCntSound;						//�T�E���h�p�̃J�E���^�[
	float m_fAnimAngle;						//�A�j���[�V�����p�̊p�x
	float m_fRange;							//������͈͂̔��a
	bool  m_bActive;						//�v���C���[�������邩�ǂ���
	bool  m_bForceActive;					//�����I�ɃA�N�e�B�u�ɂ��邩�ǂ���
	bool  m_bDeath;							//���S�t���O

	CFogParticle* m_pParticle;				//�p�[�e�B�N���ւ̃|�C���^
	CBoxHitbox*   m_pHitbox;				//�q�b�g�{�b�N�X�ւ̃|�C���^

};




#endif