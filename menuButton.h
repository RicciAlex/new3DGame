//=============================================================================
//
// menuButton.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CUIString;
class CObject_2D;


class CMenuButton : public CObject
{
public:

	enum BUTTON_TYPE
	{
		BUTTON_TYPE_CONTINUE,
		BUTTON_TYPE_START,
		BUTTON_TYPE_QUIT,
		BUTTON_TYPE_RANKING,

		BUTTON_TYPE_MAX
	};



	CMenuButton();							//コンストラクタ
	~CMenuButton() override;				//デストラクタ
											
	HRESULT Init(void) override;			//初期化処理
	void Uninit(void) override;				//終了処理
	void Update(void) override;				//更新処理
	void Draw(void) override;				//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;		//位置の設定処理

	const D3DXVECTOR3 GetPos(void) override;			//位置の取得処理

	static CMenuButton* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char* pString, BUTTON_TYPE type);		//生成処理
	static CMenuButton* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, D3DXCOLOR stringCol, const char* pString, BUTTON_TYPE type);		//生成処理
	static CMenuButton* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, D3DXCOLOR stringCol, D3DXCOLOR triggeredCol, const char* pString, BUTTON_TYPE type);		//生成処理

private:

	bool MouseOnButton(void);			//マウスカーソルがボタンを重なっているかどうかを判断する関数

	D3DXVECTOR3 m_pos;					//ボタンの位置
	D3DXVECTOR2 m_size;					//ボタンのサイズ
	BUTTON_TYPE m_type;					//ボタンの種類
	D3DXCOLOR   m_normalCol;			//普通のカラー
	D3DXCOLOR   m_TriggeredCol;			//マウスカーソルと重なった時のカラー
	bool		m_bOverlap;				//マウスカーソルと重なっているかどうか

	CUIString*  m_pString;				//ボタンの配列

};



#endif