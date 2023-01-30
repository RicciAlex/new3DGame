//=============================================================================
//
// PauseMenu.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _PAUSE_MENU_H
#define _PAUSE_MENU_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "menu.h"

//=============================================================================
//�O���錾
//=============================================================================
class CMenuButton;


class CPauseMenu : public CMenu
{
public:

	static const D3DXVECTOR3 DEFAULT_MENU_POS;				//�f�B�t�H���g�̃��j���[�̈ʒu

	enum MenuButtonType
	{
		TYPE_CONTINUE = 0,
		TYPE_QUIT,

		TYPE_MAX
	};

	CPauseMenu();								//�R���X�g���N�^
	~CPauseMenu() override;						//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����
	void Draw(void) override;					//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;//�ʒu�̐ݒ菈��

	static CPauseMenu* Create(void);			//��������

private:

	void CreateButton(void);			//�{�^���̐�������

	static const D3DXVECTOR2 DEFAULT_MENU_SIZE;				//�f�B�t�H���g�̃��j���[�̃T�C�Y
	static const D3DXVECTOR2 DEFAULT_BUTTON_SIZE;			//�f�B�t�H���g�̃{�^���̃T�C�Y
	static const float		 DEFAULT_BUTTON_DISTANCE;		//�{�^���̊Ԃ̋���
	static const char		 BUTTON_STRING[TYPE_MAX][48];	//�{�^���̕�����

	D3DXVECTOR3 m_buttonRelativePos[TYPE_MAX];				//�{�^���̑��Έʒu
	bool m_bActive;											//�A�N�e�B�u�ł��邩�ǂ���

	CMenuButton* m_pButton[TYPE_MAX];						//���j���[�̃{�^��

};


#endif