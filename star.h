//=============================================================================
//
// star.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GOLD_STAR_H
#define GOLD_STAR_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBoxHitbox;


class CGoldStar : public CModel
{
public:
	CGoldStar();						//�R���X�g���N�^
	~CGoldStar() override;				//�f�X�g���N�^

	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����
	void Draw(void) override;			//�`�揈��

	static CGoldStar* Create(const D3DXVECTOR3 pos);		//��������

private:

	CBoxHitbox* m_pHitbox;			//�q�b�g�{�b�N�X

};



#endif