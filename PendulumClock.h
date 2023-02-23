//=============================================================================
//
// PendulumClock.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _PENDULUM_CLOCK_H
#define _PENDULUM_CLOCK_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBoxHitbox;
class CModelPart;
class CObject_2D;


class CPendulumClock : public CModel
{
public:

	static const float DEFAULT_RANGE;		//�f�B�t�H���g�̗L���͈�


	CPendulumClock();					//�R���X�g���N�^
	~CPendulumClock() override;			//�f�X�g���N�^
										
	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����
	void Draw(void) override;			//�`�揈��

	void SetRange(const float fRange);	//�L���͈͂̐ݒ菈��

	static CPendulumClock* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fShadowHeight);		//��������
	static CPendulumClock* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fShadowHeight, const float fRange);		//��������

private:

	void CheckPlayer(void);

	static const int NEEDLE_NUMBER = 2;		//�j�̐�
	static const float DEFAULT_ANIM_FRAME_ANGLE;		//���t���[�����Z����Ă���p�x
	static const float MIN_RANGE;			//�ŏ��̗L���͈�

	int				m_nCntSound;		//�T�E���h�p�̃J�E���^�[
	float			m_fAnimAngle;		//�A�j���[�V�����p�̊p�x
	float			m_fAnimCoeff;		//�A�j���[�V�����p�̊p�x
	float			m_fRange;			//�L���͈�
	bool			m_bVisible;			//UI���\���Ă��邩�ǂ���
	bool			m_bSound;			//�T�E���h���Đ�����Ă��邩�ǂ���

	CModelPart*		m_pPendulum;		//�y���W�������̃��f���ւ̃|�C���^
	CModelPart*		m_pNeedle[NEEDLE_NUMBER];		//�j�ւ̃|�C���^
	CObject_2D*		m_pUI;			//UI�ւ̃|�C���^
	CBoxHitbox* m_pHitbox;			//�q�b�g�{�b�N�X�ւ̃|�C���^
};


#endif