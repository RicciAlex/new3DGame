//=============================================================================
//
// star.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "star.h"
#include "BoxHitbox.h"
#include "application.h"
#include "rendering.h"
#include "membraneLighting.h"
#include "camera.h"
#include "directionalLight.h"

//�R���X�g���N�^
CGoldStar::CGoldStar()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CGoldStar::~CGoldStar()
{

}

//����������
HRESULT CGoldStar::Init(void)
{
	if (FAILED(CModel::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	//�����o�[�ϐ�������������

	return S_OK;
}

//�I������
void CGoldStar::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox)
	{//null�`�F�b�N
		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//�|�C���^��null�ɂ���
	}
}

//�X�V����
void CGoldStar::Update(void)
{
	CModel::Update();

	if (m_pHitbox)
	{
		if (m_pHitbox->GetCollisionState())
		{
			Release();
		}
	}
}

//�`�揈��
void CGoldStar::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();				//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxShadow;			//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;							//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;								//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXVECTOR4 vecLight;							//���C�g�̌���
	D3DXVECTOR3 ShadowPos, Normal;						//���e�p�̈ʒu�Ɩ@��
	D3DXPLANE planeField;							//��
	D3DXMATRIX* mtxWorld = GetWorldMatrix();
	float fScale = GetScale(), fShadowHeight = GetShadowHeight();
	D3DXVECTOR3 pos = GetPos(), rot = GetRot();
	LPD3DXMESH pMesh;
	LPD3DXBUFFER pBuffMat;
	DWORD nNumMat;
	std::vector <LPDIRECT3DTEXTURE9> vTex;

	GetModel(CModel::MODEL_ITEM_STAR, &pMesh, &pBuffMat, &nNumMat);
	GetTextures(vTex, CModel::MODEL_ITEM_STAR);

													//���C�g�̌�����ݒ肷��
	D3DXVECTOR3 dir = CDirectionalLight::GetPrincipalLightDir();
	D3DXVec3Normalize(&dir, &dir);
	vecLight = D3DXVECTOR4(-dir.x, -dir.y, -dir.z, 0.0f);

	ShadowPos = D3DXVECTOR3(0.0f, fShadowHeight, 0.0f);				//�ʂ̍���
	Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);						//�ʂ̖@��

																//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(mtxWorld);
	D3DXMatrixIdentity(&mtxShadow);

	//�X�P�[���𔽉f
	if (fScale != 0.0f)
	{
		D3DXMATRIX mtxScale;

		D3DXMatrixScaling(&mtxScale, fScale, fScale, fScale);
		D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxScale);
	}

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxTrans);

	if (GetShadowDraw())
	{//�e�̕`��̃t���O��true��������

	 //�e�̕`��p�̃}�g���b�N�X�����
		D3DXPlaneFromPointNormal(&planeField, &ShadowPos, &Normal);
		D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

		D3DXMatrixMultiply(&mtxShadow, mtxWorld, &mtxShadow);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

		//���݂̃}�e���A����ێ�
		pDevice->GetMaterial(&matDef);

		//�}�e���A���f�[�^�ւ̃|�C���^�̎擾
		pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)nNumMat; nCntMat++)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);

			D3DXCOLOR col = pMat[nCntMat].MatD3D.Diffuse;			//�}�e���A���̐F��ۑ�����

			//�}�e���A���̐F��^�����ɂ���
			pMat[nCntMat].MatD3D.Diffuse.r = 0.0f;
			pMat[nCntMat].MatD3D.Diffuse.g = 0.0f;
			pMat[nCntMat].MatD3D.Diffuse.b = 0.0f;
			pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;

			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, vTex.data()[nCntMat]);

			//���f���p�[�c�̕`��
			pMesh->DrawSubset(nCntMat);

			//�}�e���A���̐F�����ɖ߂�
			pMat[nCntMat].MatD3D.Diffuse.r = col.r;
			pMat[nCntMat].MatD3D.Diffuse.g = col.g;
			pMat[nCntMat].MatD3D.Diffuse.b = col.b;
			pMat[nCntMat].MatD3D.Diffuse.a = col.a;
		}

		pMat = nullptr;

		//�ێ��������}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}

	//�ێ��������}�e���A����߂�
	pDevice->SetMaterial(&matDef);


	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, mtxWorld);

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^�̎擾
	pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)nNumMat; nCntMat++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//�}�e���A���̐F���ݒ肳��Ă�����A���̃}�e���A���̐F��ς�����A�`�悵�āA���ɖ߂�
		D3DXCOLOR c = {};
		D3DXCOLOR scaledCol = {};

		if (fScale != 0.0f)
		{
			scaledCol = pMat[nCntMat].MatD3D.Diffuse;
			pMat[nCntMat].MatD3D.Diffuse.r *= fScale;
			pMat[nCntMat].MatD3D.Diffuse.g *= fScale;
			pMat[nCntMat].MatD3D.Diffuse.b *= fScale;
		}

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
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

			//�����̓����x��ݒ�
			pMembrane->SetAlpha(0.4f);
			pMembrane->BeginPass();
		}

		//���f���p�[�c�̕`��
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

	//�ێ��������}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CGoldStar* CGoldStar::Create(const D3DXVECTOR3 pos)
{
	CGoldStar* pStar = new CGoldStar;			//�C���X�^���X�𐶐�����

	if (FAILED(pStar->Init()))
	{//����������
		return nullptr;
	}

	pStar->SetPos(pos);													//�ʒu�̐ݒ�
	pStar->StartRotation(D3DXVECTOR3(0.0f, D3DX_PI * 0.01f, 0.0f));		//��]������
	pStar->SetPriority(5);												//�v���C�I���e�B�̐ݒ�

	//�q�b�g�{�b�N�X�̐���
	pStar->m_pHitbox = CBoxHitbox::Create(pos, D3DXVECTOR3(0.0f, -31.3f, 0.0f), D3DXVECTOR3(30.0f, 65.0f, 30.0f), CHitbox::TYPE_VANISHING, pStar);
	
	if (pStar->m_pHitbox)
	{//�����o������
		pStar->m_pHitbox->SetOverlapResponse(CHitbox::TYPE_PLAYER, CHitbox::RESPONSE_OVERLAP);		//�v���C���[�Əd�Ȃ邱�Ƃ��ł���悤�ɐݒ肷��
	}

	return pStar;				//���������C���X�^���X��Ԃ�
}