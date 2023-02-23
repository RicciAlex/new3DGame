//=============================================================================
//
// tutorial.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _TUTORIAL_H
#define _TUTORIAL_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "game.h"

//=============================================================================
//前方宣言
//=============================================================================
class CUIString;
class CObject_2D;

class CTutorial : public CGame
{
public:

	CTutorial();								//コンストラクタ
	~CTutorial() override;						//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理

	static CTutorial* Create(void);				//生成処理

private:

	bool m_bChangeIcon;			//アイコンを変えたかどうか

	CObject_2D* m_pUiIcon[2];	//UIアイコンへのポインタ
	CUIString*  m_pUiString;	//UIの文字列へのポインタ
};



#endif