//=============================================================================
//
// checkpoint.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "checkpoint.h"
#include "model.h"
#include "application.h"
#include "game.h"
#include "player.h"

//=============================================================================
//							静的変数の初期化
//=============================================================================
const float			CCheckpoint::ANIMATION_AMPLITUDE = 0.005f;
const float			CCheckpoint::DEFAULT_RANGE = 300.0f;				//ディフォルトの半径
const D3DXCOLOR		CCheckpoint::DEFAULT_NORMAL_COLOR = D3DXCOLOR(1.0f, 0.5f, 0.1f, 0.5f);		//ディフォルトの普通の色
const D3DXCOLOR		CCheckpoint::DEFAULT_ACTIVE_COLOR = D3DXCOLOR(0.1f, 1.0f, 0.1f, 0.5f);		//ディフォルトのアクティブの色
bool				CCheckpoint::m_bChange = false;
bool				CCheckpoint::m_bFirst = true;

//コンストラクタ
CCheckpoint::CCheckpoint()
{
	//メンバー変数をクリアする
	m_pos = Vec3Null;
	m_fRange = 0.0f;
	m_normalCol = ColorNull;
	m_activeCol = ColorNull;
	m_nScaleAnimCnt = 0;
	m_fScaleAnim = 0.0f;
	m_bActive = false;

	m_pFlag = nullptr;
	m_pAura = nullptr;
}

//デストラクタ
CCheckpoint::~CCheckpoint()
{

}

//初期化処理
HRESULT CCheckpoint::Init(void)
{
	//メンバー変数を初期化する
	m_pos = Vec3Null;
	m_fRange = DEFAULT_RANGE;
	m_normalCol = DEFAULT_NORMAL_COLOR;
	m_activeCol = DEFAULT_ACTIVE_COLOR;
	m_nScaleAnimCnt = 0;
	m_fScaleAnim = ANIMATION_AMPLITUDE;
	m_bActive = false;

	m_pFlag = nullptr;
	m_pAura = nullptr;

	return S_OK;
}

//終了処理
void CCheckpoint::Uninit(void)
{
	//モデルの破棄処理
	if (m_pFlag)
	{//nullチェック
		m_pFlag->Release();			//メモリを解放する
		m_pFlag = nullptr;			//ポインタをnullにする
	}
	if (m_pAura)
	{//nullチェック
		m_pAura->Release();			//メモリを解放する
		m_pAura = nullptr;			//ポインタをnullにする
	}
}

//更新処理
void CCheckpoint::Update(void)
{
	if (!m_bActive)
	{
		CPlayer* pPlayer = CApplication::GetGame()->GetPlayer();

		if (pPlayer)
		{
			D3DXVECTOR3 distance = pPlayer->GetPos() - m_pos;			//距離を計算する

			if (D3DXVec3Length(&distance) <= m_fRange)
			{
				if (m_pAura)
				{
					m_pAura->SetModelColor(0, m_activeCol);
				}

				m_bActive = true;

				if (!m_bFirst)
				{
					m_bChange = true;
				}
				else
				{
					m_bFirst = false;
				}

				pPlayer->SetRespawnPoint(D3DXVECTOR3(m_pos.x, m_pos.y + 50.0f, m_pos.z - 50.0f));
			}
		}
	}
	else
	{
		if (m_bChange)
		{
			if (m_pAura)
			{
				m_pAura->SetModelColor(0, m_normalCol);
			}

			m_bActive = false;
			m_bChange = false;
		}
	}

	if (m_pAura)
	{
		float fScale = m_pAura->GetScale();

		m_nScaleAnimCnt++;

		if (m_nScaleAnimCnt >= ANIMATION_FRAMES)
		{
			m_nScaleAnimCnt = 0;

			m_fScaleAnim *= -1.0f;
		}

		fScale += m_fScaleAnim;

		m_pAura->SetScale(fScale);
	}
}

//描画処理
void CCheckpoint::Draw(void)
{

}

//位置の設定処理
void CCheckpoint::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//位置の取得処理
const D3DXVECTOR3 CCheckpoint::GetPos(void)
{
	return m_pos;
}



//=============================================================================
//
//									静的関数
//
//=============================================================================





//クリア処理
void CCheckpoint::Clear(void)
{
	m_bFirst = true;
	m_bChange = false;
}

