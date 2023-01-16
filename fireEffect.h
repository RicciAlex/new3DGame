//=============================================================================
//
// fireEffect.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _FIRE_EFFECT_H
#define _FIRE_EFFECT_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "effect.h"


class CFireEffect : public CEffect
{
public:
	CFireEffect();
	~CFireEffect() override;

	HRESULT Init(void) override;	//初期化処理
	void Uninit(void) override;		//終了処理
	void Update(void) override;		//更新処理

	static CFireEffect* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);

private:

	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const D3DXVECTOR2 DEFAULT_DELTA_SIZE;
	static const int		 DEFAULT_LIFE;
	static const D3DXCOLOR   DEFAULT_COLOR;
	static const D3DXCOLOR	 DEFAULT_DELTA_COLOR;




};




#endif