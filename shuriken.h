//=============================================================================
//
// shuriken.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SHURIKEN_H
#define SHURIKEN_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBoxHitbox;

class CShuriken : public CModel
{
public:
	CShuriken();				//�R���X�g���N�^
	~CShuriken() override;		//�f�X�g���N�^

	HRESULT Init(void);			//����������
	void Uninit(void);			//�I������
	void Update(void);			//�X�V����

	static CShuriken* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 speed);		//��������
	static CShuriken* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 speed, const float fShadowHeight);		//��������

private:

	D3DXVECTOR3 m_move;						//���x
	int			m_nLife;					//���C�t
	
	CBoxHitbox* m_pHitbox;				//�q�b�g�{�b�N�X

};




#endif