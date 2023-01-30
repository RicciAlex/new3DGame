//=============================================================================
//
// spikeTrap.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef STALKING_BOT_H
#define STALKING_BOT_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "fogBot.h"

//=============================================================================
//前方宣言
//=============================================================================


class CStalkingBot : public CFogbot
{
public:

	enum State
	{
		STATE_WAIT = 0,			//待機状態
		STATE_FOLLOW,			//追いかける状態
		STATE_CIRCLE,			//円形移動
		STATE_STAR,				//星の形の移動(メイン状態)
		STATE_RUN,				//逃げる状態

		STATE_MAX
	};

	CStalkingBot();						//コンストラクタ
	~CStalkingBot() override;			//デストラクタ
										
	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理

	//生成処理
	static CStalkingBot* Create(const D3DXVECTOR3 pos, const float fShadowHeight);
	static CStalkingBot* Create(const D3DXVECTOR3 pos, const float fShadowHeight, const float fStartAngle);

private:

	void StateUpdate(void);				//状態によっての更新処理
	bool Activate(void);				//アクティブ状態になったかどうかの判定の処理
	void FollowPlayer(void);			//プレイヤーを追いかける処理		
	void CirclePlayer(void);			//プレイヤーを中心にして、公転する
	void StarCircling(void);			//星の形に動かす
	void RunAway(void);					//逃げる処理

	static const float DEFAULT_APPROACHING_SPEED;				//ディフォルトの追いかける速度
	static const float DEFAULT_ANGLE_SPEED;						//ディフォルトの回転速度
	static const float DEFAULT_FIRST_COEFF;						//ディフォルトの最初のパラメータ(パラメトリック方程式用)
	static const float DEFAULT_SECOND_COEFF;					//ディフォルトの二番目のパラメータ(パラメトリック方程式用)
	static const float DEFAULT_AMPLITUDE;						//ディフォルトの拡大率
	static const float DEFAULT_ACTIVATION_DISTANCE;				//ディフォルトのアクティブ状態になる距離
	static const float DEFAULT_CIRCLE_RANGE;					//ディフォルトの円形の半径
	static const float DEFAULT_MAX_STAR_ANGLE;					//ディフォルトの最大角度(この角度を超えたら、逃げる状態になる)
	static const float DEFAULT_RUN_DISTANCE;					//ディフォルトの逃げる距離
	static const D3DXVECTOR3 DEFAULT_RELATIVE_POS;				//ディフォルトの相対位置

	D3DXVECTOR3 m_center;					//中心点
	D3DXVECTOR3 m_move;						//速度
	float		m_fPresentAngle;			//現在の角度
	float		m_fStarRange;				//星の形の動きの半径

	State		m_state;					//状態

};

#endif