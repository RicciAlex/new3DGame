//=============================================================================
//
// goal.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _GOAL_H
#define _GOAL_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"


class CGoal : public CModel
{
public:
	CGoal();						//コンストラクタ
	~CGoal() override;				//デストラクタ
									
	HRESULT Init(void);				//初期化処理
	void Uninit(void);				//終了処理
	void Update(void);				//更新処理

	static CGoal* Create(const D3DXVECTOR3 pos);			//生成処理

private:

};




#endif