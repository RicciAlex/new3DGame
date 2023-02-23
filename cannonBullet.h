//=============================================================================
//
// cannonBullet.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _CANNON_BULLET_H_
#define _CANNON_BULLET_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBoss;


class CCannonBullet : public CModel
{
public:

	CCannonBullet();				//コンストラクタ
	~CCannonBullet() override;		//デストラクタ

	HRESULT Init(void) override;	//初期化処理
	void Uninit(void) override;		//終了処理
	void Update(void) override;		//更新処理

	static CCannonBullet* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 target);			//生成処理
	static CCannonBullet* Create(const D3DXVECTOR3 pos, CBoss* pBoss);			//生成処理

private:

	void SetSpeed(const D3DXVECTOR3 target);		//速度の設定処理

	static const float GRAVITY_ACCELERATION;		//重力加速度
	static const int DEFAULT_LIFE;					//ディフォルトのライフ

	D3DXVECTOR3 m_move;		//速度
	int m_nLife;			//ライフ
	CBoss* m_pBoss;			//ボスへのポインタ

};


#endif