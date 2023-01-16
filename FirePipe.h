//=============================================================================
//
// FirePipe.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _FIRE_PIPE_H
#define _FIRE_PIPE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CFireParticle;
class CCylinderHitbox;


class CFirePipe : public CModel
{
public:
	CFirePipe();						//�R���X�g���N�^
	~CFirePipe() override;				//�f�X�g���N�^

	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����

	static CFirePipe* Create(const D3DXVECTOR3 pos);							//��������
	static CFirePipe* Create(const D3DXVECTOR3 pos, const int nFireTime);		//��������

private:

	static const int MIN_FIRE_TIME = 1;			//�΂�����/�t����܂ł̃t���[�����̍ŏ��l
	static const int DEFAULT_FIRE_TIME = 180;	//�f�B�t�H���g�̉΂�����/�t����܂ł̃t���[����
	static const D3DXVECTOR3 FIRE_HITBOX_SIZE;	//�΂̃q�b�g�{�b�N�X�̃T�C�Y
	static const D3DXVECTOR3 HITBOX_SIZE;		//�q�b�g�{�b�N�X�̃T�C�Y

	int m_nCntTime;						//���݂̃t���[��
	int m_nFireTime;					//�΂�����/�t����܂ł̃t���[����

	CFireParticle* m_pParticle;			//�p�[�e�B�N���ւ̃|�C���^
	CCylinderHitbox* m_pHitbox;			//�q�b�g�{�b�N�X�ւ̃|�C���^
	CCylinderHitbox* m_pFireHitbox;		//�΂̃q�b�g�{�b�N�X�ւ̃|�C���^

};



#endif