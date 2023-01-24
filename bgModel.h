//=============================================================================
//
// bgModel.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _BG_MODEL_H
#define _BG_MODEL_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"


class CBgModel : public CModel
{
public:

	CBgModel();						//�R���X�g���N�^
	~CBgModel() override;			//�f�X�g���N�^

	HRESULT Init(void) override;	//����������
	void Uninit(void) override;		//�I������
	void Update(void) override;		//�X�V����

	static CBgModel* Create(CModel::ModelType type, const D3DXVECTOR3 pos);									//��������
	static CBgModel* Create(CModel::ModelType type, const D3DXVECTOR3 pos, const D3DXVECTOR3 move);			//��������

private:

	D3DXVECTOR3 m_move;					//���x

};


#endif