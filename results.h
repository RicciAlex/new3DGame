//=============================================================================
//
// results.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _RESULTS_H
#define _RESULTS_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"
#include "score.h"

//=============================================================================
//前方宣言
//=============================================================================
class CUIString;


class CResults : public CMode
{
public:
	CResults();									//コンストラクタ
	~CResults() override;						//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理

	static CResults* Create(void);				//生成処理

private:

	static const int UI_NUMBER = 4;				//UIの数
	static const int START_DELAY;			//アニメーションの開始前のディレイ
	static const int ANIM_DELAY;			//アニメーションする時のディレイ
	static const D3DXVECTOR3 UI_STARTING_POS;	//最初のUIの位置
	static const float UI_DISTANCE;	//UIの距離
	static const D3DXVECTOR2 UI_SIZE;	//UIのサイズ


	int m_nCntAnim;				//アニメーション用のカウンター
	int m_nPhase;				//アニメーション用の変数

	CUIString* m_pRanking[UI_NUMBER];		//UIへのポインタ
};



#endif