//生成処理
CCheckpoint* CCheckpoint::Create(const D3DXVECTOR3 pos)
{
	CCheckpoint* pPoint = new CCheckpoint;			//インスタンスを生成する

	if (FAILED(pPoint->Init()))
	{//初期化処理
		return nullptr;
	}

	pPoint->m_pos = pos;			//位置の設定

	pPoint->m_pFlag = CModel::Create(CModel::MODEL_FLAG, pos);			//チェックポイントのフラグモデルの生成

	if (pPoint->m_pFlag)
	{//生成出来たら、影を描画しないようにする
		pPoint->m_pFlag->SetShadowDraw(false);
		pPoint->m_pFlag->SetModelColor(1, ColorGreen);
	}

	pPoint->m_pAura = CModel::Create(CModel::MODEL_CHECKPOINT_AURA, pos);		//チェックポイントのオーラモデルの生成

	if (pPoint->m_pAura)
	{
		pPoint->m_pAura->SetScale(3.0f);
		pPoint->m_pAura->SetShadowDraw(false);
	}

	return pPoint;			//生成したインスタンスを返す
}

//生成処理
CCheckpoint* CCheckpoint::Create(const D3DXVECTOR3 pos, const float fRange)
{
	CCheckpoint* pPoint = new CCheckpoint;			//インスタンスを生成する

	if (FAILED(pPoint->Init()))
	{//初期化処理
		return nullptr;
	}

	pPoint->m_pos = pos;					//位置の設定
	pPoint->m_fRange = fRange;				//半径の設定

	pPoint->m_pFlag = CModel::Create(CModel::MODEL_FLAG, pos);			//チェックポイントのフラグモデルの生成

	if (pPoint->m_pFlag)
	{//生成出来たら、影を描画しないようにする
		pPoint->m_pFlag->SetShadowDraw(false);
		pPoint->m_pFlag->SetModelColor(1, ColorGreen);
	}

	pPoint->m_pAura = CModel::Create(CModel::MODEL_CHECKPOINT_AURA, pos);		//チェックポイントのオーラモデルの生成

	if (pPoint->m_pAura)
	{
		pPoint->m_pAura->SetScale(3.0f);
		pPoint->m_pAura->SetShadowDraw(false);
	}

	return pPoint;			//生成したインスタンスを返す
}

//生成処理
CCheckpoint* CCheckpoint::Create(const D3DXVECTOR3 pos, const float fRange, const D3DXCOLOR normalCol)
{
	CCheckpoint* pPoint = new CCheckpoint;			//インスタンスを生成する

	if (FAILED(pPoint->Init()))
	{//初期化処理
		return nullptr;
	}

	pPoint->m_pos = pos;					//位置の設定
	pPoint->m_fRange = fRange;				//半径の設定
	pPoint->m_normalCol = normalCol;		//普通の色の設定

	pPoint->m_pFlag = CModel::Create(CModel::MODEL_FLAG, pos);			//チェックポイントのフラグモデルの生成

	if (pPoint->m_pFlag)
	{//生成出来たら、影を描画しないようにする
		pPoint->m_pFlag->SetShadowDraw(false);
		pPoint->m_pFlag->SetModelColor(1, ColorGreen);
	}

	pPoint->m_pAura = CModel::Create(CModel::MODEL_CHECKPOINT_AURA, pos);		//チェックポイントのオーラモデルの生成

	if (pPoint->m_pFlag)
	{//生成出来たら、色を設定する
		pPoint->m_pAura->SetModelColor(0, normalCol);
		pPoint->m_pAura->SetScale(3.0f);
		pPoint->m_pAura->SetShadowDraw(false);
	}

	return pPoint;			//生成したインスタンスを返す
}

//生成処理
CCheckpoint* CCheckpoint::Create(const D3DXVECTOR3 pos, const float fRange, const D3DXCOLOR normalCol, const D3DXCOLOR activeCol)
{
	CCheckpoint* pPoint = new CCheckpoint;			//インスタンスを生成する

	if (FAILED(pPoint->Init()))
	{//初期化処理
		return nullptr;
	}

	pPoint->m_pos = pos;					//位置の設定
	pPoint->m_fRange = fRange;				//半径の設定
	pPoint->m_normalCol = normalCol;		//普通の色の設定
	pPoint->m_activeCol = activeCol;		//アクティブの色の設定

	pPoint->m_pFlag = CModel::Create(CModel::MODEL_FLAG, pos);			//チェックポイントのフラグモデルの生成

	if (pPoint->m_pFlag)
	{//生成出来たら、影を描画しないようにする
		pPoint->m_pFlag->SetShadowDraw(false);
		pPoint->m_pFlag->SetModelColor(1, ColorGreen);
	}

	pPoint->m_pAura = CModel::Create(CModel::MODEL_CHECKPOINT_AURA, pos);		//チェックポイントのオーラモデルの生成

	if (pPoint->m_pFlag)
	{//生成出来たら、色を設定する
		pPoint->m_pAura->SetModelColor(0, normalCol);
		pPoint->m_pAura->SetScale(3.0f);
		pPoint->m_pAura->SetShadowDraw(false);
	}

	return pPoint;			//生成したインスタンスを返す
}