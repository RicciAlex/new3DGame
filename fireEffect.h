//=============================================================================
//
// fireEffect.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _FIRE_EFFECT_H
#define _FIRE_EFFECT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "effect.h"


class CFireEffect : public CEffect
{
public:
	CFireEffect();
	~CFireEffect() override;

	HRESULT Init(void) override;	//����������
	void Uninit(void) override;		//�I������
	void Update(void) override;		//�X�V����

	static CFireEffect* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);

private:

	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const D3DXVECTOR2 DEFAULT_DELTA_SIZE;
	static const int		 DEFAULT_LIFE;
	static const D3DXCOLOR   DEFAULT_COLOR;
	static const D3DXCOLOR	 DEFAULT_DELTA_COLOR;




};




#endif