//=============================================================================
//
// star.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "star.h"
#include "BoxHitbox.h"
#include "application.h"
#include "score.h"
#include "rendering.h"
#include "membraneLighting.h"
#include "camera.h"
#include "directionalLight.h"
#include "game.h"
#include "player.h"
#include "sound.h"

//コンストラクタ
CGoldStar::CGoldStar()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//デストラクタ
CGoldStar::~CGoldStar()
{

}

//初期化処理
HRESULT CGoldStar::Init(void)
{
	if (FAILED(CModel::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	//メンバー変数を初期化する

	return S_OK;
}

//終了処理
void CGoldStar::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//ポインタをnullにする
	}
}

//更新処理
void CGoldStar::Update(void)
{
	CModel::Update();

	if (m_pHitbox)
	{
		m_pHitbox->SetPos(GetPos());

		if (m_pHitbox->GetCollisionState())
		{
			CPlayer * pPlayer = CApplication::GetGame()->GetPlayer();		//プレイヤーの取得

			if (pPlayer)
			{//nullチェック

				pPlayer->AddStar();

				CScore* pScore = CApplication::GetScore();

				if (pScore)
				{
					pScore->AddStar();
				}

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ITEM);
			}

			Release();
			return;
		}
	}
}

//描画処理
void CGoldStar::Draw(void)
{

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();				//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxShadow;			//計算用マトリックス
	D3DMATERIAL9 matDef;							//現在のマテリアル保存用
	D3DXMATERIAL *pMat;								//マテリアルデータへのポインタ
	D3DXVECTOR4 vecLight;							//ライトの向き
	D3DXVECTOR3 ShadowPos, Normal;						//投影用の位置と法線
	D3DXPLANE planeField;							//面
	D3DXMATRIX* mtxWorld = GetWorldMatrix();
	float fScale = GetScale(), fShadowHeight = GetShadowHeight();
	D3DXVECTOR3 pos = GetPos(), rot = GetRot();
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	DWORD nNumMat;
	std::vector <LPDIRECT3DTEXTURE9> vTex;

	GetModel(CModel::MODEL_ITEM_STAR, &pMesh, &pBuffMat, &nNumMat);
	GetTextures(vTex, CModel::MODEL_ITEM_STAR);

													//ライトの向きを設定する
	D3DXVECTOR3 dir = CDirectionalLight::GetPrincipalLightDir();
	D3DXVec3Normalize(&dir, &dir);
	vecLight = D3DXVECTOR4(-dir.x, -dir.y, -dir.z, 0.0f);

	ShadowPos = D3DXVECTOR3(0.0f, fShadowHeight, 0.0f);				//面の高さ
	Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						//面の法線

																//ワールドマトリックスの初期化
	D3DXMatrixIdentity(mtxWorld);
	D3DXMatrixIdentity(&mtxShadow);

	//スケールを反映
	if (fScale != 0.0f)
	{
		D3DXMATRIX mtxScale;

		D3DXMatrixScaling(&mtxScale, fScale, fScale, fScale);
		D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxScale);
	}

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxTrans);

	if (GetShadowDraw())
	{//影の描画のフラグがtrueだったら

	 //影の描画用のマトリックスを作る
		D3DXPlaneFromPointNormal(&planeField, &ShadowPos, &Normal);
		D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

		D3DXMatrixMultiply(&mtxShadow, mtxWorld, &mtxShadow);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

		//現在のマテリアルを保持
		pDevice->GetMaterial(&matDef);

		//マテリアルデータへのポインタの取得
		pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)nNumMat; nCntMat++)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			D3DXCOLOR col = pMat[nCntMat].MatD3D.Diffuse;			//マテリアルの色を保存する

			//マテリアルの色を真っ黒にする
			pMat[nCntMat].MatD3D.Diffuse.r = 0.0f;
			pMat[nCntMat].MatD3D.Diffuse.g = 0.0f;
			pMat[nCntMat].MatD3D.Diffuse.b = 0.0f;
			pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;

			//マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, vTex.data()[nCntMat]);

			//モデルパーツの描画
			pMesh->DrawSubset(nCntMat);

			//マテリアルの色を元に戻す
			pMat[nCntMat].MatD3D.Diffuse.r = col.r;
			pMat[nCntMat].MatD3D.Diffuse.g = col.g;
			pMat[nCntMat].MatD3D.Diffuse.b = col.b;
			pMat[nCntMat].MatD3D.Diffuse.a = col.a;
		}

		pMat = nullptr;

		//保持しいたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, mtxWorld);

	//現在のマテリアルを保持
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタの取得
	pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)nNumMat; nCntMat++)
	{
		//マテリアルの色が設定されていたら、そのマテリアルの色を変えたら、描画して、元に戻す
		D3DXCOLOR c = {};
		D3DXCOLOR scaledCol = {};

		if (fScale != 0.0f)
		{
			scaledCol = pMat[nCntMat].MatD3D.Diffuse;
			pMat[nCntMat].MatD3D.Diffuse.r *= fScale;
			pMat[nCntMat].MatD3D.Diffuse.g *= fScale;
			pMat[nCntMat].MatD3D.Diffuse.b *= fScale;
		}

		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, vTex.data()[nCntMat]);

		CMembraneShading* pMembrane = CApplication::GetRenderer()->GetMembraneEffect();

		if (pMembrane)
		{
			D3DXVECTOR3 posV = CApplication::GetCamera()->GetPos();
			D3DXVECTOR4 cameraPos = D3DXVECTOR4(posV.x, posV.y, posV.z, 1.0f);

			vecLight.w = 1.0f;

			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

			pMembrane->Begin();
			pMembrane->SetMatrix(mtxWorld, &cameraPos, &vecLight);
			pMembrane->SetAmbient(0.0f);
			pMembrane->SetSpecular(60.0f);
			pMembrane->SetSpecularPower(5.0f);

			//薄膜の透明度を設定
			pMembrane->SetAlpha(0.4f);
			pMembrane->BeginPass();
		}

		//モデルパーツの描画
		pMesh->DrawSubset(nCntMat);

		if (pMembrane)
		{
			pMembrane->EndPass();
			pMembrane->End();
		}

		if (fScale != 0.0f)
		{
			pMat[nCntMat].MatD3D.Diffuse.r = scaledCol.r;
			pMat[nCntMat].MatD3D.Diffuse.g = scaledCol.g;
			pMat[nCntMat].MatD3D.Diffuse.b = scaledCol.b;
		}
	}

	//保持しいたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

	//テクスチャの設定
	pDevice->SetTexture(0, nullptr);
}

