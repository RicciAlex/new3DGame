//=============================================================================
//
// accelerationFloor.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "accelerationFloor.h"
#include "BoxHitbox.h"
#include "application.h"
#include "game.h"
#include "player.h"


//コンストラクタ
CAccelerationFloor::CAccelerationFloor()
{
	//メンバー変数をクリアする
	m_bActive = false;
	m_speed = Vec2Null;

	m_pHitbox = nullptr;
}

//デストラクタ
CAccelerationFloor::~CAccelerationFloor()
{

}

//初期化処理
HRESULT CAccelerationFloor::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CObject_3D::Init()))
	{
		return -1;
	}

	//メンバー変数を初期化する
	m_bActive = true;
	m_speed = Vec2Null;

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CAccelerationFloor::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//ポインタをnullにする
	}

	//基本クラスの終了処理
	CObject_3D::Uninit();
}

//更新処理
void CAccelerationFloor::Update(void)
{
	//基本クラスの更新処理
	CObject_3D::Update();
}

//テクスチャの移動量の設定処理
void CAccelerationFloor::SetTextureTiling(const D3DXVECTOR2 tiling)
{
	CObject_3D::SetTextureTiling(tiling);
	MoveTexCoordinates(D3DXVECTOR2(m_speed.x * -0.01f * tiling.x, m_speed.y * 0.01f * tiling.y));
}

//テクスチャの大きさの設定処理
void CAccelerationFloor::SetTextureTiling(const float fTiling)
{
	CObject_3D::SetTextureTiling(fTiling);
	MoveTexCoordinates(D3DXVECTOR2(m_speed.x * -0.01f * fTiling, m_speed.y * 0.01f * fTiling));
}

//テクスチャの大きさの設定処理
void CAccelerationFloor::SetTextureTiling(const float fTilingX, const float fTilingY)
{
	CObject_3D::SetTextureTiling(fTilingX, fTilingY);
	MoveTexCoordinates(D3DXVECTOR2(m_speed.x * -0.01f * fTilingX, m_speed.y * 0.01f * fTilingY));
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CAccelerationFloor* CAccelerationFloor::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXVECTOR2 speed)
{
	CAccelerationFloor* pFloor = new CAccelerationFloor;		//インスタンスを生成する

	if (FAILED(pFloor->Init()))
	{//初期化処理
		return nullptr;
	}

	pFloor->SetPos(pos);
	pFloor->SetSize(size);
	pFloor->m_bActive = true;
	pFloor->m_speed = speed;
	pFloor->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
	pFloor->MoveTexCoordinates(D3DXVECTOR2(pFloor->m_speed.x * -0.01f, pFloor->m_speed.y * 0.01f));

	if (speed.x > 0.0f)
	{
		pFloor->SetTexture(CObject::TEXTURE_ARROW_TILE_RIGHT);
	}
	else if(speed.x < 0.0f)
	{
		pFloor->SetTexture(CObject::TEXTURE_ARROW_TILE_LEFT);
	}
	else if (speed.y > 0.0f)
	{
		pFloor->SetTexture(CObject::TEXTURE_ARROW_TILE_UP);
	}
	else if (speed.y < 0.0f)
	{
		pFloor->SetTexture(CObject::TEXTURE_ARROW_TILE_DOWN);
	}

	pFloor->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, -9.0f, 0.0f), D3DXVECTOR3(size.x, 10.0f, size.y), CHitbox::TYPE_NEUTRAL, pFloor);

	if (pFloor->m_pHitbox)
	{
		pFloor->m_pHitbox->SetAcceleration(D3DXVECTOR3(speed.x, 0.0f, speed.y));
	}

	return pFloor;
}

//生成処理
CAccelerationFloor * CAccelerationFloor::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXVECTOR2 speed, CObject::TextType texture)
{
	CAccelerationFloor* pFloor = new CAccelerationFloor;		//インスタンスを生成する

	if (FAILED(pFloor->Init()))
	{//初期化処理
		return nullptr;
	}

	pFloor->SetPos(pos);
	pFloor->SetSize(size);
	pFloor->m_bActive = true;
	pFloor->m_speed = speed;
	pFloor->SetRot(D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f));
	pFloor->MoveTexCoordinates(D3DXVECTOR2(pFloor->m_speed.x * -0.01f, pFloor->m_speed.y * 0.01f));
	pFloor->SetTexture(texture);

	pFloor->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, -9.0f, 0.0f), D3DXVECTOR3(size.x, 10.0f, size.y), CHitbox::TYPE_NEUTRAL, pFloor);

	if (pFloor->m_pHitbox)
	{
		pFloor->m_pHitbox->SetAcceleration(D3DXVECTOR3(speed.x, 0.0f, speed.y));
	}

	return pFloor;
}
