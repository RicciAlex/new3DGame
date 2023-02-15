//=============================================================================
//
// fallBoard.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "fallBoard.h"
#include "BoxHitbox.h"
#include "application.h"
#include "sound.h"

//=============================================================================
//							静的変数の初期化
//=============================================================================
const float CFallBoard::DEFAULT_FALL_ACCELERATION = -1.5f;										//ディフォルトの落下加速
const D3DXVECTOR3 CFallBoard::DEFAULT_BOARD_SIZE = D3DXVECTOR3(50.0f, 10.0f, 25.0f);			//ディフォルトのモデルサイズ

//コンストラクタ
CFallBoard::CFallBoard()
{
	//メンバー変数をクリアする
	m_startingPos = Vec3Null;
	m_nCntFall = 0;
	m_nFallDelay = 0;
	m_fFallSpeed = 0.0f;
	m_bFall = false;

	m_pHitbox = nullptr;
}

//デストラクタ
CFallBoard::~CFallBoard()
{
	
}

//初期化処理
HRESULT CFallBoard::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	//メンバー変数を初期化する
	m_startingPos = Vec3Null;
	m_nCntFall = 0;
	m_nFallDelay = DEFAULT_FALL_DELAY;
	m_fFallSpeed = 0.0f;
	m_bFall = false;

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CFallBoard::Uninit(void)
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
void CFallBoard::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	if (m_pHitbox)
	{
		m_pHitbox->SetPos(pos);

		if (m_pHitbox->GetCollisionState())
		{
			m_pHitbox->SetCollisionState(false);

			if (!m_bFall && m_fFallSpeed <= 0.0f)
			{
				m_bFall = true;
			}
		}
	}

	if (m_bFall)
	{
		m_nCntFall++;

		if (m_nCntFall < m_nFallDelay)
		{
			pos.x += 0.5f * sinf(D3DX_PI * 0.25f * m_nCntFall);
		}
		else
		{
			if (m_nCntFall == m_nFallDelay)
			{
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FALL_WHISTLE);
			}

			m_fFallSpeed += DEFAULT_FALL_ACCELERATION;

			if (pos.y <= m_startingPos.y - 1500.0f)
			{
				pos.x = m_startingPos.x;
				pos.y = m_startingPos.y - 1500.0f;

				m_bFall = false;
				m_fFallSpeed = 4.0f;
				m_nCntFall = 0;
			}
		}
	}

	pos.y += m_fFallSpeed;

	if (pos.y >= m_startingPos.y)
	{
		pos.y = m_startingPos.y;
		m_fFallSpeed = 0.0f;
	}

	SetPos(pos);
}




//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CFallBoard* CFallBoard::Create(const D3DXVECTOR3 pos)
{
	CFallBoard* pBoard = new CFallBoard;			//インスタンスを生成する

	if (FAILED(pBoard->Init()))
	{//初期化処理
		return nullptr;
	}

	pBoard->SetPos(pos);			//位置の設定
	pBoard->m_startingPos = pos;	//もとの位置の設定

	pBoard->SetModel(CModel::MODEL_WOODEN_BOARD);		//モデルの設定
	pBoard->SetScale(2.0f);								//スケールの設定
	pBoard->SetShadowDraw(false);						//影を描画しないように設定する

	D3DXVECTOR3 size = D3DXVECTOR3(DEFAULT_BOARD_SIZE.x * 2.0f, DEFAULT_BOARD_SIZE.y * 2.0f, DEFAULT_BOARD_SIZE.z * 2.0f);		//ヒットボックスのサイズ

	pBoard->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, size, CHitbox::TYPE_NEUTRAL, pBoard);		//ヒットボックスの生成

	return pBoard;				//生成したインスタンスを返す
}

//生成処理
CFallBoard * CFallBoard::Create(const D3DXVECTOR3 pos, const int nFallDelay)
{
	CFallBoard* pBoard = new CFallBoard;			//インスタンスを生成する

	if (FAILED(pBoard->Init()))
	{//初期化処理
		return nullptr;
	}

	pBoard->SetPos(pos);					//位置の設定
	pBoard->m_startingPos = pos;			//もとの位置の設定
	pBoard->m_nFallDelay = nFallDelay;		//落下するまでのフレーム数の設定

	pBoard->SetModel(CModel::MODEL_WOODEN_BOARD);		//モデルの設定
	pBoard->SetScale(2.0f);								//スケールの設定
	pBoard->SetShadowDraw(false);						//影を描画しないように設定する

	D3DXVECTOR3 size = D3DXVECTOR3(DEFAULT_BOARD_SIZE.x * 2.0f, DEFAULT_BOARD_SIZE.y * 2.0f, DEFAULT_BOARD_SIZE.z * 2.0f);		//ヒットボックスのサイズ

	pBoard->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, size, CHitbox::TYPE_NEUTRAL, pBoard);		//ヒットボックスの生成

	return pBoard;				//生成したインスタンスを返す
}
