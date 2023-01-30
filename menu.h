//=============================================================================
//
// menu.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _MENU_H
#define _MENU_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CObject_2D;


class CMenu
{
public:

	CMenu();									//�R���X�g���N�^
	virtual ~CMenu();							//�f�X�g���N�^

	virtual HRESULT Init(void);					//����������
	virtual void Uninit(void);					//�I������
	virtual void Update(void);					//�X�V����
	virtual void Draw(void);					//�`�揈��

	virtual void SetPos(const D3DXVECTOR3 pos);	//�ʒu�̐ݒ菈��

	const D3DXVECTOR3 GetPos(void);				//�ʒu�̎擾����

protected:

	void CreateBg(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, CObject::TextType texture);		//�w�i��������

	const CObject_2D* GetBg(void);			//�w�i�̎擾����

private:

	D3DXVECTOR3 m_pos;				//�ʒu

	CObject_2D* m_pBg;				//���j���[�̔w�i

};



#endif