//=============================================================================
//
// spikeTrap.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef STALKING_BOT_H
#define STALKING_BOT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "fogBot.h"

//=============================================================================
//�O���錾
//=============================================================================


class CStalkingBot : public CFogbot
{
public:
	CStalkingBot();						//�R���X�g���N�^
	~CStalkingBot() override;			//�f�X�g���N�^
										
	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����

	//��������
	static CStalkingBot* Create(const D3DXVECTOR3 pos, const float fShadowHeight);
	static CStalkingBot* Create(const D3DXVECTOR3 pos, const float fShadowHeight, const float fStartAngle);

private:

	static const float DEFAULT_APPROACHING_SPEED;				//�f�B�t�H���g�̒ǂ������鑬�x
	static const float DEFAULT_ANGLE_SPEED;						//�f�B�t�H���g�̉�]���x
	static const float DEFAULT_FIRST_COEFF;						//�f�B�t�H���g�̍ŏ��̃p�����[�^(�p�����g���b�N�������p)
	static const float DEFAULT_SECOND_COEFF;					//�f�B�t�H���g�̓�Ԗڂ̃p�����[�^(�p�����g���b�N�������p)
	static const float DEFAULT_AMPLITUDE;						//�f�B�t�H���g�̊g�嗦
	static const D3DXVECTOR3 DEFAULT_RELATIVE_POS;				//�f�B�t�H���g�̑��Έʒu

	D3DXVECTOR3 m_move;
	float		m_fPresentAngle;

};

#endif