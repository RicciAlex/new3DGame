//=============================================================================
//
// goal.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _GOAL_H
#define _GOAL_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"


class CGoal : public CModel
{
public:
	CGoal();						//�R���X�g���N�^
	~CGoal() override;				//�f�X�g���N�^
									
	HRESULT Init(void);				//����������
	void Uninit(void);				//�I������
	void Update(void);				//�X�V����

	static CGoal* Create(const D3DXVECTOR3 pos);			//��������

private:

};




#endif