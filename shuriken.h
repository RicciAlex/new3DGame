//=============================================================================
//
// shuriken.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SHURIKEN_H
#define SHURIKEN_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBoxHitbox;

class CShuriken : public CModel
{
public:
	CShuriken();				//コンストラクタ
	~CShuriken() override;		//デストラクタ

	HRESULT Init(void);			//初期化処理
	void Uninit(void);			//終了処理
	void Update(void);			//更新処理

	static CShuriken* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 speed);		//生成処理
	static CShuriken* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 speed, const float fShadowHeight);		//生成処理

private:

	D3DXVECTOR3 m_move;						//速度
	int			m_nLife;					//ライフ
	
	CBoxHitbox* m_pHitbox;				//ヒットボックス

};




#endif