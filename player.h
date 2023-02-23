//=============================================================================
//
// player.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CModelPart;
class CAnimator;
class CCylinderHitbox;
class CBoxHitbox;
class CStarUI;

class CPlayer : public CObject
{
public:

	static const float		 DEFAULT_FALL_HEIGHT;						//この高さの下にいると死ぬ
	static const D3DXVECTOR3 m_playerSize;								//プレイヤーのサイズ

	enum Parts
	{
		BODY = 0,								//体
		HEAD,									//頭
		LEFT_ARM,								//左腕
		LEFT_HAND,								//左手
		RIGHT_ARM,								//右腕
		RIGHT_HAND,								//右手
		LEFT_LEG,								//左足
		LEFT_FOOT,								//左太腿
		RIGHT_LEG,								//右足
		RIGHT_FOOT,								//右太腿
		SAYA,									//鞘
		KATANA,									//刀
		PARTS_MAX
	};

	enum STATE
	{
		STATE_NEUTRAL = 0,						//ニュートラル
		STATE_RUNNING,							//走る
		STATE_JUMP_START,
		STATE_JUMP,								//ジャンプ
		STATE_ATTACK,							//攻撃

		STATE_MAX								
	};

	enum PlayerColor
	{
		PLAYER_RED = 0,							//赤
		PLAYER_GREEN,							//緑
		PLAYER_BLUE,							//青
		PLAYER_YELLOW,							//黄
		PLAYER_MAGENTA,							//マゼンタ
		PLAYER_CYAN,							//シアン
		PLAYER_BLACK,							//黒
		PLAYER_WHITE,							//白

		PLAYER_COLOR_MAX
	};

	enum CAMERA_POS
	{
		CAMERA_POS_NORMAL = 0,
		CAMERA_POS_BACK,

		CAMERA_POS_MAX
	};

	CPlayer();															//コンストラクタ
	~CPlayer() override;												//デストラクタ

	HRESULT Init(void) override;										//初期化処理
	void Uninit(void) override;											//終了処理
	void Update(void) override;											//更新処理
	void Draw(void) override;											//描画処理

	void AddStar(void);													//星1つの加算処理

	void SetPos(const D3DXVECTOR3 pos) override;						//位置の設定処理
	void SetRot(const D3DXVECTOR3 rot);									//向きの設定処理
	void SetLanded(void);												//着地しているかどうかの設定処理
	void SetMove(const D3DXVECTOR3 move);								//速度の設定処理
	void SetTargetCameraPos(CAMERA_POS pos);							//カメラの目的の位置の設定処理
	void SetRespawnPoint(const D3DXVECTOR3 pos);						//リスポーンの位置の設定処理
	void SetCameraAnim(const bool bAnim);								//カメラアニメーションの設定処理
	void SetStarNumber(const int nStar);								//星の数の設定処理

	const D3DXVECTOR3 GetPos(void) override;							//位置の取得処理
	const D3DXVECTOR3 GetLastPos(void);									//前回の位置の取得処理
	const D3DXVECTOR3 GetMove(void);									//速度の取得処理
	const bool GetLanded(void);											//着地しているかどうかの取得処理
	const int GetStarNumber(void);										//星の数の取得処理

	static CPlayer* Create(const D3DXVECTOR3 pos,int nCntPlayer);		//生成処理
	static D3DXCOLOR* GetPlayerColors(void);							//プレイヤーの色の取得処理

	void PlayerController(int nCntPlayer);								//プレイヤーのキー処理
	void SetFriction(const float fFriction);

private:

	void TransformUpdate(void);
	void UpdateRotation(void);
	void UpdateHitbox(void);
	void UpdateAnimation(void);
	void FieldUpdate(void);
	void RespawnPlayer(void);
	void HitboxEffectUpdate(void);
	void UpdatePlayerCamera(void);
	void MoveCamera(void);

	static const D3DXVECTOR3 m_baseCameraPos;							//普通のカメラの位置
	static const D3DXVECTOR3 m_baseFocalPointPos;						//普通の注視点の位置
	static const D3DXVECTOR3 m_BackCameraPos;							//後ろのカメラの位置
	static D3DXCOLOR m_playerColor[PLAYER_COLOR_MAX];					//プレイヤーの色
	static const float m_MaxWalkingSpeed;								//最大の歩くスピード
	static const float m_AccelerationCoeff;								//加速係数
	static const float JUMP_SPEED;										//ジャンプ力
	static const float MAX_FALL_SPEED;									//最大の落下スピード
	static const float GRAVITY_ACCELERATION;							//重力
	static const int   ATTACK_TIME;										//攻撃時間

	D3DXVECTOR3 m_pos;													//位置
	D3DXVECTOR3 m_LastPos;												//前回の位置
	D3DXVECTOR3 m_move;													//速度
	D3DXVECTOR3 m_rot;													//向き
	D3DXVECTOR3 m_DestRot;												//目的の角度
	D3DXVECTOR3 m_cameraPos;											//カメラの相対位置
	D3DXVECTOR3 m_cameraTarget;											//カメラの目的の位置
	D3DXVECTOR3 m_respawnPoint;											//リスポーンの位置
	D3DXMATRIX  m_mtxWorld;												//ワールドマトリックス
	int			m_nInvincibilityCnt;									//無敵状態のカウンター
	int			m_nCntAttack;											//攻撃カウンター
	int			m_nIdxPlayer;											//プレイヤー番号
	float		m_fFrictionCoeff;										//摩擦係数
	bool		m_bJump;												//ジャンプしているかどうか
	bool		m_bLanded;												//着地しているかどうか
	bool		m_bMoving;												//移動しているかどうか
	bool		m_bRot;													//回転したかどうか
	bool		m_bHit;													//当たったかどうか
	bool		m_bAttacking;											//アタックしたかどうか
	bool		m_bFall;												//落下しているかどうか
	bool		m_bMoveCamera;											//カメラの位置を更新するかどうか
	bool		m_bCameraAnim;											//カメラアニメーション中であるかどうか

	STATE m_State;														//プレイヤーの状態

	CModelPart* m_pModel[PARTS_MAX];									//モデルへのポインタ
	CAnimator* m_pAnimator;												//アニメーターへのポインタ
	CCylinderHitbox* m_pHitbox;											//ヒットボックス
	CBoxHitbox* m_pAttackHitbox;										//攻撃のヒットボックス
	CStarUI*	m_pUI;													//UIへのポインタ
};

#endif