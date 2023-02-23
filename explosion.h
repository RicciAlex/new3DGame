//=============================================================================
//
// explosion.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CFireEffect;


class CExplosion : public CObject
{
public:

	CExplosion();
	~CExplosion() override;

	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;	//位置の設定処理

	const D3DXVECTOR3 GetPos(void) override;		//位置の取得処理

	static CExplosion* Create(const D3DXVECTOR3 pos);		//生成処理

private:

	static const int DEFAULT_LIFE;	//ディフォルトのライフ
	static const int EFFECT_NUMBER;	//毎フレーム生成されるエフェクト数

	D3DXVECTOR3 m_pos;				//位置
	int m_nLife;					//ライフ

};


#endif