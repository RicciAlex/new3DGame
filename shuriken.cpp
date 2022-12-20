//=============================================================================
//
// shuriken.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "shuriken.h"
#include "BoxHitbox.h"
#include "application.h"
#include "rendering.h"
#include "camera.h"
#include "directionalLight.h"
#include "phongShading.h"

//コンストラクタ
CShuriken::CShuriken()
{
	//メンバー変数をクリアする
	m_move = Vec3Null;
	m_nLife = 0;

	m_pHitbox = nullptr;
}

//デストラクタ
CShuriken::~CShuriken()
{

}

//初期化処理
HRESULT CShuriken::Init(void)
{
	if (FAILED(CModel::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	//メンバー変数を初期化する
	m_move = Vec3Null;
	m_nLife = 120;

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CShuriken::Uninit(void)
{
	if (m_pHitbox)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}
}

//更新処理
void CShuriken::Update(void)
{
	CModel::Update();

	D3DXVECTOR3 pos = GetPos() + m_move;
	SetPos(pos);

	if (m_pHitbox)
	{
		m_pHitbox->SetPos(GetPos());

		if (m_pHitbox->GetCollisionState())
		{
			m_pHitbox->SetCollisionState(false);
		}
	}
	
	m_nLife--;

	if (m_nLife <= 0)
	{
		Release();
	}
}

void CShuriken::Draw(void)
{
	CPhongShading* pPhong = CApplication::GetRenderer()->GetPhongEffect();

	if (pPhong)
	{
		D3DXVECTOR3 posV = CApplication::GetCamera()->GetPos();		//視点の取得

																	//視点の位置をVector4に変換する
		D3DXVECTOR4 cameraPos = {};

		cameraPos.x = posV.x;
		cameraPos.y = posV.y;
		cameraPos.z = posV.z;
		cameraPos.w = 1.0f;

		//位置を取得してから、Vector4に変換して、正規化する
		D3DXVECTOR3 l = CDirectionalLight::GetPrincipalLightDir();
		D3DXVec3Normalize(&l, &l);
		D3DXVECTOR4 light = D3DXVECTOR4(posV.x - l.x, posV.y - l.y, posV.z - l.z, 0.0f);
		D3DXVec3Normalize((D3DXVECTOR3*)&light, (D3DXVECTOR3*)&light);

		pPhong->Begin();											//シェーダーエフェクトの開始処理
		pPhong->SetAmbient(0.50f);									//環境光の設定
		pPhong->SetSpecular(40.0f);									//スペキュラーの範囲の設定
		pPhong->SetSpecularPower(0.75f);							//スペキュラーの強度の設定
		pPhong->SetMatrix(GetWorldMatrix(), &cameraPos, &light);	//ワールドマトリックスの設定
		pPhong->BeginPass();										//パスの開始
	}

	//基本クラスの描画処理
	CModel::Draw();

	if (pPhong)
	{
		pPhong->EndPass();		//パスの終了処理
		pPhong->End();			//シェーダーエフェクトの終了処理
	}
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CShuriken* CShuriken::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 speed)
{
	CShuriken* pShuriken = new CShuriken;

	if (FAILED(pShuriken->Init()))
	{
		return nullptr;
	}

	pShuriken->SetPos(pos);
	pShuriken->m_move = speed;
	pShuriken->SetModel(CModel::MODEL_SHURIKEN);
	pShuriken->SetShadowDraw(false);
	pShuriken->StartRotation(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.1f));

	pShuriken->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(17.0f, 20.0f, 17.0f), CHitbox::TYPE_OBSTACLE, pShuriken, -1, CHitbox::EFFECT_DAMAGE);

	return pShuriken;
}

CShuriken* CShuriken::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 speed, const float fShadowHeight)
{
	CShuriken* pShuriken = new CShuriken;

	if (FAILED(pShuriken->Init()))
	{
		return nullptr;
	}

	pShuriken->SetPos(pos);
	pShuriken->m_move = speed;
	pShuriken->SetModel(CModel::MODEL_SHURIKEN);
	pShuriken->SetShadowHeight(fShadowHeight);
	pShuriken->StartRotation(D3DXVECTOR3(0.0f, 0.0f, D3DX_PI * 0.1f));

	pShuriken->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), D3DXVECTOR3(17.0f, 20.0f, 17.0f), CHitbox::TYPE_OBSTACLE, pShuriken, -1, CHitbox::EFFECT_DAMAGE);

	return pShuriken;
}