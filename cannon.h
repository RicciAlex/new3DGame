//=============================================================================
//
// cannon.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _CANNON_H_
#define _CANNON_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBoxHitbox;
class CButton;
class CBoss;

class CCannon : public CModel
{
public:

	CCannon();					//コンストラクタ
	~CCannon() override;		//デストラクタ

	HRESULT Init(void) override;	//初期化処理
	void Uninit(void) override;		//終了処理
	void Update(void) override;		//更新処理

	static CCannon* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 buttonPos, CBoss* pBoss);		//生成処理

private:

	static const D3DXVECTOR3 HITBOX_SIZE;			//ヒットボックスのサイズ

	bool m_bFired;				//弾を撃ったかどうか

	CButton* m_pButton;			//ボタンへのポインタ
	CBoxHitbox* m_pHitbox;		//ヒットボックスへのポインタ
	CBoss* m_pBoss;				//ボスへのポインタ

};


#endif