//=============================================================================
//
// stageSelectCursor.h
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "stageSelectCursor.h"
#include "model.h"

//=============================================================================
//							静的変数の初期化
//=============================================================================
const D3DXVECTOR3 CStageSelectCursor::RELATIVE_POS[JEWEL_NUMBER] = {
	{ 250.0f, 0.0f, 0.0f },
	{ 216.5f, 0.0f, 125.0 },
	{ 125.0, 0.0f, 216.5f },
	{ 0.0f, 0.0f, 250.0f },
	{ -125.0, 0.0f, 216.5f },
	{ -216.5f, 0.0f, 125.0 },
	{ -250.0f, 0.0f, 0.0f },
	{ -216.5f, 0.0f, -125.0 },
	{ -125.0, 0.0f, -216.5f },
	{ 0.0f, 0.0f, -250.0f },
	{ 125.0, 0.0f, -216.5f },
	{ 216.5f, 0.0f, -125.0 }

};		//宝石の相対位置


const D3DXCOLOR CStageSelectCursor::JEWEL_COLOR[JEWEL_NUMBER / 2] = {
	ColorRed,
	ColorGreen,
	ColorBlue,
	ColorYellow,
	ColorCyan,
	ColorMagenta

};		//宝石の色

//コンストラクタ
CStageSelectCursor::CStageSelectCursor()
{
	//メンバー変数をクリアする
	m_pos = Vec3Null;

	for (int nCnt = 0; nCnt < JEWEL_NUMBER; nCnt++)
	{
		m_pModel[nCnt] = nullptr;
	}
}

//デストラクタ
CStageSelectCursor::~CStageSelectCursor()
{

}

//初期化処理
HRESULT CStageSelectCursor::Init(void)
{
	return S_OK;
}

//終了処理
void CStageSelectCursor::Uninit(void)
{
	//モデルの破棄処理
	for (int nCnt = 0; nCnt < JEWEL_NUMBER; nCnt++)
	{
		if (m_pModel[nCnt])
		{//nullチェック
			m_pModel[nCnt]->Release();		//メモリを解放する
			m_pModel[nCnt] = nullptr;		//ポインタをnullにする
		}
	}
}

//更新処理
void CStageSelectCursor::Update(void)
{

}

//描画処理
void CStageSelectCursor::Draw(void)
{

}

//位置の設定処理
void CStageSelectCursor::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;

	for (int nCnt = 0; nCnt < JEWEL_NUMBER; nCnt++)
	{
		m_pModel[nCnt]->SetPos(m_pos + RELATIVE_POS[nCnt]);
	}
}

//位置の取得処理
const D3DXVECTOR3 CStageSelectCursor::GetPos(void)
{
	return m_pos;
}





//生成処理
CStageSelectCursor * CStageSelectCursor::Create(const D3DXVECTOR3 pos)
{
	CStageSelectCursor* pCursor = new CStageSelectCursor;			//インスタンスを生成する

	if(FAILED(pCursor->Init()))
	{//初期化処理
		return nullptr;
	}

	pCursor->m_pos = pos;			//位置の設定

	//宝石の生成処理
	for (int nCnt = 0; nCnt < JEWEL_NUMBER; nCnt++)
	{
		pCursor->m_pModel[nCnt] = CModel::Create(CModel::MODEL_JEWEL, pos + RELATIVE_POS[nCnt]);

		if (pCursor->m_pModel[nCnt])
		{//生成出来たら、色を設定する
			pCursor->m_pModel[nCnt]->SetModelColor(1, JEWEL_COLOR[nCnt % (JEWEL_NUMBER / 2)]);
			pCursor->m_pModel[nCnt]->SetScale(1.5f);
			pCursor->m_pModel[nCnt]->SetShadowDraw(false);
			pCursor->m_pModel[nCnt]->StartRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.005f, 0.0f));
		}
	}

	return pCursor;				//生成したインスタンスを返す
}
