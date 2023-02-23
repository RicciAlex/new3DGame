//=============================================================================
//
// stageSelectCursor.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _STAGE_SELECT_CURSOR_H_
#define _STAGE_SELECT_CURSOR_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CModel;


class CStageSelectCursor : public CObject
{
public:

	CStageSelectCursor();							//コンストラクタ
	~CStageSelectCursor() override;					//デストラクタ

	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;	//位置の設定処理

	const D3DXVECTOR3 GetPos(void) override;		//位置の取得処理

	static CStageSelectCursor* Create(const D3DXVECTOR3 pos);		//生成処理

private:

	static const int JEWEL_NUMBER = 12;			//宝石の数
	static const D3DXVECTOR3 RELATIVE_POS[JEWEL_NUMBER];		//宝石の相対位置
	static const D3DXCOLOR JEWEL_COLOR[JEWEL_NUMBER / 2];		//宝石の色

	D3DXVECTOR3 m_pos;							//位置

	CModel* m_pModel[JEWEL_NUMBER];				//モデルへのポインタ

};


#endif