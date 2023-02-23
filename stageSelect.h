//=============================================================================
//
// stageSelect.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef STAGE_SELECT_H
#define STAGE_SELECT_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"

//=============================================================================
//前方宣言
//=============================================================================
class CStageSelectCursor;
class CAnimateUI;


class CStageSelect : public CMode
{
public:

	enum STAGE
	{
		FIRST_STAGE = 0,
		SECOND_STAGE,

		STAGE_MAX
	};

	CStageSelect();
	~CStageSelect() override;

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理
												
	static CStageSelect* Create(void);			//生成処理

private:

	static const D3DXVECTOR3 DEFAULT_STRING_POS;			//ディフォルトの文字列の位置
	static const D3DXVECTOR2 DEFAULT_STRING_SIZE;			//ディフォルトの文字列のサイズ
	static const D3DXVECTOR3 CURSOR_POS[2];					//カーソルの位置

	int m_nSelectedStage;				//現在のステージインデックス

	CStageSelectCursor* m_pCursor;		//カーソルへのポインタ
	CAnimateUI* m_pLogo[STAGE_MAX];		//ステージのロゴへのポインタ

};




#endif