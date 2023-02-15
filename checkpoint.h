//=============================================================================
//
// checkpoint.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef CHECKPOINT_H
#define CHECKPOINT_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CModel;

class CCheckpoint : public CObject
{
public:

	static const float			DEFAULT_RANGE;				//ディフォルトの半径
	static const D3DXCOLOR		DEFAULT_NORMAL_COLOR;		//ディフォルトの普通の色
	static const D3DXCOLOR		DEFAULT_ACTIVE_COLOR;		//ディフォルトのアクティブの色

	CCheckpoint();						//コンストラクタ
	~CCheckpoint() override;			//デストラクタ

	HRESULT Init(void) override;			//初期化処理
	void Uninit(void) override;				//終了処理
	void Update(void) override;				//更新処理
	void Draw(void) override;				//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;	//位置の設定処理
	const D3DXVECTOR3 GetPos(void) override;		//位置の取得処理

	static void Clear(void);

	static CCheckpoint* Create(const D3DXVECTOR3 pos);			//生成処理
	static CCheckpoint* Create(const D3DXVECTOR3 pos, const float fRange);			//生成処理
	static CCheckpoint* Create(const D3DXVECTOR3 pos, const float fRange, const D3DXCOLOR normalCol);			//生成処理
	static CCheckpoint* Create(const D3DXVECTOR3 pos, const float fRange, const D3DXCOLOR normalCol, const D3DXCOLOR activeCol);			//生成処理

private:

	static const int			ANIMATION_FRAMES = 120;		//アニメーションのフレーム数
	static const float			ANIMATION_AMPLITUDE;		

	static bool m_bChange;
	static bool	m_bFirst;				//最初のチェックポイントであるかどうか

	D3DXVECTOR3 m_pos;					//位置
	float		m_fRange;				//半径
	D3DXCOLOR	m_normalCol;			//普通の色
	D3DXCOLOR	m_activeCol;			//アクティブであるときの色
	int			m_nScaleAnimCnt;		//アニメーション用のカウンター
	float		m_fScaleAnim;			//アニメーション用の変数
	bool		m_bActive;				//アクティブであるかどうか

	CModel*		m_pFlag;				//チェックポイントのフラグモデル
	CModel*		m_pAura;				//チェックポイントのオーラのモデル
};

#endif