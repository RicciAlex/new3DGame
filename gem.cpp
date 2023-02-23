//=============================================================================
//
// gem.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "gem.h"
#include "BoxHitbox.h"
#include "application.h"
#include "game.h"
#include "goal.h"
#include "sound.h"


//=============================================================================
//							静的変数の初期化
//=============================================================================
const float CGem::DEFAULT_SCALE = 1.75f;			//ディフォルトのスケールの係数
const D3DXVECTOR3 CGem::DEFAULT_ROTATION = { 0.0f, -D3DX_PI * 0.005f, 0.0f };		//ディフォルトの回転速度
const D3DXVECTOR3 CGem::DEFAULT_SIZE = { 25.0f, 50.0f, 25.0f };		//ディフォルトのサイズ


//コンストラクタ
CGem::CGem()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//デストラクタ
CGem::~CGem()
{

}

//初期化処理
HRESULT CGem::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CModel::Init()))
	{
		return 1;
	}

	SetModel(CModel::MODEL_JEWEL);			//モデルの設定
	SetScale(DEFAULT_SCALE);				//スケールの設定
	StartRotation(DEFAULT_ROTATION);		//回転の設定

	return S_OK;
}

//終了処理
void CGem::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox)
	{//nullチェック

		m_pHitbox->Release();		//メモリを解放する
		m_pHitbox = nullptr;		//ポインタをnullにする
	}

	//基本クラスの終了処理
	CModel::Uninit();
}

//更新処理
void CGem::Update(void)
{
	//基本クラスの更新処理
	CModel::Update();

	if (m_pHitbox)
	{
		if (m_pHitbox->GetCollisionState())
		{
			if (D3DXVec3Length(&m_newPos) > 0.0f)
			{
				m_pHitbox->Release();
				m_pHitbox = nullptr;

				SetPos(m_newPos);
				SetScale(0.8f);
				SetShadowDraw(false);
				CApplication::GetGame()->GetGoal()->SubtractGem();
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_GEM);
			}
			else
			{
				Release();
				return;
			}
		}
	}
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CGem * CGem::Create(const D3DXVECTOR3 pos)
{
	CGem* pGem = new CGem;			//インスタンスを生成する

	if (FAILED(pGem->Init()))
	{//初期化処理
		return nullptr;
	}

	pGem->SetPos(pos);				//位置の設定

	//ヒットボックスの生成処理
	pGem->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, D3DXVECTOR3(DEFAULT_SIZE), CHitbox::TYPE_VANISHING, pGem, 1);

	if (pGem->m_pHitbox)
	{//nullチェック
		pGem->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);	//プレイヤーのヒットボックスと重なることができるようにする
	}

	CApplication::GetGame()->GetGoal()->AddGem();

	return pGem;					//生成したインスタンスを返す
}

CGem * CGem::Create(const D3DXVECTOR3 pos, const D3DXCOLOR col)
{
	CGem* pGem = new CGem;			//インスタンスを生成する

	if (FAILED(pGem->Init()))
	{//初期化処理
		return nullptr;
	}

	pGem->SetPos(pos);				//位置の設定
	pGem->SetModelColor(1, col);	//色の設定

	//ヒットボックスの生成処理
	pGem->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, D3DXVECTOR3(DEFAULT_SIZE), CHitbox::TYPE_VANISHING, pGem, 1);

	if (pGem->m_pHitbox)
	{//nullチェック
		pGem->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);	//プレイヤーのヒットボックスと重なることができるようにする
	}

	CApplication::GetGame()->GetGoal()->AddGem();

	return pGem;					//生成したインスタンスを返す
}

CGem * CGem::Create(const D3DXVECTOR3 pos, const D3DXCOLOR col, const float fShadowHeight)
{
	CGem* pGem = new CGem;			//インスタンスを生成する

	if (FAILED(pGem->Init()))
	{//初期化処理
		return nullptr;
	}

	pGem->SetPos(pos);				//位置の設定
	pGem->SetModelColor(1, col);	//色の設定
	pGem->SetShadowHeight(fShadowHeight);		//影のY座標の設定

	//ヒットボックスの生成処理
	pGem->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, D3DXVECTOR3(DEFAULT_SIZE), CHitbox::TYPE_VANISHING, pGem, 1);

	if (pGem->m_pHitbox)
	{//nullチェック
		pGem->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);	//プレイヤーのヒットボックスと重なることができるようにする
	}

	CApplication::GetGame()->GetGoal()->AddGem();

	return pGem;					//生成したインスタンスを返す
}

CGem * CGem::Create(const D3DXVECTOR3 pos, const D3DXCOLOR col, const float fShadowHeight, const D3DXVECTOR3 newPos, CGoal* pGoal)
{
	CGem* pGem = new CGem;			//インスタンスを生成する

	if (FAILED(pGem->Init()))
	{//初期化処理
		return nullptr;
	}

	pGem->SetPos(pos);				//位置の設定
	pGem->SetModelColor(1, col);	//色の設定
	pGem->SetShadowHeight(fShadowHeight);		//影のY座標の設定
	pGem->m_newPos = newPos;		//新しい位置の設定

												//ヒットボックスの生成処理
	pGem->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, D3DXVECTOR3(DEFAULT_SIZE), CHitbox::TYPE_VANISHING, pGem, 1);

	if (pGem->m_pHitbox)
	{//nullチェック
		pGem->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);	//プレイヤーのヒットボックスと重なることができるようにする
	}

	pGoal->AddGem();

	return pGem;					//生成したインスタンスを返す
}
