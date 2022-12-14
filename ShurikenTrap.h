//=============================================================================
//
// ShurikenTrap.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SHURIKEN_TRAP_H
#define SHURIKEN_TRAP_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCylinderHitbox;
class CButton;


class CShurikenTrap : CObject
{
public:
	CShurikenTrap();									//コンストラクタ
	~CShurikenTrap() override;							//デストラクタ
														
	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理
	void Draw(void) override;							//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;		//位置の設定処理
	const D3DXVECTOR3 GetPos(void) override;			//位置の取得処理

	static CShurikenTrap* Create(const D3DXVECTOR3 pos, const float Yrot, const float fDistance);	//生成処理
	static CShurikenTrap* Create(const D3DXVECTOR3 pos, const float Yrot, const float fDistance, 
								 const D3DXCOLOR buttonCol, const D3DXCOLOR triggeredCol);			//生成処理

private:

	D3DXVECTOR3 m_spawnPos;				//弾の発生位置
	D3DXVECTOR3 m_rot;					//向き
	int			m_nDelay;				//ディレイ

	CButton*	m_pButton;				//ボタンへのポインタ
	CCylinderHitbox* m_pHitbox;			//ヒットボックス
};



#endif