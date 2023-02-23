//=============================================================================
//
// animationFade.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef ANIMATION_FADE_H
#define ANIMATION_FADE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object2D.h"

class CAnimationFade : public CObject_2D
{
public:

	enum FADE_ANIMATION_TYPE
	{
		TYPE_NORMAL = 0,
		TYPE_PLATFORM,

		TYPE_MAX
	};

	CAnimationFade();				//コンストラクタ
	~CAnimationFade() override;		//デストラクタ
									
	HRESULT Init(void) override;	//初期化処理
	void Uninit(void) override;		//終了処理
	void Update(void) override;		//更新処理

	static CAnimationFade* Create(const D3DXVECTOR3 cameraPos, const D3DXVECTOR3 focalPoint, FADE_ANIMATION_TYPE type);		//生成処理

private:

	static const float DEFAULT_FADE_SPEED;				//ディフォルトのフェードスピード
	static const int   DEFAULT_ANIM_FRAMES[TYPE_MAX];	//ディフォルトのアニメーションフレーム数

	enum FADE_PHASE
	{
		START_OUT = 0,
		START_IN,
		ANIM_PAUSE,
		END_OUT,
		END_IN,

		PHASE_MAX
	};

	bool FadeOut(void);				//フェードアウトの関数
	bool FadeIn(void);				//フェードインの関数
	void PlatformAnim(void);		//プラットフォームアニメーション
	void NormalAnim(void);			//普通のアニメーション

	D3DXVECTOR3			m_startingPos;		//カメラの元の位置
	D3DXVECTOR3			m_cameraPos;		//カメラの位置
	D3DXVECTOR3			m_startingFocal;		//注視点の元の位置
	D3DXVECTOR3			m_focalPos;		//注視点の位置
	int					m_nAnimFrame;		//アニメーションのフレーム数
	FADE_ANIMATION_TYPE m_type;				//アニメーションの種類
	FADE_PHASE			m_phase;			//状態

};


#endif