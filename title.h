//=============================================================================
//
// title.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _TITLE_H
#define _TITLE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBillboard;


class CTitle : public CMode
{
public:
	CTitle();
	~CTitle() override;

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理

	static CTitle* Create(void);				//生成処理

private:

	static const D3DXVECTOR3 FOCAL_POINT_RELATIVE_POS;		//注視点の相対位置
	static const D3DXVECTOR3 BG_RELATIVE_POS;		//背景の相対位置
	static const D3DXVECTOR3 START_POS[2];			//開始の位置
	static const D3DXVECTOR3 END_POS[2];			//終了の位置

	void SetMap(void);			//マップの配置処理

	int m_nPresentCourse;		//現在のコース
	bool m_bChange;				//フェード中であるかどうか

	CBillboard* m_pBg;			//背景へのポインタ


};



#endif