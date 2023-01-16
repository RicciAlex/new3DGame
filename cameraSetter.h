//=============================================================================
//
// cameraSetter.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef CAMERA_SETTER_H
#define CAMERA_SETTER_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"
#include "player.h"

//=============================================================================
//前方宣言
//=============================================================================

class CCameraSetter : public CObject
{
public:
	CCameraSetter();						//コンストラクタ
	~CCameraSetter() override;				//デストラクタ

	HRESULT Init(void) override;			//初期化処理
	void Uninit(void) override;				//終了処理
	void Update(void) override;				//更新処理
	void Draw(void) override;				//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;	//位置の設定処理
	const D3DXVECTOR3 GetPos(void) override;		//位置の取得処理

	static CCameraSetter* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, CPlayer::CAMERA_POS target);		//生成処理

private:

	bool TestOverlap(void);			//プレイヤーと重なっているかどうか

	D3DXVECTOR3 m_pos;				//位置
	D3DXVECTOR3 m_size;				//サイズ
	CPlayer::CAMERA_POS m_CameraTarget;		//カメラの目的の位置

	bool m_bActive;					//使用中であるかどうか
};



#endif