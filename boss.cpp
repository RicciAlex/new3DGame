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
#include "iceBoulder.h"
#include "twister.h"
#include "score.h"


#include "rendering.h"
#include "inputKeyboard.h"


//=============================================================================
//								静的変数の初期化
//=============================================================================
const D3DXVECTOR3 CBoss::DEFAULT_POS = { 0.0f, 200.0f, 2775.0f };			//ディフォルトの位置
const int CBoss::DEFAULT_LIFE = 4;						//ディフォルトの体力
const int CBoss::DEFAULT_INVULNERABILITY_FRAMES = 120;	//ディフォルトの無敵状態フレーム数
const int CBoss::DEFAULT_SPAWN_FRAMES = 180;			//ディフォルトのスポーンフレーム数
const int CBoss::DEFAULT_DESPAWN_TIME = 300;			//ディフォルトのディスポーンフレーム数
const float CBoss::DEFAULT_DESPAWN_SPEED = -4.0f;		//ディフォルトのディスポーン速度

//=======================================================================================
//Icicle攻撃
const int CBoss::DEFAULT_ICICLE_COOLDOWN = 320;			//ディフォルトのIcicle攻撃のクールダウン
const int CBoss::ICICLE_ROAR_DELAY = 60;				//鳴き声のディレイ
const int CBoss::SET_TARGET_DELAY = 130;				//目的の位置の設定のディレイ
const int CBoss::ICICLE_ATTACK_DELAY = 150;				//攻撃までのディレイ
//=======================================================================================
//=======================================================================================
//Boulder攻撃
const int CBoss::DEFAULT_BOULDER_COOLDOWN = 250;		//ディフォルトのBoulder攻撃のクールダウン
const int CBoss::THROWN_BOULDER_NUMBER = 4;				//投げた岩の数
const int CBoss::THROW_DELAY = 30;						//投げる間のディレイ
const D3DXVECTOR3 CBoss::BOULDER_SPAWN_RELATIVE_POS = { 800.0f, 0.0f, -100.0f };	//Boulder攻撃のスポーンの相対位置
//=======================================================================================
//=======================================================================================
//Twister攻撃
const int CBoss::DEFAULT_TWISTER_COOLDOWN = 480;		//ディフォルトのTwister攻撃のクールダウン
const float CBoss::DEFAULT_TWISTER_DISTANCE = 200.0f;	//スポーンからプレイヤーまでの距離
//=======================================================================================


//コンストラクタ
CBoss::CBoss()
{
	//メンバー変数をクリアする
	m_targetPos = Vec3Null;
	m_presentAttack = (BOSS_ATTACK)0;
	m_state = (STATE)0;
	m_nCntAttack = 0;
	m_nCntCooldown = 0;
	m_nCntDamage = 0;
	m_nLife = 0;
	m_fRelativeTranslation = 0.0f;
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
	m_state = STATE_SPAWN;
	SetShadowDraw(false);
	SetScale(4);
	SetDrawDistance(5000.0f);
	m_nLife = DEFAULT_LIFE;

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
	SetPos(playerPos + DEFAULT_POS + D3DXVECTOR3(0.0f, m_fRelativeTranslation, 0.0f));

	//基本クラスの更新処理
	CModel::Update();

	//状態によっての更新処理
	UpdateState();
}

//描画処理
void CBoss::Draw(void)
{
	if (m_nCntDamage % 20 < 9)
	{
		CModel::Draw();
	}
}

//ダメージを受ける処理
void CBoss::DealDamage(void)
{
	m_nLife--;

	if (m_nLife > 0)
	{
		CApplication::GetRenderer()->SetFogColor(D3DXCOLOR(1.0f,
			1.0f - (1.0f - ((float)m_nLife / (float)DEFAULT_LIFE)),
			1.0f - (1.0f - ((float)m_nLife / (float)DEFAULT_LIFE)),
			1.0f));

		m_nCntDamage = DEFAULT_INVULNERABILITY_FRAMES;
		m_state = STATE_DAMAGE;
	}
	else
	{
		CApplication::GetRenderer()->SetFogColor(ColorWhite);
		m_state = STATE_DEATH;
		m_nCntCooldown = DEFAULT_DESPAWN_TIME;
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WIN);
	}
}

