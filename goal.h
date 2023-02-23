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
#include "UIString.h"


class CGoal : public CModel
{
public:
	CGoal();						//コンストラクタ
	~CGoal() override;				//デストラクタ
									
	HRESULT Init(void);				//初期化処理
	void Uninit(void);				//終了処理
	void Update(void);				//更新処理

	void AddGem(void);				//宝石の加算処理
	void SubtractGem(void);			//宝石の減算処理

	static CGoal* Create(const D3DXVECTOR3 pos);			//生成処理

private:

	static const float DEFAULT_RADIUS;				//ディフォルトの半径

	int m_nPresentGem;			//現在の宝石数
	bool m_bCreate;				//UIを生成したかどうか

	CUIString* m_pGemNeeded;	//必要な宝石のUI文字列へのポインタ

};




#endif