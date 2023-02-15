//=============================================================================
//
// gem.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _GEM_H
#define _GEM_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"
#include "goal.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBoxHitbox;


class CGem : public CModel
{
public:
	CGem();							//�R���X�g���N�^
	~CGem() override;				//�f�X�g���N�^
									
	HRESULT Init(void) override;	//����������
	void Uninit(void) override;		//�I������
	void Update(void) override;		//�X�V����

	static CGem* Create(const D3DXVECTOR3 pos);		//��������
	static CGem* Create(const D3DXVECTOR3 pos, const D3DXCOLOR col);		//��������
	static CGem* Create(const D3DXVECTOR3 pos, const D3DXCOLOR col, const float fShadowHeight);		//��������
	static CGem* Create(const D3DXVECTOR3 pos, const D3DXCOLOR col, const float fShadowHeight, const D3DXVECTOR3 newPos, CGoal* pGoal);		//��������

private:

	static const float DEFAULT_SCALE;			//�f�B�t�H���g�̃X�P�[���̌W��
	static const D3DXVECTOR3 DEFAULT_ROTATION;	//�f�B�t�H���g�̉�]���x
	static const D3DXVECTOR3 DEFAULT_SIZE;		//�f�B�t�H���g�̃T�C�Y


	D3DXVECTOR3 m_newPos;						//�V�����ʒu

	CBoxHitbox* m_pHitbox;						//�q�b�g�{�b�N�X�ւ̃|�C���^
};


#endif