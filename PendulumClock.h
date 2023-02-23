//=============================================================================
//
// PendulumClock.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _PENDULUM_CLOCK_H
#define _PENDULUM_CLOCK_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBoxHitbox;
class CModelPart;
class CObject_2D;


class CPendulumClock : public CModel
{
public:

	static const float DEFAULT_RANGE;		//ディフォルトの有効範囲


	CPendulumClock();					//コンストラクタ
	~CPendulumClock() override;			//デストラクタ
										
	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理
	void Draw(void) override;			//描画処理

	void SetRange(const float fRange);	//有効範囲の設定処理

	static CPendulumClock* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fShadowHeight);		//生成処理
	static CPendulumClock* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fShadowHeight, const float fRange);		//生成処理

private:

	void CheckPlayer(void);

	static const int NEEDLE_NUMBER = 2;		//針の数
	static const float DEFAULT_ANIM_FRAME_ANGLE;		//毎フレーム加算されている角度
	static const float MIN_RANGE;			//最小の有効範囲

	int				m_nCntSound;		//サウンド用のカウンター
	float			m_fAnimAngle;		//アニメーション用の角度
	float			m_fAnimCoeff;		//アニメーション用の角度
	float			m_fRange;			//有効範囲
	bool			m_bVisible;			//UIが表情されているかどうか
	bool			m_bSound;			//サウンドが再生されているかどうか

	CModelPart*		m_pPendulum;		//ペンジュラムのモデルへのポインタ
	CModelPart*		m_pNeedle[NEEDLE_NUMBER];		//針へのポインタ
	CObject_2D*		m_pUI;			//UIへのポインタ
	CBoxHitbox* m_pHitbox;			//ヒットボックスへのポインタ
};


#endif