//=============================================================================
//
// spawnTrigger.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _SPAWN_TRIGGER_H
#define _SPAWN_TRIGGER_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"
#include "triggerablePlatform.h"
#include <vector>

//=============================================================================
//前方宣言
//=============================================================================

class CSpawnTrigger : public CObject
{
public:

	CSpawnTrigger();					//コンストラクタ
	~CSpawnTrigger() override;			//デストラクタ
										
	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理
	void Draw(void) override;			//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;		//位置の設定処理
	void AddObject(CObject* pObj, const float fHeight);	//オブジェクトの追加処理
	void AddTriggerPlatform(CTriggerablePlatform* pTrigger);	//トリガーの追加処理

	const D3DXVECTOR3 GetPos(void) override;			//位置の取得処理

	static CSpawnTrigger* Create(void);					//生成処理
	static CSpawnTrigger* Create(const D3DXVECTOR3 pos);					//生成処理

private:

	static const D3DXVECTOR3 DEFAULT_POS;				//ディフォルトの位置

	D3DXVECTOR3 m_pos;									//位置

	CTriggerablePlatform* m_pTrigger;					//トリガーへのポインタ
	std::vector <CObject*> m_vSpawnObj;					//オブジェクトへのポインタ
	std::vector <float>	  m_vObjHeight;					//オブジェクトのY座標
};



#endif