//=============================================================================
//
// iceBoulder.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _ICE_BOULDER_H_
#define _ICE_BOULDER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCylinderHitbox;


class CIceBoulder : public CModel
{
public:

	CIceBoulder();					//コンストラクタ
	~CIceBoulder() override;		//デストラクタ
									
	HRESULT Init(void) override;	//初期化処理
	void Uninit(void) override;		//終了処理
	void Update(void) override;		//更新処理


	static CIceBoulder* Create(const D3DXVECTOR3 pos);			//生成処理

private:

	void SetSpeed(void);				//速度の設定処理
	void UpdateHitbox(void);			//ヒットボックスの更新処理
	void CreateShard(void);				//破片の生成処理

	static const float DEFAULT_GRAVITY_ACCELERATION;			//重力
	static const int   ATTACK_FRAME;							//攻撃のフレーム数
	static const int   SHARD_NUMBER;							//破片の数
	static const D3DXVECTOR3 HITBOX_RELATIVE_POS;				//ヒットボックスの相対位置
	static const D3DXVECTOR3 HITBOX_SIZE;						//ヒットボックスのサイズ

	
	D3DXVECTOR3 m_target;				//目的の位置
	D3DXVECTOR3 m_move;					//速度

	CCylinderHitbox* m_pHitbox;			//ヒットボックスへのポインタ

};



#endif