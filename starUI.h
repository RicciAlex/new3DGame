//=============================================================================
//
// starUI.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _STAR_UI_H_
#define _STAR_UI_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CObject_2D;
class CUIString;


class CStarUI : public CObject
{
public:

	CStarUI();										//コンストラクタ
	~CStarUI() override;							//デストラクタ

	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	void AddStar(void);								//星数1つを加算する処理

	void SetPos(const D3DXVECTOR3 pos) override;	//位置の設定処理
	void SetTargetStar(const int target);			//目的の星数の設定処理

	const D3DXVECTOR3 GetPos(void) override;		//位置の取得処理


	static CStarUI* Create(const int nMaxStar);		//生成処理

private:

	int m_nStarNumber;					//現在の星数
	int m_nTargetStar;					//目的の星数
	bool m_bDone;						//目的についたかどうか

	CObject_2D* m_pStar;				//2Dオブジェクトへのポインタ
	CUIString*	m_pString;				//文字へのポインタ

};





#endif