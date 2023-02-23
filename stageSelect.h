//=============================================================================
//
// stageSelect.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef STAGE_SELECT_H
#define STAGE_SELECT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
//�O���錾
//=============================================================================
class CStageSelectCursor;
class CAnimateUI;


class CStageSelect : public CMode
{
public:

	enum STAGE
	{
		FIRST_STAGE = 0,
		SECOND_STAGE,

		STAGE_MAX
	};

	CStageSelect();
	~CStageSelect() override;

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����
												
	static CStageSelect* Create(void);			//��������

private:

	static const D3DXVECTOR3 DEFAULT_STRING_POS;			//�f�B�t�H���g�̕�����̈ʒu
	static const D3DXVECTOR2 DEFAULT_STRING_SIZE;			//�f�B�t�H���g�̕�����̃T�C�Y
	static const D3DXVECTOR3 CURSOR_POS[2];					//�J�[�\���̈ʒu

	int m_nSelectedStage;				//���݂̃X�e�[�W�C���f�b�N�X

	CStageSelectCursor* m_pCursor;		//�J�[�\���ւ̃|�C���^
	CAnimateUI* m_pLogo[STAGE_MAX];		//�X�e�[�W�̃��S�ւ̃|�C���^

};




#endif