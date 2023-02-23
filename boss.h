//=============================================================================
//
// boss.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _BOSS_H_
#define _BOSS_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "model.h"

//=============================================================================
//前方宣言
//=============================================================================



class CBoss : public CModel
{
public:
	CBoss();						//コンストラクタ
	~CBoss() override;				//デストラクタ
									
	HRESULT Init(void) override;	//初期化処理
	void Uninit(void) override;		//終了処理
	void Update(void) override;		//更新処理
	void Draw(void) override;		//描画処理
	
	void DealDamage(void);					//ダメージを受ける処理
	void DealDamage(const int nDamage);		//ダメージを受ける処理

	static CBoss* Create(void);		//生成処理

private:

	enum STATE
	{
		STATE_SPAWN = 0,
		STATE_ATTACK,
		STATE_DAMAGE,
		STATE_DEATH,

		STATE_MAX
	};

	enum BOSS_ATTACK
	{
		ATTACK_ICICLE = 0,
		ATTACK_BOULDER,
		ATTACK_TWISTER,

		ATTACK_MAX
	};

	void UpdateState(void);									//状態によっての更新処理
	void SelectAttack(const D3DXVECTOR3 &playerPos);		//攻撃の設定処理
	void SetIcicleAttack(const D3DXVECTOR3 &playerPos);		//Icicle攻撃の設定処理
	void SetBoulderAttack(const D3DXVECTOR3 &playerPos);	//Boulder攻撃の設定処理
	void SetTwisterAttack(const D3DXVECTOR3 &playerPos);	//Twister攻撃の設定処理
	void UpdateAttack(const D3DXVECTOR3 &playerPos);		//現在の攻撃の更新処理
	void IcicleUpdate(const D3DXVECTOR3 &playerPos);		//Icicle攻撃の更新処理	
	void BoulderUpdate(const D3DXVECTOR3 &playerPos);		//Boulder攻撃の更新処理

	static const D3DXVECTOR3 DEFAULT_POS;			//ディフォルトの位置
	static const int DEFAULT_LIFE;					//ディフォルトの体力
	static const int DEFAULT_INVULNERABILITY_FRAMES;	//ディフォルトの無敵状態フレーム数
	static const int DEFAULT_SPAWN_FRAMES;			//ディフォルトのスポーンフレーム数
	static const int DEFAULT_DESPAWN_TIME;			//ディフォルトのディスポーンフレーム数
	static const float DEFAULT_DESPAWN_SPEED;		//ディフォルトのディスポーン速度

	//=======================================================================================
	//Icicle攻撃
	static const int DEFAULT_ICICLE_COOLDOWN;		//ディフォルトのIcicle攻撃のクールダウン
	static const int ICICLE_ROAR_DELAY;				//鳴き声のディレイ
	static const int SET_TARGET_DELAY;				//目的の位置の設定のディレイ
	static const int ICICLE_ATTACK_DELAY;			//攻撃までのディレイ
	//=======================================================================================
	//=======================================================================================
	//Boulder攻撃
	static const int DEFAULT_BOULDER_COOLDOWN;				//ディフォルトのBoulder攻撃のクールダウン
	static const int THROWN_BOULDER_NUMBER;					//投げた岩の数
	static const int THROW_DELAY;							//投げる間のディレイ
	static const D3DXVECTOR3 BOULDER_SPAWN_RELATIVE_POS;	//Boulder攻撃のスポーンの相対位置
	//=======================================================================================
	//=======================================================================================
	//Twister攻撃
	static const int DEFAULT_TWISTER_COOLDOWN;		//ディフォルトのTwister攻撃のクールダウン
	static const float DEFAULT_TWISTER_DISTANCE;	//スポーンからプレイヤーまでの距離
	//=======================================================================================


	D3DXVECTOR3 m_targetPos;	//攻撃の位置
	BOSS_ATTACK m_presentAttack;	//現在の攻撃
	STATE m_state;				//状態
	int m_nCntAttack;			//攻撃カウンター
	int m_nCntCooldown;			//クールダウンのカウンター
	int m_nCntDamage;			//ダメージのカウンター
	int m_nLife;				//体力
	float m_fRelativeTranslation;				//相対移動

};


#endif