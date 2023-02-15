//=============================================================================
//
// spawnTrigger.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "spawnTrigger.h"


//=============================================================================
//								静的変数の初期化
//=============================================================================
const D3DXVECTOR3 CSpawnTrigger::DEFAULT_POS = { 0.0f, -10000.0f, 0.0f };				//ディフォルトの位置


//コンストラクタ
CSpawnTrigger::CSpawnTrigger()
{
	//メンバー変数をクリアする
	m_pos = Vec3Null;

	m_vSpawnObj.clear();
	m_vObjHeight.clear();
}

//デストラクタ
CSpawnTrigger::~CSpawnTrigger()
{

}

//初期化処理
HRESULT CSpawnTrigger::Init(void)
{
	//メンバー変数を初期化する
	m_pos = Vec3Null;

	return S_OK;
}

//終了処理
void CSpawnTrigger::Uninit(void)
{
	m_vSpawnObj.clear();
	m_vSpawnObj.shrink_to_fit();

	m_vObjHeight.clear();
	m_vObjHeight.shrink_to_fit();
}

//更新処理
void CSpawnTrigger::Update(void)
{
	if (m_pTrigger)
	{
		if (m_pTrigger->GetTriggeredState())
		{
			for (int nCnt = 0; nCnt < (int)m_vSpawnObj.size(); nCnt++)
			{
				if (m_vSpawnObj.data()[nCnt])
				{
					D3DXVECTOR3 pos = m_vSpawnObj.data()[nCnt]->GetPos();
					pos.y = m_vObjHeight.data()[nCnt];

					m_vSpawnObj.data()[nCnt]->SetPos(pos);
				}
			}

			Release();
			return;
		}
	}
}

//描画処理
void CSpawnTrigger::Draw(void)
{

}

//位置の設定処理
void CSpawnTrigger::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//オブジェクトの追加処理
void CSpawnTrigger::AddObject(CObject* pObj, const float fHeight)
{
	m_vSpawnObj.push_back(pObj);
	m_vObjHeight.push_back(fHeight);

	D3DXVECTOR3 pos = pObj->GetPos();
	pos.y = DEFAULT_POS.y;
	pObj->SetPos(pos);
}

//トリガーの追加処理
void CSpawnTrigger::AddTriggerPlatform(CTriggerablePlatform * pTrigger)
{
	m_pTrigger = pTrigger;
}

//位置の取得処理
const D3DXVECTOR3 CSpawnTrigger::GetPos(void)
{
	return m_pos;
}



//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CSpawnTrigger* CSpawnTrigger::Create(void)
{
	CSpawnTrigger* pSpawn = new CSpawnTrigger;			//インスタンスを生成する

	if (FAILED(pSpawn->Init()))
	{//初期化処理
		return nullptr;
	}

	pSpawn->m_pos = DEFAULT_POS;	//位置の設定

	return pSpawn;					//生成したインスタンスを返す
}

//生成処理
CSpawnTrigger* CSpawnTrigger::Create(const D3DXVECTOR3 pos)
{
	CSpawnTrigger* pSpawn = new CSpawnTrigger;			//インスタンスを生成する

	if (FAILED(pSpawn->Init()))
	{//初期化処理
		return nullptr;
	}

	pSpawn->m_pos = pos;	//位置の設定

	return pSpawn;			//生成したインスタンスを返す
}