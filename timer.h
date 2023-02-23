//=============================================================================
//
// timer.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _TIMER_H
#define _TIMER_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CUIString;


class CTimer : public CObject
{
public:

	static const int DEFAULT_MAX_TIME = 900000;

	CTimer();							//�R���X�g���N�^
	~CTimer() override;					//�f�X�g���N�^
										
	HRESULT Init(void) override;		//����������
	void  Uninit(void) override;		//�I������
	void  Update(void) override;		//�X�V����
	void Draw(void) override;			//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��
	void AddTime(const float fMilliseconds);			//���Ԃ̒ǉ�����

	const D3DXVECTOR3 GetPos(void) override;			//�ʒu�̎擾����
	const float GetTime(void);							//���Ԃ̎擾����

	static CTimer* Create(void);		//��������

private:

	float m_fCurrentTime;
	float m_fStartTime;
	float m_fAddedTime;

	CUIString* m_pString;

};




#endif