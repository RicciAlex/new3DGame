//=============================================================================
//
// iceWall.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef ICE_WALL_H
#define ICE_WALL_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CModelPart;
class CBoxHitbox;


class CIceWall : public CObject
{
public:
	CIceWall();							//�R���X�g���N�^
	~CIceWall() override;				//�f�X�g���N�^
										
	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����
	void Draw(void) override;			//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��

	const D3DXVECTOR3 GetPos(void) override;			//�ʒu�̎擾����

	static CIceWall* Create(const D3DXVECTOR3 pos, const bool bRotate);			//��������

private:

	void SetMove(void);				//���x�̐ݒ菈��

	static const int PART_NUMBER = 5;			//�ǂ̃p�[�c��
	static const D3DXVECTOR3 RELATIVE_PARTS_POS[PART_NUMBER];	//�p�[�c�̑��Έʒu
	static const D3DXVECTOR3 HITBOX_SIZE;		//�f�B�t�H���g�̃T�C�Y

	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_rot;				//��]
	D3DXVECTOR3 m_move[PART_NUMBER];	//�p�[�c�̑��x
	D3DXVECTOR3 m_partsRot[PART_NUMBER];	//�p�[�c�̑��x
	D3DXMATRIX	m_mtxWorld;			//���[���h�}�g���b�N�X
	int			m_nCntDeath;		//���S�J�E���^�[
	bool		m_bBroken;			//��ꂽ���ǂ���

	CModelPart* m_pPart[PART_NUMBER];			//���f���p�[�c�ւ̃|�C���^
	CBoxHitbox* m_pHitbox;			//�q�b�g�{�b�N�X

};


#endif