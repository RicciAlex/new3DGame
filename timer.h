//=============================================================================
//
// timer.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _TIMER_H
#define _TIMER_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CUIString;


class CTimer : public CObject
{
public:

	static const int DEFAULT_MAX_TIME = 900000;

	CTimer();							//コンストラクタ
	~CTimer() override;					//デストラクタ
										
	HRESULT Init(void) override;		//初期化処理
	void  Uninit(void) override;		//終了処理
	void  Update(void) override;		//更新処理
	void Draw(void) override;			//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;		//位置の設定処理
	void AddTime(const float fMilliseconds);			//時間の追加処理

	const D3DXVECTOR3 GetPos(void) override;			//位置の取得処理
	const float GetTime(void);							//時間の取得処理

	static CTimer* Create(void);		//生成処理

private:

	float m_fCurrentTime;
	float m_fStartTime;
	float m_fAddedTime;

	CUIString* m_pString;

};




#endif