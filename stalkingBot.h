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
	CStalkingBot();						//コンストラクタ
	~CStalkingBot() override;			//デストラクタ
										
	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理

	//生成処理
	static CStalkingBot* Create(const D3DXVECTOR3 pos, const float fShadowHeight);
	static CStalkingBot* Create(const D3DXVECTOR3 pos, const float fShadowHeight, const float fStartAngle);

private:

	static const float DEFAULT_APPROACHING_SPEED;				//ディフォルトの追いかける速度
	static const float DEFAULT_ANGLE_SPEED;						//ディフォルトの回転速度
	static const float DEFAULT_FIRST_COEFF;						//ディフォルトの最初のパラメータ(パラメトリック方程式用)
	static const float DEFAULT_SECOND_COEFF;					//ディフォルトの二番目のパラメータ(パラメトリック方程式用)
	static const float DEFAULT_AMPLITUDE;						//ディフォルトの拡大率
	static const D3DXVECTOR3 DEFAULT_RELATIVE_POS;				//ディフォルトの相対位置

	D3DXVECTOR3 m_move;
	float		m_fPresentAngle;

};

#endif