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

private:

	void UpdateParticle(void);

	static const float DEFAULT_VIEW_RANGE;	//ディフォルトの見える範囲の半径
	static D3DXVECTOR3 DEFAULT_PARTICLE_RELATIVE_POS;		//パーティクルのディフォルトの相対位置
	static const float DEFAULT_FRAME_ANGLE;	//アニメーション用の角度
	static const float DEFAULT_ANIM_AMPLITUDE;

	float m_fAnimAngle;						//アニメーション用の角度
	float m_fRange;							//見える範囲の半径
	bool  m_bActive;						//プレイヤーが見えるかどうか

	CFogParticle* m_pParticle;				//パーティクルへのポインタ
	CBoxHitbox*   m_pHitbox;				//ヒットボックスへのポインタ

};




#endif