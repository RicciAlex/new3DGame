//=============================================================================
//
// accelerationFloor.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef ACCELERATION_FLOOR_H
#define ACCELERATION_FLOOR_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object3D.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBoxHitbox;


class CAccelerationFloor : public CObject_3D
{
public:
	CAccelerationFloor();						//コンストラクタ
	~CAccelerationFloor() override;				//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理

	void SetSpeed(const D3DXVECTOR2 speed);		//速度の設定処理
	void SetSpeed(const float speedX, const float speedY);			//速度の設定処理

	void SetTextureTiling(const D3DXVECTOR2 tiling) override;					//テクスチャの大きさの設定処理
	void SetTextureTiling(const float fTiling) override;				//テクスチャの大きさの設定処理
	void SetTextureTiling(const float fTilingX, const float fTilingY) override;					//テクスチャの大きさの設定処理

	
	static CAccelerationFloor* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXVECTOR2 speed);		//生成処理
	static CAccelerationFloor* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXVECTOR2 speed, CObject::TextType texture);		//生成処理

private:

	bool m_bActive;
	D3DXVECTOR2 m_speed;

	CBoxHitbox* m_pHitbox;

};


#endif