//=============================================================================
//
// fogParticle.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _FOG_PARTICLE_H
#define _FOG_PARTICLE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

class CFogParticle : public CObject
{
public:
	CFogParticle();								//コンストラクタ
	~CFogParticle() override;						//デストラクタ


	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;	//位置の設定処理
	void SetActiveState(const bool bActive);		//エフェクトをスポーンするかどうかの設定処理

	const D3DXVECTOR3 GetPos(void) override;		//位置の取得処理
	const bool GetActiveState(void);				//エフェクトをスポーンするかどうかの取得処理

	static CFogParticle* Create(const D3DXVECTOR3 pos);	//生成処理

private:

	const int DEFAULT_EFFECT_NUMBER = 5;

	D3DXVECTOR3 m_pos;								//位置
	bool		m_bActive;							//エフェクトをスポーンするかどうか

};


#endif
