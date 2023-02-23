//=============================================================================
//
// title.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _TITLE_H
#define _TITLE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBillboard;


class CTitle : public CMode
{
public:
	CTitle();
	~CTitle() override;

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	static CTitle* Create(void);				//��������

private:

	static const D3DXVECTOR3 FOCAL_POINT_RELATIVE_POS;		//�����_�̑��Έʒu
	static const D3DXVECTOR3 BG_RELATIVE_POS;		//�w�i�̑��Έʒu
	static const D3DXVECTOR3 START_POS[2];			//�J�n�̈ʒu
	static const D3DXVECTOR3 END_POS[2];			//�I���̈ʒu

	void SetMap(void);			//�}�b�v�̔z�u����

	int m_nPresentCourse;		//���݂̃R�[�X
	bool m_bChange;				//�t�F�[�h���ł��邩�ǂ���

	CBillboard* m_pBg;			//�w�i�ւ̃|�C���^


};



#endif