//=============================================================================
//
// menu.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _MENU_H
#define _MENU_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CObject_2D;


class CMenu
{
public:

	CMenu();									//コンストラクタ
	virtual ~CMenu();							//デストラクタ

	virtual HRESULT Init(void);					//初期化処理
	virtual void Uninit(void);					//終了処理
	virtual void Update(void);					//更新処理
	virtual void Draw(void);					//描画処理

	virtual void SetPos(const D3DXVECTOR3 pos);	//位置の設定処理

	const D3DXVECTOR3 GetPos(void);				//位置の取得処理

protected:

	void CreateBg(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, CObject::TextType texture);		//背景生成処理

	const CObject_2D* GetBg(void);			//背景の取得処理

private:

	D3DXVECTOR3 m_pos;				//位置

	CObject_2D* m_pBg;				//メニューの背景

};



#endif