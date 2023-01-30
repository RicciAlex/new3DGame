//=============================================================================
//
// spikeTrap.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SPIKE_TRAP_H
#define SPIKE_TRAP_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBoxHitbox;

class CSpikeTrap : public CModel
{
public:

	static const int DEFAULT_DELAY = 60;			//ディフォルトのディレイ
	static const float DEFAULT_SPEED;				//ディフォルトの速度

	CSpikeTrap();							//コンストラクタ
	~CSpikeTrap() override;					//デストラクタ

	HRESULT Init(void) override;			//初期化処理
	void Uninit(void) override;				//終了処理
	void Update(void) override;				//更新処理
	void Draw(void) override;				//描画処理

	void SetStartingDelay(const int nDelay);//初期時のディレイの設定処理
	void SetPos(const D3DXVECTOR3 pos) override;		//位置の設定処理

	static CSpikeTrap* Create(const D3DXVECTOR3 pos);										//生成処理
	static CSpikeTrap* Create(const D3DXVECTOR3 pos, const float fSpeed);					//生成処理
	static CSpikeTrap* Create(const D3DXVECTOR3 pos, const float fSpeed, const int nDelay);	//生成処理(delayというのは下げたら、前回上がるまでのフレームです。デフォルトは60)
	static CSpikeTrap* Create(const D3DXVECTOR3 pos, const float fSpeed, const int nDelay, const int nStartDelay);	//生成処理

private:

	static const float DEFAULT_SPIKE_HEIGHT;		//はじめのスパイクのY座標
	static const D3DXVECTOR3 DEFAULT_HITBOX_SIZE;	//ディフォルトのヒットボックスサイズ

	int m_nDelay;			//ディレイ
	int m_nCntTime;			//アニメーションカウンター
	float m_fSpeed;			//速度
	float m_fStartingHeight;//初期時の高さ
	bool m_bMoving;			//動いているかどうか

	CBoxHitbox* m_pHitbox;	//ヒットボックスへのポインタ
	CModel*		m_pModel;	//モデルへのポインタ

};



#endif