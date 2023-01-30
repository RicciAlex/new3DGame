//=============================================================================
//
// PauseMenu.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _PAUSE_MENU_H
#define _PAUSE_MENU_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "menu.h"

//=============================================================================
//前方宣言
//=============================================================================
class CMenuButton;


class CPauseMenu : public CMenu
{
public:

	static const D3DXVECTOR3 DEFAULT_MENU_POS;				//ディフォルトのメニューの位置

	enum MenuButtonType
	{
		TYPE_CONTINUE = 0,
		TYPE_QUIT,

		TYPE_MAX
	};

	CPauseMenu();								//コンストラクタ
	~CPauseMenu() override;						//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理
	void Draw(void) override;					//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;//位置の設定処理

	static CPauseMenu* Create(void);			//生成処理

private:

	void CreateButton(void);			//ボタンの生成処理

	static const D3DXVECTOR2 DEFAULT_MENU_SIZE;				//ディフォルトのメニューのサイズ
	static const D3DXVECTOR2 DEFAULT_BUTTON_SIZE;			//ディフォルトのボタンのサイズ
	static const float		 DEFAULT_BUTTON_DISTANCE;		//ボタンの間の距離
	static const char		 BUTTON_STRING[TYPE_MAX][48];	//ボタンの文字列

	D3DXVECTOR3 m_buttonRelativePos[TYPE_MAX];				//ボタンの相対位置
	bool m_bActive;											//アクティブであるかどうか

	CMenuButton* m_pButton[TYPE_MAX];						//メニューのボタン

};


#endif