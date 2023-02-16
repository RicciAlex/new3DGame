//=============================================================================
//
// twisterEffect.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _TWISTER_EFFECT_H_
#define _TWISTER_EFFECT_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "effect.h"


class CTwisterEffect : public CEffect
{
public:

	static const int		 DEFAULT_LIFE;			//ディフォルトのライフ

	CTwisterEffect();					//コンストラクタ
	~CTwisterEffect() override;			//デストラクタ
										
	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理

	static CTwisterEffect* Create(const D3DXVECTOR3 pos);		//生成処理

private:

	static const D3DXCOLOR	 DEFAULT_COLOR;			//ディフォルトの色
	static const D3DXVECTOR2 DEFAULT_SIZE;			//ディフォルトのサイズ 

};





#endif