//位置の設定処理
void CGoldStar::SetPos(const D3DXVECTOR3 pos)
{
	CModel::SetPos(pos);
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CGoldStar* CGoldStar::Create(const D3DXVECTOR3 pos)
{
	CGoldStar* pStar = new CGoldStar;			//インスタンスを生成する

	if (FAILED(pStar->Init()))
	{//初期化処理
		return nullptr;
	}

	pStar->SetPos(pos);													//位置の設定
	pStar->StartRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.01f, 0.0f));		//回転させる
	pStar->SetPriority(5);												//プライオリティの設定

	//ヒットボックスの生成
	pStar->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, -31.3f, 0.0f), D3DXVECTOR3(30.0f, 65.0f, 30.0f), CHitbox::TYPE_VANISHING, pStar);
	
	if (pStar->m_pHitbox)
	{//生成出来たら
		pStar->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);		//プレイヤーと重なることができるように設定する
	}

	return pStar;				//生成したインスタンスを返す
}

CGoldStar * CGoldStar::Create(const D3DXVECTOR3 pos, const float fShadowHeight)
{
	CGoldStar* pStar = new CGoldStar;			//インスタンスを生成する

	if (FAILED(pStar->Init()))
	{//初期化処理
		return nullptr;
	}

	pStar->SetPos(pos);													//位置の設定
	pStar->StartRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.01f, 0.0f));		//回転させる
	pStar->SetPriority(5);												//プライオリティの設定
	pStar->SetShadowHeight(fShadowHeight);								//影のY座標の設定

																		//ヒットボックスの生成
	pStar->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, -31.3f, 0.0f), D3DXVECTOR3(30.0f, 65.0f, 30.0f), CHitbox::TYPE_VANISHING, pStar);

	if (pStar->m_pHitbox)
	{//生成出来たら
		pStar->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);		//プレイヤーと重なることができるように設定する
	}

	return pStar;				//生成したインスタンスを返す
}
