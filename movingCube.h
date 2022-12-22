//=============================================================================
//
// movingCube.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef MOVING_CUBE_H
#define MOVING_CUBE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBoxHitbox;

class CMovingCube : public CModel
{
public:

	CMovingCube();									//コンストラクタ
	~CMovingCube() override;						//デストラクタ
													
	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;	//位置の設定処理
	void SetOriginalPos(const D3DXVECTOR3 oPos);	//元の位置の設定処理

	void SetMove(const D3DXVECTOR3 move);			//速度の設定処理
	void SetMove(const D3DXVECTOR3 move, const float fRange);			//速度の設定処理

	static CMovingCube* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fRange);		//生成処理

private:

	void ClampPos(void);				//位置を制限する処理
	void PushOut(void);					//プレイヤーの押し出す処理

	static const D3DXVECTOR3 m_metalBoxSize;

	D3DXVECTOR3 m_OriginalPos;			//元の位置
	D3DXVECTOR3 m_move;					//速度
	D3DXVECTOR3 m_size;					//サイズ
	float       m_fRange;				//移動の限界

	CBoxHitbox* m_pHitbox;				//ヒットボックスへのポインタ
};


#endif