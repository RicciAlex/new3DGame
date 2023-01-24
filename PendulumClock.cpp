//=============================================================================
//
// PendulumClock.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "PendulumClock.h"
#include "modelPart.h"
#include "BoxHitbox.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "BoxHitbox.h"


//=============================================================================
//								静的変数の初期化
//=============================================================================
const float CPendulumClock::DEFAULT_ANIM_FRAME_ANGLE = D3DX_PI * 0.0025f;		//毎フレーム加算されている角度
const float CPendulumClock::DEFAULT_RANGE = 200.0f;								//有効範囲


//コンストラクタ
CPendulumClock::CPendulumClock()
{
	//メンバー変数をクリアする
	m_fAnimAngle = 0.0f;
	m_fAnimCoeff = 0.0f;

	m_pPendulum = nullptr;
	m_pHitbox = nullptr;

	for (int nCnt = 0; nCnt < NEEDLE_NUMBER; nCnt++)
	{
		m_pNeedle[nCnt] = nullptr;
	}
}

//デストラクタ
CPendulumClock::~CPendulumClock()
{

}

//初期化処理
HRESULT CPendulumClock::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CModel::Init()))
	{
		return -1;
	}

	//メンバー変数を初期化する
	m_fAnimAngle = 0.0f;
	m_fAnimCoeff = 1.0f;

	m_pPendulum = nullptr;
	m_pHitbox = nullptr;

	for (int nCnt = 0; nCnt < NEEDLE_NUMBER; nCnt++)
	{
		m_pNeedle[nCnt] = nullptr;
	}

	return S_OK;
}

//終了処理
void CPendulumClock::Uninit(void)
{
	for (int nCnt = 0; nCnt < NEEDLE_NUMBER; nCnt++)
	{
		if (m_pNeedle[nCnt])
		{
			m_pNeedle[nCnt]->Uninit();
			delete m_pNeedle[nCnt];
			m_pNeedle[nCnt] = nullptr;
		}
	}

	if (m_pPendulum)
	{
		m_pPendulum->Uninit();
		delete m_pPendulum;
		m_pPendulum = nullptr;
	}

	if (m_pHitbox)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}
}

//更新処理
void CPendulumClock::Update(void)
{
	if (m_pPendulum)
	{
		D3DXVECTOR3 rot = m_pPendulum->GetRot();

		m_fAnimAngle += DEFAULT_ANIM_FRAME_ANGLE;

		rot.z = 0.35f * sinf(4.0f * m_fAnimAngle);

		m_pPendulum->SetRot(rot);
	}

	D3DXVECTOR3 ClockRot = GetRot();

	D3DXVECTOR3 unit = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXMATRIX mtxRot;

	D3DXMatrixRotationY(&mtxRot, ClockRot.y);
	D3DXVec3TransformCoord(&unit, &unit, &mtxRot);

	for (int nCnt = 0; nCnt < NEEDLE_NUMBER; nCnt++)
	{
		if (m_pNeedle[nCnt])
		{
			float fCoeff = (nCnt * 0.9f) + 0.1f;

			D3DXVECTOR3 rot = m_pNeedle[nCnt]->GetRot();

			rot += D3DXVECTOR3(unit.x * DEFAULT_ANIM_FRAME_ANGLE * -fCoeff * m_fAnimCoeff,
							   unit.y * DEFAULT_ANIM_FRAME_ANGLE * -fCoeff * m_fAnimCoeff,
							   unit.z * DEFAULT_ANIM_FRAME_ANGLE * -fCoeff * m_fAnimCoeff);

			if (rot.x <= D3DX_PI * 0.5f)
			{
				rot.x += D3DX_PI * 2.0f;
			}
			if (rot.y <= D3DX_PI * 0.5f)
			{
				rot.y += D3DX_PI * 2.0f;
			}
			if (rot.z <= D3DX_PI * 0.5f)
			{
				rot.z += D3DX_PI * 2.0f;
			}

			m_pNeedle[nCnt]->SetRot(rot);
		}
	}
	/*if (m_pNeedle[1])
	{
		D3DXVECTOR3 rot = m_pNeedle[1]->GetRot();

		rot += D3DXVECTOR3(unit.x * m_fAnimAngle * -0.01f * m_fAnimCoeff, unit.y * m_fAnimAngle * -0.01f * m_fAnimCoeff, unit.z * m_fAnimAngle * -0.01f * m_fAnimCoeff);

		m_pNeedle[1]->SetRot(rot);
	}*/

	CModel::Update();

	CheckPlayer();
}

//描画処理
void CPendulumClock::Draw(void)
{
	CModel::Draw();

	if (m_pPendulum)
	{
		m_pPendulum->Draw(*GetWorldMatrix());
	}

	if (m_pNeedle[0])
	{
		m_pNeedle[0]->Draw(*GetWorldMatrix());
	}
	if (m_pNeedle[1])
	{
		m_pNeedle[1]->Draw(*GetWorldMatrix());
	}
}



//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CPendulumClock* CPendulumClock::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const float fShadowHeight)
{
	CPendulumClock* pClock = new CPendulumClock;		//インスタンスを生成する

	if (FAILED(pClock->Init()))
	{//初期化処理
		return nullptr;
	}

	pClock->SetModel(CModel::MODEL_CLOCK);
	pClock->SetPos(pos);
	pClock->SetRot(rot);
	pClock->SetShadowHeight(fShadowHeight);

	pClock->m_pPendulum = CModelPart::Create(CModel::MODEL_PENDULUM, D3DXVECTOR3(0.0f, 140.0f, -26.0f), Vec3Null);

	if (pClock->m_pPendulum)
	{
		pClock->m_pPendulum->SetShadowHeight(fShadowHeight);
	}

	pClock->m_pNeedle[0] = CModelPart::Create(CModel::MODEL_CLOCK_NEEDLE, D3DXVECTOR3(0.0f, 162.0f, -28.6f), Vec3Null);

	if (pClock->m_pNeedle[0])
	{
		pClock->m_pNeedle[0]->SetShadowHeight(fShadowHeight);
	}

	pClock->m_pNeedle[1] = CModelPart::Create(CModel::MODEL_CLOCK_NEEDLE, D3DXVECTOR3(0.0f, 162.0f, -28.6f), Vec3Null);

	if (pClock->m_pNeedle[1])
	{
		pClock->m_pNeedle[1]->SetShadowHeight(fShadowHeight);
	}

	pClock->m_pHitbox = CBoxHitbox::Create(pos, Vec3Null, D3DXVECTOR3(28.0f, 187.0f, 28.0f), CHitbox::TYPE_NEUTRAL, pClock);

	return pClock;			//生成したインスタンスを返す
}



//=============================================================================
//
//								静的関数
//
//=============================================================================




void CPendulumClock::CheckPlayer(void)
{
	D3DXVECTOR3 playerPos = CApplication::GetGame()->GetPlayer()->GetPos();
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 distance = playerPos - pos;

	float dist = D3DXVec3Length(&distance);

	if (dist <= DEFAULT_RANGE)
	{
		float fTime = 2500.0f * (DEFAULT_RANGE) / (60.0f * dist);

		CApplication::GetGame()->AddTime(fTime);

		if (dist != 0)
		{
			m_fAnimCoeff = (2000.0f / dist);
		}
	}
	else
	{
		m_fAnimCoeff = 1.0f;
	}
}