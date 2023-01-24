//=============================================================================
//
// triggerablePlatform.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef TRIGGERABLE_PLATFORM_H
#define TRIGGERABLE_PLATFORM_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CButton;
class CMovingCube;

class CTriggerablePlatform : public CObject
{
public:
	CTriggerablePlatform();						//コンストラクタ
	~CTriggerablePlatform() override;			//デストラクタ

	HRESULT Init(void) override;										//初期化処理
	void Uninit(void) override;											//終了処理
	void Update(void) override;											//更新処理
	void Draw(void) override;											//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;						//位置の設定処理
	void SetOriginalPos(const D3DXVECTOR3 oPos);						//元の位置の設定処理
	void SetButtonPos(const D3DXVECTOR3 pos);							//ボタンの位置の設定処理

	const D3DXVECTOR3 GetPos(void) override;							//位置の取得処理
	const D3DXVECTOR3 GetButtonPos(void);								//ボタンの位置の取得処理
	const bool GetTriggeredState(void);									//ボタンが押されたらかどうかの取得処理

	static CTriggerablePlatform* Create(const D3DXVECTOR3 pos, 
		const D3DXVECTOR3 buttonPos, const D3DXVECTOR3 move, const float fRange);		//生成処理

private:

	D3DXVECTOR3 m_move;							//ボタンが押した後の速度
	bool		m_bTriggered;					//ボタンが押されたかどうか

	CButton* m_pButton;							//ボタンへのポインタ
	CMovingCube* m_pPlatform;					//プラットフォームへのポインタ
};

#endif