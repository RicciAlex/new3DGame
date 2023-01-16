//=============================================================================
//
// cameraSetter.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "cameraSetter.h"
#include "application.h"
#include "game.h"

#include "line.h"

//コンストラクタ
CCameraSetter::CCameraSetter()
{
	//メンバー変数をクリアする
	m_pos = Vec3Null;
	m_size = Vec3Null;
	m_CameraTarget = (CPlayer::CAMERA_POS)0;
	m_bActive = false;
}

//デストラクタ
CCameraSetter::~CCameraSetter()
{

}

//初期化処理
HRESULT CCameraSetter::Init(void)
{
	//メンバー変数を初期化する
	m_pos = Vec3Null;
	m_size = Vec3Null;
	m_CameraTarget = CPlayer::CAMERA_POS_NORMAL;
	m_bActive = false;


	return S_OK;
}

//終了処理
void CCameraSetter::Uninit(void)
{
	
}

//更新処理
void CCameraSetter::Update(void)
{
	TestOverlap();
}

//描画処理
void CCameraSetter::Draw(void)
{

}

//位置の設定処理
void CCameraSetter::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//位置の取得処理
const D3DXVECTOR3 CCameraSetter::GetPos(void)
{
	return m_pos;
}


//=============================================================================
//
//									静的関数
//
//=============================================================================


//生成処理
CCameraSetter* CCameraSetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, CPlayer::CAMERA_POS target)
{
	CCameraSetter* pSetter = new CCameraSetter;			//インスタンスを生成する

	if (FAILED(pSetter->Init()))
	{//初期化処理
		return nullptr;
	}

	pSetter->m_pos = pos;					//位置の設定
	pSetter->m_size = size;					//サイズの設定
	pSetter->m_CameraTarget = target;		//カメラの目的の位置の設定

#ifdef _DEBUG

											//デバッグ用の線の生成
	D3DXVECTOR3 VtxPos[8] = {};

	//頂点座標の設定
	VtxPos[0] = D3DXVECTOR3(- size.x * 0.5f, - size.y * 0.5f, + size.z * 0.5f);
	VtxPos[1] = D3DXVECTOR3(+ size.x * 0.5f, - size.y * 0.5f, + size.z * 0.5f);
	VtxPos[2] = D3DXVECTOR3(+ size.x * 0.5f, - size.y * 0.5f, - size.z * 0.5f);
	VtxPos[3] = D3DXVECTOR3(- size.x * 0.5f, - size.y * 0.5f, - size.z * 0.5f);
	VtxPos[4] = D3DXVECTOR3(- size.x * 0.5f, + size.y * 0.5f, + size.z * 0.5f);
	VtxPos[5] = D3DXVECTOR3(+ size.x * 0.5f, + size.y * 0.5f, + size.z * 0.5f);
	VtxPos[6] = D3DXVECTOR3(+ size.x * 0.5f, + size.y * 0.5f, - size.z * 0.5f);
	VtxPos[7] = D3DXVECTOR3(- size.x * 0.5f, + size.y * 0.5f, - size.z * 0.5f);

	//線の生成
	CLine::Create(pos, Vec3Null, VtxPos[0], VtxPos[1], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[1], VtxPos[2], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[2], VtxPos[3], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[3], VtxPos[0], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

	CLine::Create(pos, Vec3Null, VtxPos[0], VtxPos[4], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[1], VtxPos[5], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[2], VtxPos[6], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[3], VtxPos[7], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

	CLine::Create(pos, Vec3Null, VtxPos[4], VtxPos[5], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[5], VtxPos[6], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[6], VtxPos[7], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	CLine::Create(pos, Vec3Null, VtxPos[7], VtxPos[4], D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

#endif // !DEBUG

	return pSetter;					//生成したインスタンスを返す
}



//=============================================================================
//
//								プライベート関数
//
//=============================================================================



//プレイヤーと重なっているかどうか
bool CCameraSetter::TestOverlap(void)
{
	CPlayer* pPlayer = CApplication::GetGame()->GetPlayer();

	if (pPlayer)
	{
		D3DXVECTOR3 playerPos = pPlayer->GetPos();

		if (playerPos.x >= m_pos.x - (m_size.x * 0.5f) && playerPos.x <= m_pos.x + (m_size.x * 0.5f) &&
			playerPos.y >= m_pos.y - (m_size.y * 0.5f) && playerPos.y <= m_pos.y + (m_size.y * 0.5f) &&
			playerPos.z >= m_pos.z - (m_size.z * 0.5f) && playerPos.z <= m_pos.z + (m_size.z * 0.5f))
		{
 			pPlayer->SetTargetCameraPos(m_CameraTarget);

			m_bActive = true;

			return true;
		}
	}

	if (m_bActive)
	{
		pPlayer->SetTargetCameraPos(CPlayer::CAMERA_POS_NORMAL);

		m_bActive = false;
	}

	return false;
}
