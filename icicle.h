//=============================================================================
//
// icicle.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef ICICLE_H
#define ICICLE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCylinderHitbox;


class CIcicle : public CModel
{
public:

	CIcicle();											//�R���X�g���N�^
	~CIcicle() override;								//�f�X�g���N�^
														
	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����

	static CIcicle* Create(const D3DXVECTOR3 pos);		//��������

private:

	static const D3DXVECTOR3 DEFAULT_DAMAGE_HITBOX_SIZE;		//�f�B�t�H���g�̃_���[�W��^����q�b�g�{�b�N�X�̃T�C�Y
	static const D3DXVECTOR3 DEFAULT_BODY_HITBOX_SIZE;			//�f�B�t�H���g�̃_���[�W��^���Ȃ��q�b�g�{�b�N�X�̃T�C�Y
	static const float DEFAULT_STARTING_SCALE;					//�f�B�t�H���g�̏��߂̃X�P�[��
	static const float DEFAULT_MAX_SCALE;						//�f�B�t�H���g�̍ő�̃X�P�[��
	static const float DEFAULT_SCALE_INCREMENT;					//���Z����Ă���X�P�[���̒l
	static const float DEFAULT_APLHA_INCREMENT;					//���Z����Ă��郿�l�̒l
	static const int   DEFAULT_DELAY;							//�f�B�t�H���g�̃f�B���C

	int	  m_nDelay;							//�f�B���C
	int	  m_nCntDelay;						//�f�B���C�̃J�E���^�[
	float m_fAlpha;							//���݂̃��l�̒l

	CCylinderHitbox* m_pDamageHitbox;		//�q�b�g�{�b�N�X�ւ̃|�C���^
	CCylinderHitbox* m_pHitbox;				//�q�b�g�{�b�N�X�ւ̃|�C���^
};





#endif