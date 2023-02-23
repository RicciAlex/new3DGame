//=============================================================================
//
// rendering.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef RENDERING_H
#define RENDERING_H

//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CMembraneShading;
class CPhongShading;

//=============================================================================
// レンダリングクラス
//=============================================================================
class CRenderer
{
public:
	CRenderer();									//コンストラクタ
	~CRenderer();									//デストラクタ
	HRESULT Init(HWND hWnd, bool bWindow);			//初期化処理
	void Uninit(void);								//終了処理
	void Update(void);								//更新処理
	void Draw(void);								//描画処理
													
	LPDIRECT3DDEVICE9 GetDevice(void);				//デバイスの取得処理
	CMembraneShading* GetMembraneEffect(void);		//シェーダーのエフェクトの取得処理
	CPhongShading* GetPhongEffect(void);

	void ChangeFog(void);
	void SetDeepFog(const bool bFog);				//フォグの設定処理
	void SetFogColor(const D3DXCOLOR col);			//フォグの色の設定処理

private:
	void DrawFPS(void);								//FPSの描画処理
	void UpdateFog(void);							//フォグの更新処理
	void UpdateFogColor(void);						//フォグの色の更新処理

private:

	static const int DEFAULT_FOG_CHANGE_TIME = 120;	//フォグの変更フレーム数
	static const float DEFAULT_FOG_NEAR;			//フォグの開始距離
	static const float DEFAULT_FOG_FAR;				//フォグの終了距離
	static const float DEEP_FOG_NEAR;				//フォグの開始距離(密度高い)
	static const float DEEP_FOG_FAR;				//フォグの終了距離(密度高い)
	
	LPDIRECT3D9 m_pD3D;								// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice;					// Deviceオブジェクト
	LPD3DXFONT m_pFont;								//フォント

	int	  m_nCntFog;
	int   m_nCntColorFog;
	D3DXVECTOR2 m_fFrameFog;
	D3DXCOLOR   m_targetCol;
	D3DXCOLOR   m_fogColor;
	D3DXCOLOR   m_colorSpeed;
	float m_fFogNear;
	float m_fFogFar;
	float m_fFogTarget;
	bool  m_bChangeFog;
	bool  m_bChangeColor;
	bool  m_bActive;

	CMembraneShading* m_pMembrane;					//シェーダーのエフェクトへのポインタ
	CPhongShading* m_pPhong;
};

#endif // !RENDERING_H