//=============================================================================
//
// game.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _GAME_H
#define _GAME_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"
#include "object.h"
#include "hitbox.h"
#include <functional>

//=============================================================================
//前方宣言
//=============================================================================
class CPlayer;
class CTimer;
class CPauseMenu;
class CGoal;


class CGame : public CMode
{
public:

	//ステージ
	enum STAGE
	{
		FIRST_STAGE = 0,

		STAGE_MAX
	};

	CGame();						//コンストラクタ
	~CGame() override;				//デストラクタ

	HRESULT Init(void);				//初期化処理
	void Uninit(void);				//終了処理
	void Update(void);				//更新処理

	void AddTime(const float fMilliseconds);		//時間の追加処理

	void SetPlayer(CPlayer* pPlayer);		//プレイヤーの設定処理

	const float GetTime(void);				//時間の取得処理
	CPlayer* GetPlayer(void);				//プレイヤーの取得処理
	CGoal* GetGoal(void);					//ゴールの取得処理

protected:

	void LoadMap(char* pPass, CObject::TextType fieldTexture);		//マップのロード処理

private:

	void LoadVector2(FILE* pFile, D3DXVECTOR2 &vector2);
	void LoadVector3(FILE* pFile, D3DXVECTOR3 &vector3);
	void LoadColor(FILE* pFile, D3DXCOLOR &col);

	void LoadMeshField(FILE* pFile, CObject::TextType fieldTexture);

	void LoadHitbox(FILE* pFile);
	void SetLoadedHitboxType(char* pLoadedType, CHitbox::HITBOX_TYPE &type);
	void SetLoadedHitboxEffect(char* pLoadedType, CHitbox::INTERACTION_EFFECT &effect);

	void LoadGoal(FILE* pFile, CGoal* pGoal);
	void LoadNail(FILE* pFile);
	void LoadSpikeTrap(FILE* pFile);
	void LoadStar(FILE* pFile, int& nStar);
	void LoadShurikenTrap(FILE* pFile);
	void LoadTriggerablePlatform(FILE* pFile);
	void LoadMovingCube(FILE* pFile);
	void LoadAccelerationFloor(FILE* pFile);
	void LoadCameraSetter(FILE* pFile);
	void LoadCheckpoint(FILE* pFile);
	void LoadFallBoard(FILE* pFile);
	void LoadFirePipe(FILE* pFile);
	void LoadFogbot(FILE* pFile);
	void LoadPendulumClock(FILE* pFile);
	void LoadGem(FILE* pFile);
	void LoadIceWall(FILE* pFile);
	void LoadGuideArrow(FILE* pFile);

	CPlayer* m_pPlayer;				//プレイヤーへのポインタ
	CTimer*  m_pTimer;				//タイマーへのポインタ
	CPauseMenu* m_pPauseMenu;		//ポーズメニューへのポインタ
	CGoal*   m_pGoal;				//ゴールへのポインタ

};



#endif