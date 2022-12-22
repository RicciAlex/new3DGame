//=============================================================================
//
// movingCube.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef MOVING_CUBE_H
#define MOVING_CUBE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBoxHitbox;

class CMovingCube : public CModel
{
public:

	CMovingCube();									//�R���X�g���N�^
	~CMovingCube() override;						//�f�X�g���N�^
													
	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;	//�ʒu�̐ݒ菈��
	void SetOriginalPos(const D3DXVECTOR3 oPos);	//���̈ʒu�̐ݒ菈��

	void SetMove(const D3DXVECTOR3 move);			//���x�̐ݒ菈��
	void SetMove(const D3DXVECTOR3 move, const float fRange);			//���x�̐ݒ菈��

	static CMovingCube* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const float fRange);		//��������

private:

	void ClampPos(void);				//�ʒu�𐧌����鏈��
	void PushOut(void);					//�v���C���[�̉����o������

	static const D3DXVECTOR3 m_metalBoxSize;

	D3DXVECTOR3 m_OriginalPos;			//���̈ʒu
	D3DXVECTOR3 m_move;					//���x
	D3DXVECTOR3 m_size;					//�T�C�Y
	float       m_fRange;				//�ړ��̌��E

	CBoxHitbox* m_pHitbox;				//�q�b�g�{�b�N�X�ւ̃|�C���^
};


#endif