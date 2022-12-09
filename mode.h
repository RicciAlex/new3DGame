//=============================================================================
//
// mode.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _MODE_H
#define _MODE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"


class CMode
{
public:

	CMode();								//�R���X�g���N�^
	CMode(const bool bGame);				//�R���X�g���N�^
	virtual ~CMode();						//�f�X�g���N�^
											
	virtual HRESULT Init(void) = 0;			//����������
	virtual void Uninit(void) = 0;			//�I������
	virtual void Update(void) = 0;			//�X�V����

	const bool IsGame(void);				//�Q�[���ł��邩�ǂ���

private:

	bool m_bGame;							//�Q�[�����[�h�ł��邩�ǂ���

};



#endif