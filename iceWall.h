//=============================================================================
//
// iceWall.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef ICE_WALL_H
#define ICE_WALL_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CModelPart;
class CBoxHitbox;


class CIceWall : public CObject
{
public:
	CIceWall();							//コンストラクタ
	~CIceWall() override;				//デストラクタ
										
	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理
	void Draw(void) override;			//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;		//位置の設定処理

	const D3DXVECTOR3 GetPos(void) override;			//位置の取得処理

	static CIceWall* Create(const D3DXVECTOR3 pos, const bool bRotate);			//生成処理

private:

	void SetMove(void);				//速度の設定処理

	static const int PART_NUMBER = 5;			//壁のパーツ数
	static const D3DXVECTOR3 RELATIVE_PARTS_POS[PART_NUMBER];	//パーツの相対位置
	static const D3DXVECTOR3 HITBOX_SIZE;		//ディフォルトのサイズ

	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_rot;				//回転
	D3DXVECTOR3 m_move[PART_NUMBER];	//パーツの速度
	D3DXVECTOR3 m_partsRot[PART_NUMBER];	//パーツの速度
	D3DXMATRIX	m_mtxWorld;			//ワールドマトリックス
	int			m_nCntDeath;		//死亡カウンター
	bool		m_bBroken;			//壊れたかどうか

	CModelPart* m_pPart[PART_NUMBER];			//モデルパーツへのポインタ
	CBoxHitbox* m_pHitbox;			//ヒットボックス

};


#endif