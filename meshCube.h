//=============================================================================
//
// meshcube.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _MESHCUBE_H_
#define _MESHCUBE_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"
#include <vector>

class CMeshCube : public CObject
{
public:
	CMeshCube();										//�R���X�g���N�^
	CMeshCube(const int nPriority);					//�R���X�g���N�^
	~CMeshCube() override;								//�f�X�g���N�^

	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��
	void SetPriority(const int nPriority);				//�v���C�I���e�B�̐ݒ菈��

	const D3DXVECTOR3 GetSize(void);					//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override;			//�ʒu�̎擾����
	const float GetFriction(void);						//���C�W���̎擾����

	void SetTexture(CObject::TextType texture);			//�e�N�X�`���̐ݒ菈��

	static CMeshCube* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, const D3DXVECTOR3 size);							//��������

	static bool CubeInteraction(CObject* pObj);							//�����蔻��̏���
	static CMeshCube* CubeInteraction(CObject* pObj, float* fHeight);		//�����蔻��̏���

	static void ClearCubes(void);

private:
	void SetVertex(void);								//���_�C���f�b�N�X�̐ݒ菈��

	static const int MAX_CUBE_PRIORITY = 2;

	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff;					//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;						//�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;									//�ʒu
	D3DXVECTOR3 m_rot;									//����
	D3DXVECTOR3 m_size;									//�P�ʂ̃T�C�Y
	D3DXMATRIX m_mtxWorld;								//�����h�}�g���b�N�X
	int m_nVertexNumber;								//���b�V���t�B�[���h�̒��_��
	int m_nIndexNumber;									//���b�V���t�B�[���h�̃C���f�b�N�X��
	int m_nPolygonNumber;								//���b�V���t�B�[���h�̃|���S����
	float m_fFriction;									//���C�W��
	int	  m_nPriority;									//�v���C�I���e�B
	float m_fShadowHeight;

	static std::vector <CMeshCube*> m_vMeshCube;		//���b�V���ւ̃|�C���^�̃x�N�g��

};


#endif