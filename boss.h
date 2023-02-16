//=============================================================================
//
// boss.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _BOSS_H_
#define _BOSS_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================



class CBoss : public CModel
{
public:
	CBoss();						//�R���X�g���N�^
	~CBoss() override;				//�f�X�g���N�^
									
	HRESULT Init(void) override;	//����������
	void Uninit(void) override;		//�I������
	void Update(void) override;		//�X�V����
	

	static CBoss* Create(void);		//��������

private:

	static const D3DXVECTOR3 DEFAULT_POS;			//�f�B�t�H���g�̈ʒu


	D3DXVECTOR3 m_targetPos;	//�U���̈ʒu
	int m_nCntAttack;			//�U���J�E���^�[

};


#endif