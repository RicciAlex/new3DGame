//=============================================================================
//
// fogEffect.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _FOG_EFFECT_H
#define _FOG_EFFECT_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "effect.h"


class CFogEffect : public CEffect
{
public:

	CFogEffect();					//コンストラクタ
	~CFogEffect() override;			//デストラクタ

	HRESULT Init(void) override;	//初期化処理
	void Uninit(void) override;		//終了処理
	void Update(void) override;		//更新処理

	static CFogEffect* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);		//生成処理

private:

	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const int		 DEFAULT_LIFE;
	static const D3DXCOLOR   DEFAULT_COLOR;

	float m_fAcceleration;				//加速

};




#endif