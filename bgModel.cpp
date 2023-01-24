//=============================================================================
//
// bgModel.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bgModel.h"


//コンストラクタ
CBgModel::CBgModel()
{
	//メンバー変数をクリアする
	m_move = Vec3Null;
}

//デストラクタ
CBgModel::~CBgModel()
{

}

//初期化処理
HRESULT CBgModel::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	//メンバー変数を初期化する
	m_move = Vec3Null;

	return S_OK;
}

//終了処理
void CBgModel::Uninit(void)
{
	//基本クラスの終了処理
	CModel::Uninit();
}

//更新処理
void CBgModel::Update(void)
{
	if (D3DXVec3Length(&m_move) > 0.0f)
	{//速度が0ではなかったら

		D3DXVECTOR3 pos = GetPos();		//位置の取得

		pos += m_move;					//位置の更新

		SetPos(pos);					//位置の設定
	}

	//基本クラスの更新処理
	CModel::Update();
}



//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CBgModel* Create(CModel::ModelType type, const D3DXVECTOR3 pos)
{
	CBgModel* pModel = new CBgModel;			//インスタンスを生成する

	if (FAILED(pModel->Init()))
	{//初期化処理
		return nullptr;
	}

	pModel->SetModel(type);		//モデルの設定
	pModel->SetPos(pos);		//位置の設定

	return pModel;				//生成したインスタンスを返す
}

//生成処理
CBgModel* CBgModel::Create(CModel::ModelType type, const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CBgModel* pModel = new CBgModel;			//インスタンスを生成する

	if (FAILED(pModel->Init()))
	{//初期化処理
		return nullptr;
	}

	pModel->SetModel(type);		//モデルの設定
	pModel->SetPos(pos);		//位置の設定
	pModel->m_move = move;		//速度の設定

	return pModel;				//生成したインスタンスを返す
}