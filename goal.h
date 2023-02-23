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
#include "UIString.h"


class CGoal : public CModel
{
public:
	CGoal();						//�R���X�g���N�^
	~CGoal() override;				//�f�X�g���N�^
									
	HRESULT Init(void);				//����������
	void Uninit(void);				//�I������
	void Update(void);				//�X�V����

	void AddGem(void);				//��΂̉��Z����
	void SubtractGem(void);			//��΂̌��Z����

	static CGoal* Create(const D3DXVECTOR3 pos);			//��������

private:

	static const float DEFAULT_RADIUS;				//�f�B�t�H���g�̔��a

	int m_nPresentGem;			//���݂̕�ΐ�
	bool m_bCreate;				//UI�𐶐��������ǂ���

	CUIString* m_pGemNeeded;	//�K�v�ȕ�΂�UI������ւ̃|�C���^

};




#endif