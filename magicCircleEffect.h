//=============================================================================
//
// magicCircleEffect.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _MAGIC_CIRCLE_EFFECT_H
#define _MAGIC_CIRCLE_EFFECT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object3D.h"



class CMagicCircleEffect : public CObject_3D
{
public:
	CMagicCircleEffect();					//�R���X�g���N�^
	~CMagicCircleEffect() override;			//�f�X�g���N�^

	HRESULT Init(void) override;			//����������

	static CMagicCircleEffect* Create(const D3DXVECTOR3 pos);		//��������

private:

	static const D3DXVECTOR2 DEFAULT_SIZE;			//�f�B�t�H���g�̃T�C�Y

};


#endif