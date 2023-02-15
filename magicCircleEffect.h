//=============================================================================
//
// magicCircleEffect.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _MAGIC_CIRCLE_EFFECT_H
#define _MAGIC_CIRCLE_EFFECT_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object3D.h"



class CMagicCircleEffect : public CObject_3D
{
public:
	CMagicCircleEffect();					//コンストラクタ
	~CMagicCircleEffect() override;			//デストラクタ

	HRESULT Init(void) override;			//初期化処理

	static CMagicCircleEffect* Create(const D3DXVECTOR3 pos);		//生成処理

private:

	static const D3DXVECTOR2 DEFAULT_SIZE;			//ディフォルトのサイズ

};


#endif