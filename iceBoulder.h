//=============================================================================
//
// iceBoulder.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _ICE_BOULDER_H_
#define _ICE_BOULDER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCylinderHitbox;


class CIceBoulder : public CModel
{
public:

	CIceBoulder();					//�R���X�g���N�^
	~CIceBoulder() override;		//�f�X�g���N�^
									
	HRESULT Init(void) override;	//����������
	void Uninit(void) override;		//�I������
	void Update(void) override;		//�X�V����


	static CIceBoulder* Create(const D3DXVECTOR3 pos);			//��������

private:

	void SetSpeed(void);				//���x�̐ݒ菈��
	void UpdateHitbox(void);			//�q�b�g�{�b�N�X�̍X�V����
	void CreateShard(void);				//�j�Ђ̐�������

	static const float DEFAULT_GRAVITY_ACCELERATION;			//�d��
	static const int   ATTACK_FRAME;							//�U���̃t���[����
	static const int   SHARD_NUMBER;							//�j�Ђ̐�
	static const D3DXVECTOR3 HITBOX_RELATIVE_POS;				//�q�b�g�{�b�N�X�̑��Έʒu
	static const D3DXVECTOR3 HITBOX_SIZE;						//�q�b�g�{�b�N�X�̃T�C�Y

	
	D3DXVECTOR3 m_target;				//�ړI�̈ʒu
	D3DXVECTOR3 m_move;					//���x

	CCylinderHitbox* m_pHitbox;			//�q�b�g�{�b�N�X�ւ̃|�C���^

};



#endif