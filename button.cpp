//=============================================================================
//
// button.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "button.h"
#include "CylinderHitbox.h"
#include "application.h"
#include "sound.h"

//コンストラクタ
CButton::CButton()
{
	//メンバー変数をクリアする
	m_originalPos = Vec3Null;
	m_normalCol = ColorNull;
	m_triggeredCol = ColorNull;
	m_bTriggered = false;
	m_bOnce = false;
	m_pHitbox = nullptr;
}

//デストラクタ
CButton::~CButton()
{

}


//初期化処理
HRESULT CButton::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	//メンバー変数を初期化する
	m_originalPos = Vec3Null;
	m_normalCol = ColorRed;
	m_triggeredCol = ColorGreen;
	m_bTriggered = false;
	m_bOnce = false;
	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CButton::Uninit(void)
{
	//ヒットボックスの破棄
	if (m_pHitbox)
	{//nullチェック
		m_pHitbox->Release();		//メモリを解放する
		m_pHitbox = false;			//ポインタをnullにする
	}
}

//更新処理
void CButton::Update(void)
{
	//ヒットボックスの更新処理
	if (m_pHitbox)
	{//nullチェック

		if (!m_bOnce)
		{
			if (m_pHitbox->GetCollisionState())
			{//何かと当たったら

				m_pHitbox->SetCollisionState(false);			//当っていない状態に戻す

				m_bTriggered = true;				//押された状態にする
				SetModelColor(0, m_triggeredCol);	//色を変更する
				SetPos(m_originalPos + D3DXVECTOR3(0.0f, -9.0f, 0.0f));			//位置を更新する

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BUTTON);
			}
			else
			{//当っていない状態だったら

				m_bTriggered = false;				//押されていない状態に戻す
				SetModelColor(0, m_normalCol);		//色を変更する
				SetPos(m_originalPos);				//位置を更新する
			}
		}
		else
		{//一回だけ押すことができたら

			if (!m_bTriggered)
			{//まだ押されていない状態だったら

				if (m_pHitbox->GetCollisionState())
				{//何かと当たったら

					m_pHitbox->SetCollisionState(false);			//当っていない状態に戻す

					m_bTriggered = true;				//押された状態にする
					SetModelColor(0, m_triggeredCol);	//色を変更する
					SetPos(m_originalPos + D3DXVECTOR3(0.0f, -9.0f, 0.0f));			//位置を更新する

					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BUTTON);
				}
			}
		}
	}
}

//一回だけ押すことができるかどうかの設定処理
void CButton::SetTriggerableOnce(const bool bOnce)
{
	m_bOnce = bOnce;
}

//押されたかどうかの取得処理
bool CButton::GetTrigger(void)
{
	return m_bTriggered;
}




//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CButton* CButton::Create(const D3DXVECTOR3 pos)
{
	CButton* pButton = new CButton;					//インスタンスを生成する

	if (FAILED(pButton->Init()))
	{//初期化処理
		return nullptr;
	}

	pButton->SetPos(pos);							//位置の設定
	pButton->m_originalPos = pos;					//元の位置の設定
	pButton->SetModel(CModel::MODEL_BUTTON);		//モデルの設定
	pButton->m_normalCol = ColorRed;				//普通の色の設定
	pButton->m_triggeredCol = ColorGreen;			//押された後の色の設定
	pButton->SetShadowDraw(false);					//影を描画しないようにする

	//ヒットボックスの生成
	pButton->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(50.0f, 10.0f, 50.0f), CHitbox::TYPE_BUTTON, pButton);
	pButton->m_pHitbox->IgnoreAllCollision();
	pButton->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);

	return pButton;									//生成したインスタンスを返す
}	

//生成処理
CButton* CButton::Create(const D3DXVECTOR3 pos, const D3DXCOLOR normalCol, const D3DXCOLOR pressedCol)
{
	CButton* pButton = new CButton;					//インスタンスを生成する

	if (FAILED(pButton->Init()))
	{//初期化処理
		return nullptr;
	}

	pButton->SetPos(pos);							//位置の設定
	pButton->m_originalPos = pos;					//元の位置の設定
	pButton->SetModel(CModel::MODEL_BUTTON);		//モデルの設定
	pButton->SetModelColor(0, normalCol);			//色の設定
	pButton->m_normalCol = normalCol;				//普通の色の設定
	pButton->m_triggeredCol = pressedCol;			//押された後の色の設定
	pButton->SetShadowDraw(false);					//影を描画しないようにする

	//ヒットボックスの生成
	pButton->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(50.0f, 10.0f, 50.0f), CHitbox::TYPE_BUTTON, pButton);
	pButton->m_pHitbox->IgnoreAllCollision();
	pButton->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);

	return pButton;									//生成したインスタンスを返す
}

CButton * CButton::Create(const D3DXVECTOR3 pos, const bool bOnce)
{
	CButton* pButton = new CButton;					//インスタンスを生成する

	if (FAILED(pButton->Init()))
	{//初期化処理
		return nullptr;
	}

	pButton->SetPos(pos);							//位置の設定
	pButton->m_originalPos = pos;					//元の位置の設定
	pButton->SetModel(CModel::MODEL_BUTTON);		//モデルの設定
	pButton->m_normalCol = ColorRed;				//普通の色の設定
	pButton->m_triggeredCol = ColorGreen;			//押された後の色の設定
	pButton->SetShadowDraw(false);					//影を描画しないようにする
	pButton->m_bOnce = true;						//一回だけ押すことができるように設定する
		
	//ヒットボックスの生成
	pButton->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(50.0f, 10.0f, 50.0f), CHitbox::TYPE_BUTTON, pButton);
	pButton->m_pHitbox->IgnoreAllCollision();
	pButton->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);

	return pButton;									//生成したインスタンスを返す
}

CButton * CButton::Create(const D3DXVECTOR3 pos, const D3DXCOLOR normalCol, const D3DXCOLOR pressedCol, const bool bOnce)
{
	CButton* pButton = new CButton;					//インスタンスを生成する

	if (FAILED(pButton->Init()))
	{//初期化処理
		return nullptr;
	}

	pButton->SetPos(pos);							//位置の設定
	pButton->m_originalPos = pos;					//元の位置の設定
	pButton->SetModel(CModel::MODEL_BUTTON);		//モデルの設定
	pButton->SetModelColor(0, normalCol);			//色の設定
	pButton->m_normalCol = normalCol;				//普通の色の設定
	pButton->m_triggeredCol = pressedCol;			//押された後の色の設定
	pButton->SetShadowDraw(false);					//影を描画しないようにする
	pButton->m_bOnce = true;						//一回だけ押すことができるように設定する

													//ヒットボックスの生成
	pButton->m_pHitbox = CCylinderHitbox::Create(pos, Vec3Null, D3DXVECTOR3(50.0f, 10.0f, 50.0f), CHitbox::TYPE_BUTTON, pButton);
	pButton->m_pHitbox->IgnoreAllCollision();
	pButton->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);

	return pButton;									//生成したインスタンスを返す
}
