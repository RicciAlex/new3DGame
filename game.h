//=============================================================================
//
// game.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _GAME_H
#define _GAME_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
//�O���錾
//=============================================================================
class CPlayer;
class CTimer;


class CGame : public CMode
{
public:

	//�X�e�[�W
	enum STAGE
	{
		FIRST_STAGE = 0,

		STAGE_MAX
	};

	CGame();						//�R���X�g���N�^
	~CGame() override;				//�f�X�g���N�^

	HRESULT Init(void);				//����������
	void Uninit(void);				//�I������
	void Update(void);				//�X�V����

	void AddTime(const float fMilliseconds);		//���Ԃ̒ǉ�����

	void SetPlayer(CPlayer* pPlayer);		//�v���C���[�̐ݒ菈��
	CPlayer* GetPlayer(void);				//�v���C���[�̎擾����

private:

	CPlayer* m_pPlayer;				//�v���C���[�ւ̃|�C���^
	CTimer*  m_pTimer;				//�^�C�}�[�ւ̃|�C���^

};



#endif