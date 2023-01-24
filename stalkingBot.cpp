//=============================================================================
//
// spikeTrap.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "stalkingBot.h"


//=============================================================================
//								静的変数の初期化
//=============================================================================
const float		  CStalkingBot::DEFAULT_APPROACHING_SPEED = 15.0f;				//ディフォルトの追いかける速度
const float		  CStalkingBot::DEFAULT_ANGLE_SPEED = D3DX_PI * 0.01f;			//ディフォルトの回転速度
const float		  CStalkingBot::DEFAULT_FIRST_COEFF = 3.0f;						//ディフォルトの最初のパラメータ(パラメトリック方程式用)
const float		  CStalkingBot::DEFAULT_SECOND_COEFF = 5.0f;					//ディフォルトの二番目のパラメータ(パラメトリック方程式用)
const float		  CStalkingBot::DEFAULT_AMPLITUDE = 10.0f;						//ディフォルトの拡大率
const D3DXVECTOR3 CStalkingBot::DEFAULT_RELATIVE_POS = {0.0f, 50.0f, 0.0f};		//ディフォルトの相対位置


//コンストラクタ
CStalkingBot::CStalkingBot()
{

}

//デストラクタ
CStalkingBot::~CStalkingBot()
{

}

//初期化処理
HRESULT CStalkingBot::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CFogbot::Init()))
	{
		return -1;
	}

	return S_OK;
}

//終了処理
void CStalkingBot::Uninit(void)
{
	//基本クラスの終了処理
	CFogbot::Uninit();
}

//更新処理
void CStalkingBot::Update(void)
{
	//基本クラスの更新処理
	CFogbot::Update();
}



//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CStalkingBot* CStalkingBot::Create(const D3DXVECTOR3 pos, const float fShadowHeight)
{
	CStalkingBot* pBot = new CStalkingBot;			//インスタンスを生成する

	//初期化処理
	if (FAILED(pBot->Init()))
	{
		return nullptr;
	}

	pBot->CreateDefaultBot();				//ディフォルトのボットの生成処理

	pBot->SetPos(pos);						//位置の設定
	pBot->SetShadowHeight(fShadowHeight);	//影のY座標の設定


	return pBot;							//生成したインスタンスを返す
}

CStalkingBot* CStalkingBot::Create(const D3DXVECTOR3 pos, const float fShadowHeight, const float fStartAngle)
{
	CStalkingBot* pBot = new CStalkingBot;			//インスタンスを生成する

													//初期化処理
	if (FAILED(pBot->Init()))
	{
		return nullptr;
	}

	pBot->CreateDefaultBot();				//ディフォルトのボットの生成処理

	pBot->SetPos(pos);						//位置の設定
	pBot->SetShadowHeight(fShadowHeight);	//影のY座標の設定


	return pBot;							//生成したインスタンスを返す
}