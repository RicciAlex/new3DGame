//=============================================================================
//
// animationFade.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef ANIMATION_FADE_H
#define ANIMATION_FADE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object2D.h"

class CAnimationFade : public CObject_2D
{
public:

	enum FADE_ANIMATION_TYPE
	{
		TYPE_NORMAL = 0,
		TYPE_PLATFORM,

		TYPE_MAX
	};

	CAnimationFade();				//�R���X�g���N�^
	~CAnimationFade() override;		//�f�X�g���N�^
									
	HRESULT Init(void) override;	//����������
	void Uninit(void) override;		//�I������
	void Update(void) override;		//�X�V����

	static CAnimationFade* Create(const D3DXVECTOR3 cameraPos, const D3DXVECTOR3 focalPoint, FADE_ANIMATION_TYPE type);		//��������

private:

	static const float DEFAULT_FADE_SPEED;				//�f�B�t�H���g�̃t�F�[�h�X�s�[�h
	static const int   DEFAULT_ANIM_FRAMES[TYPE_MAX];	//�f�B�t�H���g�̃A�j���[�V�����t���[����

	enum FADE_PHASE
	{
		START_OUT = 0,
		START_IN,
		ANIM_PAUSE,
		END_OUT,
		END_IN,

		PHASE_MAX
	};

	bool FadeOut(void);				//�t�F�[�h�A�E�g�̊֐�
	bool FadeIn(void);				//�t�F�[�h�C���̊֐�
	void PlatformAnim(void);		//�v���b�g�t�H�[���A�j���[�V����
	void NormalAnim(void);			//���ʂ̃A�j���[�V����

	D3DXVECTOR3			m_startingPos;		//�J�����̌��̈ʒu
	D3DXVECTOR3			m_cameraPos;		//�J�����̈ʒu
	D3DXVECTOR3			m_startingFocal;		//�����_�̌��̈ʒu
	D3DXVECTOR3			m_focalPos;		//�����_�̈ʒu
	int					m_nAnimFrame;		//�A�j���[�V�����̃t���[����
	FADE_ANIMATION_TYPE m_type;				//�A�j���[�V�����̎��
	FADE_PHASE			m_phase;			//���

};


#endif