//=============================================================================
//
// effect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "effect.h"
#include "application.h"
#include "rendering.h"

//コンストラクタ
CEffect::CEffect()
{
	//メンバー変数をクリアする
	m_nLife = 0;
	m_move = Vec3Null;
}

//デストラクタ
CEffect::~CEffect()
{

}

//初期化処理
HRESULT CEffect::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CBillboard::Init()))
	{
		return -1;
	}

	//メンバー変数を初期化する
	m_nLife = DEFAULT_LIFE;
	m_move = Vec3Null;

	return S_OK;
}

//終了処理
void CEffect::Uninit(void)
{
	//基本クラスの終了処理
	CBillboard::Uninit();
}

//更新処理
void CEffect::Update(void)
{
	m_nLife--;

	if (m_nLife <= 0)
	{
		Release();
		return;
	}

	if (D3DXVec3Length(&m_move) > 0.0f)
	{
		SetPos(GetPos() + m_move);
	}

	//基本クラスの更新処理
	CBillboard::Update();
}

//描画処理
void CEffect::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();				//デバイスの取得
	
	//加算合成の設定
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//基本クラスの描画処理
	CBillboard::Draw();

	//設定を元に戻す
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//速度の設定処理
void CEffect::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}

//ライフの設定処理
void CEffect::SetLife(const int nLife)
{
	m_nLife = nLife;
}

//速度の取得処理
const D3DXVECTOR3 CEffect::GetMove(void)
{
	return m_move;
}



//=============================================================================
//
//									静的関数
//
//=============================================================================


//生成処理
CEffect* CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col)
{
	CEffect* pEffect = new CEffect;		//インスタンスを生成する

	//初期化処理
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	pEffect->SetPos(pos);				//位置の設定
	pEffect->SetSize(size);				//サイズの設定
	pEffect->SetColor(col);				//色の設定

	return pEffect;						//生成したインスタンスを返す
}

//生成処理
CEffect* CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const int nLife)
{
	CEffect* pEffect = new CEffect;		//インスタンスを生成する

										//初期化処理
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	pEffect->SetPos(pos);				//位置の設定
	pEffect->SetSize(size);				//サイズの設定
	pEffect->SetColor(col);				//色の設定
	pEffect->m_nLife = nLife;			//ライフの設定

	return pEffect;						//生成したインスタンスを返す
}

//生成処理
CEffect * CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const D3DXVECTOR3 move)
{
	CEffect* pEffect = new CEffect;		//インスタンスを生成する

										//初期化処理
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	pEffect->SetPos(pos);				//位置の設定
	pEffect->SetSize(size);				//サイズの設定
	pEffect->SetColor(col);				//色の設定
	pEffect->m_move = move;				//速度の設定

	return pEffect;						//生成したインスタンスを返す
}

//生成処理
CEffect* CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const int nLife, const D3DXVECTOR3 move)
{
	CEffect* pEffect = new CEffect;		//インスタンスを生成する

										//初期化処理
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	pEffect->SetPos(pos);				//位置の設定
	pEffect->SetSize(size);				//サイズの設定
	pEffect->SetColor(col);				//色の設定
	pEffect->m_nLife = nLife;			//ライフの設定
	pEffect->m_move = move;				//速度の設定

	return pEffect;						//生成したインスタンスを返す
}