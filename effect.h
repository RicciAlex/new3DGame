//=============================================================================
//
// effect.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _EFFECT_H_
#define _EFFECT_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "billboard.h"

class CEffect : public CBillboard
{
public:
	CEffect();								//コンストラクタ
	~CEffect() override;					//デストラクタ

	virtual HRESULT Init(void) override;	//初期化処理
	virtual void Uninit(void) override;		//終了処理
	virtual void Update(void) override;		//更新処理
	virtual void Draw(void) override;		//描画処理
	
	void SetMove(const D3DXVECTOR3 move);	//速度の設定処理
	void SetLife(const int nLife);			//ライフの設定処理

	const D3DXVECTOR3 GetMove(void);		//速度の取得処理

	static CEffect* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col);
	static CEffect* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const int nLife);
	static CEffect* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const D3DXVECTOR3 move);
	static CEffect* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const int nLife, const D3DXVECTOR3 move);

private:

	static const int DEFAULT_LIFE = 60;

	D3DXVECTOR3 m_move;				//速度
	int			m_nLife;			//ライフ
};




#endif