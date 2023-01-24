//=============================================================================
//
// bgModel.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _BG_MODEL_H
#define _BG_MODEL_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"


class CBgModel : public CModel
{
public:

	CBgModel();						//コンストラクタ
	~CBgModel() override;			//デストラクタ

	HRESULT Init(void) override;	//初期化処理
	void Uninit(void) override;		//終了処理
	void Update(void) override;		//更新処理

	static CBgModel* Create(CModel::ModelType type, const D3DXVECTOR3 pos);									//生成処理
	static CBgModel* Create(CModel::ModelType type, const D3DXVECTOR3 pos, const D3DXVECTOR3 move);			//生成処理

private:

	D3DXVECTOR3 m_move;					//速度

};


#endif