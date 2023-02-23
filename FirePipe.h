//=============================================================================
//
// FirePipe.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _FIRE_PIPE_H
#define _FIRE_PIPE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
//前方宣言
//=============================================================================
class CFireParticle;
class CCylinderHitbox;


class CFirePipe : public CModel
{
public:

	static const int DEFAULT_FIRE_TIME = 180;	//ディフォルトの火を消す/付けるまでのフレーム数

	CFirePipe();						//コンストラクタ
	~CFirePipe() override;				//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理
	void Draw(void) override;

	static CFirePipe* Create(const D3DXVECTOR3 pos);							//生成処理
	static CFirePipe* Create(const D3DXVECTOR3 pos, const int nFireTime);		//生成処理
	static CFirePipe* Create(const D3DXVECTOR3 pos, const int nFireTime, const int nStartDelay);		//生成処理

private:

	static const int MIN_FIRE_TIME = 1;			//火を消す/付けるまでのフレーム数の最小値
	static const D3DXVECTOR3 FIRE_HITBOX_SIZE;	//火のヒットボックスのサイズ
	static const D3DXVECTOR3 HITBOX_SIZE;		//ヒットボックスのサイズ

	int m_nCntTime;						//現在のフレーム
	int m_nFireTime;					//火を消す/付けるまでのフレーム数
	int m_nCntSound;					//サウンドのカウンター

	CFireParticle* m_pParticle;			//パーティクルへのポインタ
	CCylinderHitbox* m_pHitbox;			//ヒットボックスへのポインタ
	CCylinderHitbox* m_pFireHitbox;		//火のヒットボックスへのポインタ

};



#endif