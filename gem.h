//=============================================================================
//
// gem.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _GEM_H
#define _GEM_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"
#include "goal.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBoxHitbox;


class CGem : public CModel
{
public:
	CGem();							//コンストラクタ
	~CGem() override;				//デストラクタ
									
	HRESULT Init(void) override;	//初期化処理
	void Uninit(void) override;		//終了処理
	void Update(void) override;		//更新処理

	static CGem* Create(const D3DXVECTOR3 pos);		//生成処理
	static CGem* Create(const D3DXVECTOR3 pos, const D3DXCOLOR col);		//生成処理
	static CGem* Create(const D3DXVECTOR3 pos, const D3DXCOLOR col, const float fShadowHeight);		//生成処理
	static CGem* Create(const D3DXVECTOR3 pos, const D3DXCOLOR col, const float fShadowHeight, const D3DXVECTOR3 newPos, CGoal* pGoal);		//生成処理

private:

	static const float DEFAULT_SCALE;			//ディフォルトのスケールの係数
	static const D3DXVECTOR3 DEFAULT_ROTATION;	//ディフォルトの回転速度
	static const D3DXVECTOR3 DEFAULT_SIZE;		//ディフォルトのサイズ


	D3DXVECTOR3 m_newPos;						//新しい位置

	CBoxHitbox* m_pHitbox;						//ヒットボックスへのポインタ
};


#endif