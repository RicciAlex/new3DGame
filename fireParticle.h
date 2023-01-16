//=============================================================================
//
// fireParticle.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _FIRE_PARTICLE_H
#define _FIRE_PARTICLE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

class CFireParticle : public CObject
{
public:
	CFireParticle();								//コンストラクタ
	~CFireParticle() override;						//デストラクタ


	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;	//位置の設定処理
	void SetActiveState(const bool bActive);		//エフェクトをスポーンするかどうかの設定処理

	const D3DXVECTOR3 GetPos(void) override;		//位置の取得処理
	const bool GetActiveState(void);				//エフェクトをスポーンするかどうかの取得処理

	static CFireParticle* Create(const D3DXVECTOR3 pos);	//生成処理

private:

	const int DEFAULT_EFFECT_NUMBER = 7;

	D3DXVECTOR3 m_pos;								//位置
	bool		m_bActive;							//エフェクトをスポーンするかどうか

};


#endif
