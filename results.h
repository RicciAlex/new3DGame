//=============================================================================
//
// results.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _RESULTS_H
#define _RESULTS_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"
#include "score.h"

//=============================================================================
//�O���錾
//=============================================================================
class CUIString;


class CResults : public CMode
{
public:
	CResults();									//�R���X�g���N�^
	~CResults() override;						//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	static CResults* Create(void);				//��������

private:

	static const int UI_NUMBER = 4;				//UI�̐�
	static const int START_DELAY;			//�A�j���[�V�����̊J�n�O�̃f�B���C
	static const int ANIM_DELAY;			//�A�j���[�V�������鎞�̃f�B���C
	static const D3DXVECTOR3 UI_STARTING_POS;	//�ŏ���UI�̈ʒu
	static const float UI_DISTANCE;	//UI�̋���
	static const D3DXVECTOR2 UI_SIZE;	//UI�̃T�C�Y


	int m_nCntAnim;				//�A�j���[�V�����p�̃J�E���^�[
	int m_nPhase;				//�A�j���[�V�����p�̕ϐ�

	CUIString* m_pRanking[UI_NUMBER];		//UI�ւ̃|�C���^
};



#endif