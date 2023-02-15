//=============================================================================
//
// firstStage.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _FIRST_STAGE_H
#define _FIRST_STAGE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "game.h"

//=============================================================================
//�O���錾
//=============================================================================

class CFirstStage : public CGame
{
public:
	CFirstStage();								//�R���X�g���N�^
	~CFirstStage() override;					//�f�X�g���N�^
												
	HRESULT Init(void);							//����������
	void Uninit(void);							//�I������
	void Update(void);							//�X�V����
												
	static CFirstStage* Create(void);			//��������

private:

	static const int DEFAULT_MIN_SOUND_DELAY = 180;
	static const int DEFAULT_MAX_SOUND_DELAY = 400;

	int m_nCntSound;							//�T�E���h�G�t�F�N�g�p�̃J�E���^�[
	int m_nSoundDelay;							//�T�E���h�G�t�F�N�g�̃f�B���C

};


#endif