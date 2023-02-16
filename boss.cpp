//=============================================================================
//
// boss.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "boss.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "sound.h"
#include "icicle.h"


#include "inputKeyboard.h"


//=============================================================================
//								静的変数の初期化
//=============================================================================
const D3DXVECTOR3 CBoss::DEFAULT_POS = { 0.0f, 200.0f, 2775.0f };			//ディフォルトの位置



//コンストラクタ
CBoss::CBoss()
{
	//メンバー変数をクリアする
	m_targetPos = Vec3Null;
	m_nCntAttack = 0;
}

//デストラクタ
CBoss::~CBoss()
{

}

//初期化処理
HRESULT CBoss::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	SetModel(CModel::MODEL_BOSS_EYES);
	SetPos(DEFAULT_POS);
	SetShadowDraw(false);
	SetScale(4);
	SetDrawDistance(5000.0f);

	return S_OK;
}

//終了処理
void CBoss::Uninit(void)
{
	//基本クラスの終了処理
	CModel::Uninit();
}

//更新処理
void CBoss::Update(void)
{
	D3DXVECTOR3 playerPos = CApplication::GetGame()->GetPlayer()->GetPos();
	SetPos(playerPos + DEFAULT_POS);

	//基本クラスの更新処理
	CModel::Update();

	m_nCntAttack++;

	if (m_nCntAttack == 60)
	{
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ROAR);
	}
	else if (m_nCntAttack == 130)
	{
		m_targetPos = playerPos;
	}
	if (m_nCntAttack >= 150)
	{
		m_nCntAttack = 0;

		CIcicle::Create(m_targetPos);
	}
}




//=============================================================================
//
//									静的関数
//
//=============================================================================




//生成処理
CBoss* CBoss::Create(void)
{
	CBoss* pBoss = new CBoss;			//インスタンスを生成する


	if (FAILED(pBoss->Init()))
	{//初期化処理
		return nullptr;
	}

	return pBoss;						//生成したインスタンスを返す
}