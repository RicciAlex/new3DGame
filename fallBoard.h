//=============================================================================
//
// fallBoard.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _FALL_BOARD_H_
#define _FALL_BOARD_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBoxHitbox;


class CFallBoard : public CModel
{
public:

	static const int DEFAULT_FALL_DELAY = 60;				//落下する前のフレーム数

	CFallBoard();							//コンストラクタ
	~CFallBoard() override;					//デストラクタ

	HRESULT Init(void) override;			//初期化処理
	void Uninit(void) override;				//終了処理
	void Update(void) override;				//更新処理

	static CFallBoard* Create(const D3DXVECTOR3 pos);								//生成処理
	static CFallBoard* Create(const D3DXVECTOR3 pos, const int nFallDelay);			//生成処理

private:

	static const float DEFAULT_FALL_ACCELERATION;			//ディフォルトの落下加速
	static const D3DXVECTOR3 DEFAULT_BOARD_SIZE;			//ディフォルトのモデルサイズ

	D3DXVECTOR3 m_startingPos;				//元の位置
	int	  m_nCntFall;						//落下用のカウンター
	int   m_nFallDelay;						//落下するまでのフレーム数
	float m_fFallSpeed;						//落下速度
	bool  m_bFall;							//落下するかどうか

	CBoxHitbox* m_pHitbox;					//ヒットボックス

};




#endif