//=============================================================================
//
// icicle.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef ICICLE_H
#define ICICLE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCylinderHitbox;


class CIcicle : public CModel
{
public:

	CIcicle();											//コンストラクタ
	~CIcicle() override;								//デストラクタ
														
	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理

	static CIcicle* Create(const D3DXVECTOR3 pos);		//生成処理

private:

	static const D3DXVECTOR3 DEFAULT_DAMAGE_HITBOX_SIZE;		//ディフォルトのダメージを与えるヒットボックスのサイズ
	static const D3DXVECTOR3 DEFAULT_BODY_HITBOX_SIZE;			//ディフォルトのダメージを与えないヒットボックスのサイズ
	static const float DEFAULT_STARTING_SCALE;					//ディフォルトの初めのスケール
	static const float DEFAULT_MAX_SCALE;						//ディフォルトの最大のスケール
	static const float DEFAULT_SCALE_INCREMENT;					//加算されているスケールの値
	static const float DEFAULT_APLHA_INCREMENT;					//加算されているα値の値
	static const int   DEFAULT_DELAY;							//ディフォルトのディレイ

	int	  m_nDelay;							//ディレイ
	int	  m_nCntDelay;						//ディレイのカウンター
	float m_fAlpha;							//現在のα値の値

	CCylinderHitbox* m_pDamageHitbox;		//ヒットボックスへのポインタ
	CCylinderHitbox* m_pHitbox;				//ヒットボックスへのポインタ
};





#endif