//=============================================================================
//
// ranking.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _RANKING_H
#define _RANKING_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"
#include "object.h"
#include "score.h"

//=============================================================================
//前方宣言
//=============================================================================
class CObject_2D;
class CUIString;


class CRanking : public CMode
{
public:

	CRanking();							//コンストラクタ
	~CRanking() override;				//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理

	static CRanking* Create(void);		//生成処理

private:

	static CObject::TextType TEXT_TYPE[CScore::STAGE_MAX][2];		//背景のテクスチャの種類

	static const D3DXVECTOR3 STRING_POS;		//ランキングの文字列の位置
	static const D3DXVECTOR3 ARROW_POS[2];		//アローUIの位置
	static const D3DXVECTOR2 ARROW_SIZE;		//アローUIのサイズ
	static const D3DXVECTOR2 BG_SIZE[2];		//背景のサイズ

	int m_nPresentStage;				//現在のステージ

	CObject_2D* m_pBg[2];				//背景へのポインタ
	CUIString* m_pRank[CScore::RANKING_SCORE];		//ランキングへのポインタ

};


#endif