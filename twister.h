//=============================================================================
//
// twister.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _TWISTER_H_
#define _TWISTER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"
#include "twisterEffect.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCylinderHitbox;


class CTwister : public CObject
{
public:

	CTwister();							//コンストラクタ
	~CTwister() override;				//デストラクタ
										
	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理
	void Draw(void) override;			//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;		//位置の設定処理

	const D3DXVECTOR3 GetPos(void) override;			//位置の取得処理

	static CTwister* Create(const D3DXVECTOR3 pos);			//生成処理

private:

	void UpdatePos(void);				//位置の更新処理
	void UpdateEffectPos(void);			//エフェクトの位置の更新処理
	void UpdateHitbox(void);			//ヒットボックスの更新処理

	static const int LAYER_NUMBER = 25;
	static const int EFFECT_PER_LAYER = 20;
	static const float EFFECT_DISTANCE;					//エフェクトの距離
	static const float START_RANGE;						//はじめての半径
	static const float DEFAULT_SPEED;					//ディフォルトの速度
	static const D3DXVECTOR3 HITBOX_SIZE;				//ヒットボックスのサイズ

	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_move;				//速度
	int			m_nLife;			//ライフ
	float		m_fStartingAngle[LAYER_NUMBER];		//初期時の角度
	float		m_fCurrentAngle;					//現在の角度



	CTwisterEffect* m_pEffect[LAYER_NUMBER * EFFECT_PER_LAYER];			//エフェクトへのポインタ
	CCylinderHitbox* m_pHitbox;				//ヒットボックスへのポインタ

};




#endif