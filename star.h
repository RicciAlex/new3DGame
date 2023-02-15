//=============================================================================
//
// star.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GOLD_STAR_H
#define GOLD_STAR_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBoxHitbox;


class CGoldStar : public CModel
{
public:
	CGoldStar();						//コンストラクタ
	~CGoldStar() override;				//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理
	void Draw(void) override;			//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;			//位置の設定処理

	static CGoldStar* Create(const D3DXVECTOR3 pos);		//生成処理
	static CGoldStar* Create(const D3DXVECTOR3 pos, const float fShadowHeight);		//生成処理

private:

	CBoxHitbox* m_pHitbox;			//ヒットボックス

};



#endif