//=============================================================================
//
// fogbot.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _FOGBOT_H
#define _FOGBOT_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
//前方宣言
//=============================================================================
class CFogParticle;
class CBoxHitbox;


class CFogbot : public CModel
{
public:
	CFogbot();								//コンストラクタ
	~CFogbot() override;					//デストラクタ

	HRESULT Init(void) override;			//初期化処理
	void Uninit(void) override;				//終了処理
	void Update(void) override;				//更新処理

	static CFogbot* Create(const D3DXVECTOR3 pos, const float shadowPos);		//生成処理

protected:

	void CreateDefaultBot(void);			//ディフォルトのボットの生成処理(派生クラス用)
	void ForceActivation(void);				//強制的にアクティブにする
	void Deactivate(void);					//アクティブではない状態にする

private:
	
	void UpdateParticle(void);

	static const float DEFAULT_VIEW_RANGE;	//ディフォルトの見える範囲の半径
	static D3DXVECTOR3 DEFAULT_PARTICLE_RELATIVE_POS;		//パーティクルのディフォルトの相対位置
	static const float DEFAULT_FRAME_ANGLE;	//アニメーション用の角度
	static const float DEFAULT_ANIM_AMPLITUDE;
	static const float DEFAULT_GRAVITY_ACCELERATION;	//重力加速度
	static const D3DXVECTOR3 DEFAULT_HITBOX_SIZE;		//ヒットボックスのディフォルトサイズ
	static const float DEFAULT_DESPAWN_HEIGHT;			//ディフォルトのディスポーンのY座標

	D3DXVECTOR3 m_deathSpeed;				//死亡した後のスピード
	int   m_nCntSound;						//サウンド用のカウンター
	float m_fAnimAngle;						//アニメーション用の角度
	float m_fRange;							//見える範囲の半径
	bool  m_bActive;						//プレイヤーが見えるかどうか
	bool  m_bForceActive;					//強制的にアクティブにするかどうか
	bool  m_bDeath;							//死亡フラグ

	CFogParticle* m_pParticle;				//パーティクルへのポインタ
	CBoxHitbox*   m_pHitbox;				//ヒットボックスへのポインタ

};




#endif