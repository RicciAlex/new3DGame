//=============================================================================
//
// rendering.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef RENDERING_H
#define RENDERING_H

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �O���錾
//=============================================================================
class CMembraneShading;
class CPhongShading;

//=============================================================================
// �����_�����O�N���X
//=============================================================================
class CRenderer
{
public:
	CRenderer();									//�R���X�g���N�^
	~CRenderer();									//�f�X�g���N�^
	HRESULT Init(HWND hWnd, bool bWindow);			//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��
													
	LPDIRECT3DDEVICE9 GetDevice(void);				//�f�o�C�X�̎擾����
	CMembraneShading* GetMembraneEffect(void);		//�V�F�[�_�[�̃G�t�F�N�g�̎擾����
	CPhongShading* GetPhongEffect(void);

	void ChangeFog(void);
	void SetDeepFog(const bool bFog);				//�t�H�O�̐ݒ菈��
	void SetFogColor(const D3DXCOLOR col);			//�t�H�O�̐F�̐ݒ菈��

private:
	void DrawFPS(void);								//FPS�̕`�揈��
	void UpdateFog(void);							//�t�H�O�̍X�V����
	void UpdateFogColor(void);						//�t�H�O�̐F�̍X�V����

private:

	static const int DEFAULT_FOG_CHANGE_TIME = 120;	//�t�H�O�̕ύX�t���[����
	static const float DEFAULT_FOG_NEAR;			//�t�H�O�̊J�n����
	static const float DEFAULT_FOG_FAR;				//�t�H�O�̏I������
	static const float DEEP_FOG_NEAR;				//�t�H�O�̊J�n����(���x����)
	static const float DEEP_FOG_FAR;				//�t�H�O�̏I������(���x����)
	
	LPDIRECT3D9 m_pD3D;								// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice;					// Device�I�u�W�F�N�g
	LPD3DXFONT m_pFont;								//�t�H���g

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

	CMembraneShading* m_pMembrane;					//�V�F�[�_�[�̃G�t�F�N�g�ւ̃|�C���^
	CPhongShading* m_pPhong;
};

#endif // !RENDERING_H