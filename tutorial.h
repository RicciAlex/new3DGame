//=============================================================================
//
// tutorial.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _TUTORIAL_H
#define _TUTORIAL_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "game.h"

//=============================================================================
//�O���錾
//=============================================================================
class CUIString;
class CObject_2D;

class CTutorial : public CGame
{
public:

	CTutorial();								//�R���X�g���N�^
	~CTutorial() override;						//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	static CTutorial* Create(void);				//��������

private:

	bool m_bChangeIcon;			//�A�C�R����ς������ǂ���

	CObject_2D* m_pUiIcon[2];	//UI�A�C�R���ւ̃|�C���^
	CUIString*  m_pUiString;	//UI�̕�����ւ̃|�C���^
};



#endif