//=============================================================================
//
// cannon.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _CANNON_H_
#define _CANNON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBoxHitbox;
class CButton;
class CBoss;

class CCannon : public CModel
{
public:

	CCannon();					//�R���X�g���N�^
	~CCannon() override;		//�f�X�g���N�^

	HRESULT Init(void) override;	//����������
	void Uninit(void) override;		//�I������
	void Update(void) override;		//�X�V����

	static CCannon* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 buttonPos, CBoss* pBoss);		//��������

private:

	static const D3DXVECTOR3 HITBOX_SIZE;			//�q�b�g�{�b�N�X�̃T�C�Y

	bool m_bFired;				//�e�����������ǂ���

	CButton* m_pButton;			//�{�^���ւ̃|�C���^
	CBoxHitbox* m_pHitbox;		//�q�b�g�{�b�N�X�ւ̃|�C���^
	CBoss* m_pBoss;				//�{�X�ւ̃|�C���^

};


#endif