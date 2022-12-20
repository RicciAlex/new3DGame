//=============================================================================
//
// nail.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _NAIL_H_
#define _NAIL_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBoxHitbox;


class CNail : public CModel
{
public:
	CNail();											//�R���X�g���N�^
	~CNail() override;									//�f�X�g���N�^
														
	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��
														
	static CNail* Create(const D3DXVECTOR3 pos);		//��������

private:

	CBoxHitbox* m_pHitbox;								//�q�b�g�{�b�N�X

};





#endif