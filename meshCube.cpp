//=============================================================================
//
// meshcube.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "meshCube.h"
#include "object2D.h"
#include "application.h"
#include "rendering.h"
#include "directionalLight.h"

std::vector <CMeshCube*> CMeshCube::m_vMeshCube;		//メッシュへのポインタのベクトル

//コンストラクタ
CMeshCube::CMeshCube()
{
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_pTexture = nullptr;
	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_size = Vec3Null;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nVertexNumber = 0;
	m_nIndexNumber = 0;
	m_nPolygonNumber = 0;
	m_fFriction = 0.0f;
	m_nPriority = 3;
	m_fShadowHeight = 0.0f;

	m_vMeshCube.push_back(this);
}

//コンストラクタ
CMeshCube::CMeshCube(const int nPriority) : m_nPriority(nPriority)
{
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_pTexture = nullptr;
	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_size = Vec3Null;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nVertexNumber = 0;
	m_nIndexNumber = 0;
	m_nPolygonNumber = 0;
	m_fFriction = 0.0f;
	m_fShadowHeight = 0.0f;

	m_vMeshCube.push_back(this);
}

//デストラクタ
CMeshCube::~CMeshCube()
{

}

//初期化処理
HRESULT CMeshCube::Init(void)
{
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_pTexture = nullptr;
	m_pos = Vec3Null;
	m_rot = Vec3Null;
	m_size = Vec3Null;
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nVertexNumber = 0;
	m_nIndexNumber = 0;
	m_nPolygonNumber = 0;
	m_fFriction = 0.0f;
	m_fShadowHeight = -199.0f;

	return S_OK;
}

//終了処理
void CMeshCube::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	if (m_pIdxBuff != nullptr)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	int a = m_vMeshCube.size();

	//このインスタンスのアドレスを消す
	for (int nCnt = 0; nCnt < a; nCnt++)
	{
		if (m_vMeshCube.data()[nCnt] == this)
		{
			m_vMeshCube.erase(m_vMeshCube.begin() + nCnt);
			break;
		}
	}
}

//更新処理
void CMeshCube::Update(void)
{
	/*m_rot.y += D3DX_PI * 0.005f;
	m_rot.x += D3DX_PI * 0.001f;*/
}

//描画処理
void CMeshCube::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();
	D3DXMATRIX	mtxRot, mtxTrans, mtxShadow;											//計算用マトリックス
	D3DXVECTOR4 vecLight;							//ライトの向き
	D3DXVECTOR3 pos, Normal;						//投影用の位置と法線
	D3DXPLANE planeField;							//面

													//ライトの向きを設定する
	D3DXVECTOR3 dir = CDirectionalLight::GetPrincipalLightDir();
	D3DXVec3Normalize(&dir, &dir);
	vecLight = D3DXVECTOR4(-dir.x, -dir.y, -dir.z, 0.0f);

	pos = D3DXVECTOR3(0.0f, m_fShadowHeight, 0.0f);				//面の高さ
	Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						//面の法線

																//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&mtxShadow);

	//ワルドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//影の描画用のマトリックスを作る
	D3DXPlaneFromPointNormal(&planeField, &pos, &Normal);
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//ワルドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	VERTEX_3D* pVtx = nullptr;
	D3DXCOLOR col[8] = {};

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		col[nCnt] = pVtx[nCnt].col;
		pVtx[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//影の描画処理
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertexNumber, 0, 20);

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		pVtx[nCnt].col = col[nCnt];
	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	//ワルドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//ステンシルバッファを有効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	//ステンシルバッファと比較する参照値設定
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	//ステンシルバッファの値に対してのマスク設定
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

	//ステンシルテストの比較方法の設定
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);

	//ステンシルテストの結果に対しての反映設定
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画処理
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertexNumber, 0, 20);

	//ステンシルバッファを無効にする
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	pDevice->SetTexture(0, NULL);

	//ポリゴンの描画処理
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVertexNumber, 0, 20);
}

//位置の設定処理
void CMeshCube::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//プライオリティの設定処理
void CMeshCube::SetPriority(const int nPriority)
{
	m_nPriority = nPriority;
}

//サイズの取得処理
const D3DXVECTOR3 CMeshCube::GetSize(void)
{
	return m_size;
}

//位置の取得処理
const D3DXVECTOR3 CMeshCube::GetPos(void)
{
	return m_pos;
}

//摩擦係数の取得処理
const float CMeshCube::GetFriction(void)
{
	return m_fFriction;
}

//テクスチャの設定処理
void CMeshCube::SetTexture(CObject::TextType texture)
{
	LPDIRECT3DTEXTURE9 text = CObject_2D::GetTexturePointer(texture);		//ロードしたテクスチャのポインタを取得
	m_pTexture = text;														//テクスチャを設定する
}












//生成処理
CMeshCube* CMeshCube::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size)
{
	CMeshCube* pCube = new CMeshCube;

	if (FAILED(pCube->Init()))
	{
		return nullptr;
	}

	pCube->m_pos = pos;
	pCube->m_rot = rot;
	pCube->m_size = size;

	pCube->SetVertex();

	return pCube;
}

//当たり判定の処理
bool CMeshCube::CubeInteraction(CObject* pObj)
{
	return false;
}

//当たり判定の処理
CMeshCube* CMeshCube::CubeInteraction(CObject* pObj, float* fHeight)
{
	return nullptr;
}

void CMeshCube::ClearCubes(void)
{

}








//頂点インデックスの設定処理
void CMeshCube::SetVertex(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	m_nVertexNumber = 8;
	m_nIndexNumber = 22;
	m_nPolygonNumber = 20;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVertexNumber,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIndexNumber,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D*pVtx = nullptr;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, m_size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, m_size.y, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, m_size.y, -m_size.z);

	pVtx[4].pos = D3DXVECTOR3(-m_size.x, -m_size.y, m_size.z);
	pVtx[5].pos = D3DXVECTOR3(m_size.x, -m_size.y, m_size.z);
	pVtx[6].pos = D3DXVECTOR3(-m_size.x, -m_size.y, -m_size.z);
	pVtx[7].pos = D3DXVECTOR3(m_size.x, -m_size.y, -m_size.z);

	D3DXCOLOR C[6] = { ColorRed, ColorGreen, ColorBlue, ColorYellow, ColorCyan, ColorMagenta };

	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		D3DXVECTOR3 N = pVtx[nCnt].pos;
		D3DXVec3Normalize(&N, &N);
		pVtx[nCnt].nor = N;
		pVtx[nCnt].col = C[random(0, 5)];
		pVtx[nCnt].tex = Vec2Null;

	}

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

	WORD*pIdx;		//インデックス情報へのポインタ

	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	pIdx[0] = 2;
	pIdx[1] = 0;
	pIdx[2] = 3;
	pIdx[3] = 1;

	pIdx[4] = 1;
	pIdx[5] = 5;
	pIdx[6] = 5;
	pIdx[7] = 1;
	pIdx[8] = 4;
	pIdx[9] = 0;
	pIdx[10] = 6;
	pIdx[11] = 2;
	pIdx[12] = 7;
	pIdx[13] = 3;
	pIdx[14] = 5;
	pIdx[15] = 1;

	pIdx[16] = 1;
	pIdx[17] = 4;

	pIdx[18] = 4;
	pIdx[19] = 6;
	pIdx[20] = 5;
	pIdx[21] = 7;

	m_pIdxBuff->Unlock();
}