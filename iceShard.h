//=============================================================================
//
// iceShard.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _ICE_SHARD_H_
#define _ICE_SHARD_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"


class CIceShard : public CModel
{
public:
	CIceShard();						//コンストラクタ
	~CIceShard() override;				//デストラクタ
										
	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理

	static CIceShard* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);		//生成処理

private:

	static const int DEFAULT_LIFE = 90;		//ディフォルトのライフ
	static const float DEFAULT_GRAVITY_ACCELERATION;		//重力

	D3DXVECTOR3 m_move;			//速度
	int			m_nCntLife;		//ライフのカウンター

};


#endif