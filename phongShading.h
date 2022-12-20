//=============================================================================
//
// phongShading.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _PHONG_SHADING_H
#define _PHONG_SHADING_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

class CPhongShading
{
public:
	CPhongShading(LPDIRECT3DDEVICE9 pDevice);				//�R���X�g���N�^
	~CPhongShading();											//�f�X�g���N�^
	HRESULT Load();											//���[�h����
	void Invalidate();										//�I������
	void Restore();											
	void Begin();											//�J�n����
	void BeginPass();										//�p�X�̊J�n����
	void SetAmbient(float Ambient);							//�����̐ݒ菈��
	void SetAmbient(D3DXVECTOR4* pAmbient);					//�����̐ݒ菈��
	   void SetEmissive( float Emissive );				
	   void SetEmissive( D3DXVECTOR4* pEmissive );	
	void SetSpecular(float Specular);						//�X�y�L�����[�͈̔͂̐ݒ菈��
	void SetSpecularPower(float SpecularPower);				//�X�y�L�����[�̋��x�̐ݒ菈��
	void SetMatrix(D3DXMATRIX* pMatWorld, D3DXVECTOR4* pCameraPos, D3DXVECTOR4* pLightDir);			//�}�g���b�N�X�̐ݒ菈��
	void CommitChanges();									//�ύX�̃Z�[�u����
	void EndPass();											//�p�X�̏I������
	void End();												//�I������
	BOOL IsOK();											//�g�p�ł��邩�ǂ����̏I������

private:
	LPD3DXEFFECT m_pEffect;					
	D3DXHANDLE m_pTechnique;				
	D3DXHANDLE m_pWVP;						
	D3DXHANDLE m_pLightDir;					
	D3DXHANDLE m_pEyePos;					
	D3DXHANDLE m_pAmbient;					
	D3DXHANDLE m_pEmissive;				
	D3DXHANDLE m_pSpecular;					
	D3DXHANDLE m_pSpecularPower;	
	D3DXHANDLE m_pVtxCol;
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;
	LPDIRECT3DDEVICE9 m_pDevice;			
};

#endif