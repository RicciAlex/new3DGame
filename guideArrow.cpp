//=============================================================================
//
// guideArrow.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "guideArrow.h"


//コンストラクタ
CGuideArrow::CGuideArrow()
{

}

//デストラクタ
CGuideArrow::~CGuideArrow()
{

}

//初期化処理
HRESULT CGuideArrow::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CObject_3D::Init()))
	{
		return -1;
	}

	//テクスチャアニメーション用のパラメータの設定
	SetTexture(CObject::TEXTURE_GUIDE_ARROW);
	SetTextureParameter(2, 2, 1, 45);
	SetSize(D3DXVECTOR2(25.0f, 25.0f));

	return S_OK;
}



//=============================================================================
//
//									静的関数
//
//=============================================================================




//生成処理
CGuideArrow* CGuideArrow::Create(const D3DXVECTOR3 pos)
{
	CGuideArrow* pArrow = new CGuideArrow;			//インスタンスを生成する

	if (FAILED(pArrow->Init()))
	{//初期化処理
		return nullptr;
	}

	pArrow->SetPos(pos);			//位置の設定

	return pArrow;			//生成したインスタンスを返す
}

CGuideArrow * CGuideArrow::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CGuideArrow* pArrow = new CGuideArrow;			//インスタンスを生成する

	if (FAILED(pArrow->Init()))
	{//初期化処理
		return nullptr;
	}

	pArrow->SetPos(pos);			//位置の設定
	pArrow->SetStartingRot(rot);	//向きの設定

	return pArrow;			//生成したインスタンスを返す
}