//ダメージを受ける処理
void CBoss::DealDamage(const int nDamage)
{
	m_nLife -= nDamage;

	if (m_nLife > 0)
	{
		CApplication::GetRenderer()->SetFogColor(D3DXCOLOR(1.0f,
			1.0f - (1.0f - ((float)m_nLife / (float)DEFAULT_LIFE)),
			1.0f - (1.0f - ((float)m_nLife / (float)DEFAULT_LIFE)),
			1.0f));

		m_nCntDamage = DEFAULT_INVULNERABILITY_FRAMES;
		m_state = STATE_DAMAGE;
	}
	else
	{
		CApplication::GetRenderer()->SetFogColor(ColorWhite);
		m_state = STATE_DEATH;
		m_nCntCooldown = DEFAULT_DESPAWN_TIME;
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WIN);
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

//状態によっての更新処理
void CBoss::UpdateState(void)
{
	D3DXVECTOR3 playerPos = CApplication::GetGame()->GetPlayer()->GetPos();

	switch (m_state)
	{

	case CBoss::STATE_SPAWN:

	{
		m_nCntCooldown++;

		if (m_nCntCooldown >= DEFAULT_SPAWN_FRAMES)
		{
			m_nCntCooldown = 0;
			m_state = STATE_ATTACK;
		}
	}

		break;

	case CBoss::STATE_ATTACK:

	{
		UpdateAttack(playerPos);
	}

		break;

	case CBoss::STATE_DAMAGE:

	{
		m_nCntDamage--;

		if (m_nCntDamage <= 0)
		{
			m_nCntDamage = 0;
			m_nCntAttack = 0;
			m_nCntCooldown = 0;
			m_state = STATE_ATTACK;
			m_presentAttack = ATTACK_MAX;
		}
	}

		break;

	case CBoss::STATE_DEATH:

	{
		m_nCntCooldown--;

		if (m_nCntCooldown < 0)
		{
			CScore* pScore = CApplication::GetScore();
			CMode* pMode = CApplication::GetModeInstance();

			if (pScore && pMode)
			{
				if (pMode->IsGame())
				{
					pScore->SetTime(CApplication::GetGame()->GetTime());
				}
			}

			CApplication::SetFade(CApplication::MODE_RESULTS);

			m_nCntCooldown = INT_MAX;
		}
		else
		{
			m_fRelativeTranslation += DEFAULT_DESPAWN_SPEED;
		}
	}

		break;

	default:
		break;
	}
}

//攻撃の設定処理
void CBoss::SelectAttack(const D3DXVECTOR3 &playerPos)
{
	m_nCntCooldown--;

	if (CApplication::GetGame()->GetPlayer()->GetLanded())
	{
		if (m_nCntCooldown <= 0)
		{
			m_nCntAttack = 0;
			int nSelect = random(0, ATTACK_MAX - 1);

			switch (nSelect)
			{
			case ATTACK_ICICLE:

				SetIcicleAttack(playerPos);
				m_nCntCooldown = DEFAULT_ICICLE_COOLDOWN;

				break;

			case ATTACK_BOULDER:

				SetBoulderAttack(playerPos);
				m_nCntCooldown = DEFAULT_BOULDER_COOLDOWN;

				break;

			case ATTACK_TWISTER:

				SetTwisterAttack(playerPos);
				m_nCntCooldown = DEFAULT_TWISTER_COOLDOWN;

				break;

			default:
				break;
			}
		}
	}
}

//Icicle攻撃の処理
void CBoss::SetIcicleAttack(const D3DXVECTOR3 &playerPos)
{
	m_presentAttack = ATTACK_ICICLE;
}

//Boulder攻撃の処理
void CBoss::SetBoulderAttack(const D3DXVECTOR3 &playerPos)
{
	m_presentAttack = ATTACK_BOULDER;
}

//Twister攻撃の処理
void CBoss::SetTwisterAttack(const D3DXVECTOR3 &playerPos)
{
	D3DXVECTOR3 distance = D3DXVECTOR3((float)random(-500, 500), 0.0f, (float)random(-500, 500));
	D3DXVec3Normalize(&distance, &distance);
	distance.x *= DEFAULT_TWISTER_DISTANCE;
	distance.z *= DEFAULT_TWISTER_DISTANCE;
	D3DXVECTOR3 pos = playerPos + distance;

	CTwister::Create(pos);
	m_presentAttack = ATTACK_TWISTER;
}

//攻撃の更新処理
void CBoss::UpdateAttack(const D3DXVECTOR3 &playerPos)
{
	SelectAttack(playerPos);

	if (m_presentAttack == ATTACK_ICICLE)
	{
		IcicleUpdate(playerPos);
	}
	else if (m_presentAttack == ATTACK_BOULDER)
	{
		BoulderUpdate(playerPos);
	}
}

//Icicle攻撃の更新処理	
void CBoss::IcicleUpdate(const D3DXVECTOR3 &playerPos)
{
	m_nCntAttack++;

	if (m_nCntAttack == ICICLE_ROAR_DELAY)
	{
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ROAR);
	}
	else if (m_nCntAttack == SET_TARGET_DELAY)
	{
		m_targetPos = playerPos;
	}
	if (m_nCntAttack >= ICICLE_ATTACK_DELAY)
	{
		m_nCntAttack = 0;

		CIcicle::Create(m_targetPos);
		CIcicle::Create(m_targetPos+ D3DXVECTOR3(50.0f, 0.0f, 0.0f));
		CIcicle::Create(m_targetPos+ D3DXVECTOR3(-50.0f, 0.0f, 0.0f));
		CIcicle::Create(m_targetPos+ D3DXVECTOR3(0.0f, 0.0f, 50.0f));
		CIcicle::Create(m_targetPos+ D3DXVECTOR3(0.0f, 0.0f, -50.0f));

		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ICICLE);

		m_presentAttack = ATTACK_MAX;
	}
}

//Boulder攻撃の更新処理
void CBoss::BoulderUpdate(const D3DXVECTOR3 & playerPos)
{
	m_nCntAttack++;

	if (m_nCntAttack % THROW_DELAY == 0 && m_nCntAttack / THROW_DELAY < THROWN_BOULDER_NUMBER + 1)
	{
		D3DXVECTOR3 pos = GetPos();
		pos.y = playerPos.y;
		float fDir = 1.0f;

		if (random(0, 99) % 2 == 1)
		{
			fDir *= -1.0f;
		}

		CIceBoulder::Create(pos + D3DXVECTOR3(BOULDER_SPAWN_RELATIVE_POS.x * fDir, BOULDER_SPAWN_RELATIVE_POS.y, BOULDER_SPAWN_RELATIVE_POS.z));
		m_presentAttack = ATTACK_BOULDER;

		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_THROW);
	}
}
