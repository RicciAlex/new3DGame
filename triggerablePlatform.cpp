//=============================================================================
//
// triggerablePlatform.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "triggerablePlatform.h"
#include "button.h"
#include "movingCube.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "animationFade.h"

//コンストラクタ
CTriggerablePlatform::CTriggerablePlatform()
{
	//メンバー変数をクリアする
	m_move = Vec3Null;
	m_bTriggered = false;

	m_pButton = nullptr;
	m_pPlatform = nullptr;
}

//デストラクタ
CTriggerablePlatform::~CTriggerablePlatform()
{

}

//初期化処理
HRESULT CTriggerablePlatform::Init(void)
{
	//メンバー変数を初期化する
	m_move = Vec3Null;
	m_bTriggered = false;

	m_pButton = nullptr;
	m_pPlatform = nullptr;

	return S_OK;
}

//終了処理
void CTriggerablePlatform::Uninit(void)
{
	//ボタンの破棄
	if (m_pButton)
	{//nullチェック
		m_pButton->Release();		//メモリを解放する
		m_pButton = nullptr;		//ポインタをnullにする
	}

	//プラットフォームの破棄
	if (m_pButton)
	{//nullチェック
		m_pButton->Release();		//メモリを解放する
		m_pButton = nullptr;		//ポインタをnullにする
	}
}

//更新処理
void CTriggerablePlatform::Update(void)
{
	if (m_pButton && m_pPlatform)
	{//nullチェック

		if (!m_bTriggered)
		{//ボタンがまだ押されていない場合

			if (m_pButton->GetTrigger())
			{//ボタンが押されたら

				m_bTriggered = true;				//押された状態にする

				m_pPlatform->SetMove(m_move);		//プラットフォームの速度を設定する

				CApplication::GetGame()->GetPlayer()->SetCameraAnim(true);

				CAnimationFade::Create(m_pPlatform->GetPos() + D3DXVECTOR3(0.0f, 250.0f, -500.0f), m_pPlatform->GetPos(), CAnimationFade::TYPE_PLATFORM);
			}
		}
	}
}

//描画処理
void CTriggerablePlatform::Draw(void)
{

}

//位置の設定処理
void CTriggerablePlatform::SetPos(const D3DXVECTOR3 pos)
{
	if (m_pPlatform)
	{//nullチェック
		m_pPlatform->SetPos(pos);
	}
}

//元の位置の設定処理
void CTriggerablePlatform::SetOriginalPos(const D3DXVECTOR3 oPos)
{
	if (m_pPlatform)
	{//プラットフォームのnullチェック
				
		m_pPlatform->SetOriginalPos(oPos);
	}
}

//ボタンの位置の設定処理
void CTriggerablePlatform::SetButtonPos(const D3DXVECTOR3 pos)
{
	if (m_pButton)
	{//nullチェック
		m_pButton->SetPos(pos);
	}
}

//位置の取得処理
const D3DXVECTOR3 CTriggerablePlatform::GetPos(void)
{
	if (m_pPlatform)
	{//nullチェック
		return m_pPlatform->GetPos();
	}

	return Vec3Null;
}

//ボタンの位置の取得処理
const D3DXVECTOR3 CTriggerablePlatform::GetButtonPos(void)
{
	if (m_pButton)
	{//nullチェック
		return m_pButton->GetPos();
	}

	return Vec3Null;
}

//ボタンが押されたかどうかの取得処理
const bool CTriggerablePlatform::GetTriggeredState(void)
{
	return m_bTriggered;
}



//=============================================================================
//
// triggerablePlatform.cpp
// Author : Ricci Alex
//
//=============================================================================


//生成処理
CTriggerablePlatform* CTriggerablePlatform::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 buttonPos, const D3DXVECTOR3 move, const float fRange)
{
	CTriggerablePlatform* pObj = new CTriggerablePlatform;		//インスタンスを生成する

	if(FAILED(pObj->Init()))
	{//初期化処理
		return nullptr;
	}

	pObj->m_move = move;			//ボタンが押されたらの速度の設定
	pObj->m_pPlatform = CMovingCube::Create(pos, Vec3Null, fRange);		//プラットフォームの生成

	if (!pObj->m_pPlatform)
	{//生成できなかったら、nullを返す

		pObj->Release();

		return nullptr;
	}

	pObj->m_pButton = CButton::Create(buttonPos);			//ボタンの生成

	if (!pObj->m_pButton)
	{//生成できなかったら、nullを返す

		pObj->Release();

		return nullptr;
	}

	pObj->m_pButton->SetTriggerableOnce(true);				//一回だけ押すことができることにする

	return pObj;					//生成したインスタンスを返す
}