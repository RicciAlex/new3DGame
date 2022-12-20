//=============================================================================
//
// meshcube.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _MESHCUBE_H_
#define _MESHCUBE_H_

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"
#include <vector>

//=============================================================================
//インクルードファイル
//=============================================================================
class CBoxHitbox;

class CMeshCube : public CObject
{
public:
	CMeshCube();										//コンストラクタ
	CMeshCube(const int nPriority);						//コンストラクタ
	~CMeshCube() override;								//デストラクタ

	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理
	void Draw(void) override;							//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;		//位置の設定処理
	void SetMove(const D3DXVECTOR3 move);				//速度の設定処理
	void SetPriority(const int nPriority);				//プライオリティの設定処理

	const D3DXVECTOR3 GetSize(void);					//サイズの取得処理
	const D3DXVECTOR3 GetPos(void) override;			//位置の取得処理
	const float GetFriction(void);						//摩擦係数の取得処理

	void SetTexture(CObject::TextType texture);			//テクスチャの設定処理

	static CMeshCube* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size);							//生成処理
	static CMeshCube* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size, const D3DXVECTOR3 move,
		const float fRange);	//生成処理

	static bool CubeInteraction(CObject* pObj);							//当たり判定の処理
	static CMeshCube* CubeInteraction(CObject* pObj, float* fHeight);		//当たり判定の処理

	static void ClearCubes(void);

private:
	void SetVertex(void);								//頂点インデックスの設定処理
	void ClampMove(void);								//移動を制限する

	static const int MAX_CUBE_PRIORITY = 2;

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					//頂点バッファへのポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;					//インデックスバッファへのポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;						//テクスチャへのポインタ
	D3DXVECTOR3 m_pos;									//位置
	D3DXVECTOR3 m_OriginalPos;							//元の位置
	D3DXVECTOR3 m_rot;									//向き
	D3DXVECTOR3 m_size;									//単位のサイズ
	D3DXMATRIX  m_mtxWorld;								//ワルドマトリックス
	D3DXVECTOR3 m_move;									//速度
	int m_nVertexNumber;								//メッシュフィールドの頂点数
	int m_nIndexNumber;									//メッシュフィールドのインデックス数
	int m_nPolygonNumber;								//メッシュフィールドのポリゴン数
	float m_fFriction;									//摩擦係数
	int	  m_nPriority;									//プライオリティ
	float m_fShadowHeight;								//影の位置のY座標
	float m_fRange;										//移動の限界

	CBoxHitbox* m_pHitbox;								//ヒットボックスへのポインタ

	static std::vector <CMeshCube*> m_vMeshCube;		//メッシュへのポインタのベクトル

};


#endif