//=============================================================================
//
// button.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _BUTTON_H_
#define _BUTTON_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCylinderHitbox;

class CButton : public CModel
{
public:
	CButton();						//コンストラクタ
	~CButton() override;			//デストラクタ

	HRESULT Init(void) override;	//初期化処理
	void Uninit(void) override;		//終了処理
	void Update(void) override;		//更新処理

	void SetTriggerableOnce(const bool bOnce);		//一回だけ押すことができるかどうかの設定処理

	bool GetTrigger(void);							//押されたかどうかの取得処理

	static CButton* Create(const D3DXVECTOR3 pos);															//生成処理	
	static CButton* Create(const D3DXVECTOR3 pos, const D3DXCOLOR normalCol, const D3DXCOLOR pressedCol);	//生成処理	
	static CButton* Create(const D3DXVECTOR3 pos, const bool bOnce);															//生成処理	
	static CButton* Create(const D3DXVECTOR3 pos, const D3DXCOLOR normalCol, const D3DXCOLOR pressedCol, const bool bOnce);	//生成処理	

private:

	D3DXVECTOR3 m_originalPos;			//元の位置
	D3DXCOLOR m_normalCol;				//普通の色
	D3DXCOLOR m_triggeredCol;			//押された後の色
	bool m_bTriggered;					//押されたかどうか
	bool m_bOnce;						//一回だけ押すことができるかどうか
		
	CCylinderHitbox* m_pHitbox;			//ヒットボックス

};



#endif