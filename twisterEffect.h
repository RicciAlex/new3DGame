//=============================================================================
//
// twisterEffect.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _TWISTER_EFFECT_H_
#define _TWISTER_EFFECT_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "effect.h"


class CTwisterEffect : public CEffect
{
public:

	static const int		 DEFAULT_LIFE;			//�f�B�t�H���g�̃��C�t

	CTwisterEffect();					//�R���X�g���N�^
	~CTwisterEffect() override;			//�f�X�g���N�^
										
	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����

	static CTwisterEffect* Create(const D3DXVECTOR3 pos);		//��������

private:

	static const D3DXCOLOR	 DEFAULT_COLOR;			//�f�B�t�H���g�̐F
	static const D3DXVECTOR2 DEFAULT_SIZE;			//�f�B�t�H���g�̃T�C�Y 

};





#endif