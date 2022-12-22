//=============================================================================
//
// model.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _MODEL_H
#define _MODEL_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"
#include <vector>

class CModel : public CObject
{
public:

	//�}�e���A���̐F
	struct ModelColor
	{
		int nMatNumber;
		D3DXCOLOR col;
	};

	//���f���̎��
	enum ModelType
	{
		MODEL_SPIKE_BALL = 0,
		MODEL_PLAIN_SPHERE,
		MODEL_METAL_CUBE,
		
		MODEL_PLAYER_HEAD,
		MODEL_PLAYER_BODY,
		MODEL_PLAYER_FOREARM,
		MODEL_PLAYER_ARM,
		MODEL_PLAYER_LEG,
		MODEL_PLAYER_FOOT,
		MODEL_SAYA,
		MODEL_KATANA,

		MODEL_FLAG,
		MODEL_NAILS,
		MODEL_GEAR,
		MODEL_BUTTON,
		MODEL_TRAP_PILLAR,
		MODEL_SHURIKEN,
		MODEL_SPIKE_BASE,
		MODEL_SPIKE_TRAP,
		MODEL_LEVER_BASE,
		MODEL_LEVER,

		MODEL_ITEM_STAR,

		MODEL_MAX
	};

	CModel();																			//�R���X�g���N�^
	CModel(const int nPriority);														//�R���X�g���N�^
	virtual ~CModel() override;															//�f�X�g���N�^
													
	virtual HRESULT Init(void) override;												//����������
	virtual void Uninit(void) override;													//�I������
	virtual void Update(void) override;													//�X�V����
	virtual void Draw(void) override;													//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;										//�ʒu�̐ݒ菈��
	const D3DXVECTOR3 GetPos(void) override;											//�ʒu�̎擾����

	void SetRot(const D3DXVECTOR3 ros);													//�����̐ݒ菈��
	const D3DXVECTOR3 GetRot(void);														//�����̎擾����

	void SetScale(const float scale);													//�g�嗦�̐ݒ菈��

	void SetModel(const ModelType type);												//���f���̐ݒ菈��

	void StartRotation(const D3DXVECTOR3 frameRot);										//��]�J�n����
	void StopRotating(void);															//��]��~����
																						
	void SetModelColor(const int nNumMat, const D3DXCOLOR col);							//���f���̐F�̐ݒ菈��
	void SetShadowDraw(const bool bDraw);												//�e�̕`��t���O�̐ݒ菈��
	void SetShadowHeight(const float fHeight);											//�e�̍����̐ݒ菈��

	const float GetShadowHeight(void);													//�e�̍����̎擾����
	const float GetScale(void);															//�g�嗦�̎擾����
	const bool GetShadowDraw(void);														//�e��`�悷�邩�ǂ����̎擾����
	D3DXMATRIX* GetWorldMatrix(void);													//���[���h�}�g���b�N�X�̎擾����

	static void GetModel(ModelType type, LPD3DXMESH* pMesh, LPD3DXBUFFER* pBuffMat, DWORD* numMat);		//���f���̃��b�V�����̎擾����
	static void GetTextures(std::vector <LPDIRECT3DTEXTURE9>& vTex, CModel::ModelType type);			//�}�e���A���̃e�N�X�`���̎擾����
	static void LoadAllModels(void);													//�S���̃��f���̃��[�h����
	static void DestroyAllModels(void);													//�S���̃��f���̔j������

	static CModel* Create(ModelType type, D3DXVECTOR3 pos);								//��������
	static CModel* Create(ModelType type, D3DXVECTOR3 pos, const int nPriority);		//��������

private:

	LPD3DXMESH		m_pMesh;												//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER	m_pBuffMat;												//�}�e���A�����ւ̃|�C���^
	DWORD			m_nNumMat;												//�}�e���A�����̐�
	D3DXVECTOR3		m_pos;													//���݂̈ʒu
	D3DXVECTOR3		m_LastPos;												//�O��̈ʒu
	D3DXVECTOR3		m_move;													//���f���̈ړ���
	D3DXVECTOR3		m_rot;													//����
	D3DXMATRIX		m_mtxRot;												//��]�}�g���b�N�X
	D3DXVECTOR3		m_rotAxis;												//��]��
	float			m_fRotAngle;											//��]�p
	float			m_fScale;												//�g�嗦
	D3DXVECTOR3		m_frameRot;												//1�t���[���̉�]�p�x
	D3DXMATRIX		m_mtxWorld;												//���[���h�}�g���b�N�X
	ModelType		m_type;													//���f���̎��
	std::vector <ModelColor> m_vCol;										//���f���̐F
	bool			m_bShadow;												//�e�����邩�ǂ���
	float			m_fShadowHeight;										//�e�̍���

	static LPD3DXMESH		m_pMeshAll[MODEL_MAX];							//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER		m_pBuffMatAll[MODEL_MAX];						//�}�e���A�����ւ̃|�C���^
	static DWORD			m_nNumMatAll[MODEL_MAX];						//�}�e���A�����̐�
	static char*			m_pModelPass[MODEL_MAX];						//���f���̑��΃p�X
	static std::vector <LPDIRECT3DTEXTURE9> m_vModelTexture[MODEL_MAX];		//���f���̃e�N�X�`���ւ̃|�C���^�̃x�N�g��
};

#endif