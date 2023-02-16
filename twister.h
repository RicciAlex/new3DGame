//=============================================================================
//
// twister.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _TWISTER_H_
#define _TWISTER_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"
#include "twisterEffect.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCylinderHitbox;


class CTwister : public CObject
{
public:

	CTwister();							//�R���X�g���N�^
	~CTwister() override;				//�f�X�g���N�^
										
	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����
	void Draw(void) override;			//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��

	const D3DXVECTOR3 GetPos(void) override;			//�ʒu�̎擾����

	static CTwister* Create(const D3DXVECTOR3 pos);			//��������

private:

	void UpdatePos(void);				//�ʒu�̍X�V����
	void UpdateEffectPos(void);			//�G�t�F�N�g�̈ʒu�̍X�V����
	void UpdateHitbox(void);			//�q�b�g�{�b�N�X�̍X�V����

	static const int LAYER_NUMBER = 25;
	static const int EFFECT_PER_LAYER = 20;
	static const float EFFECT_DISTANCE;					//�G�t�F�N�g�̋���
	static const float START_RANGE;						//�͂��߂Ă̔��a
	static const float DEFAULT_SPEED;					//�f�B�t�H���g�̑��x
	static const D3DXVECTOR3 HITBOX_SIZE;				//�q�b�g�{�b�N�X�̃T�C�Y

	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_move;				//���x
	int			m_nLife;			//���C�t
	float		m_fStartingAngle[LAYER_NUMBER];		//�������̊p�x
	float		m_fCurrentAngle;					//���݂̊p�x



	CTwisterEffect* m_pEffect[LAYER_NUMBER * EFFECT_PER_LAYER];			//�G�t�F�N�g�ւ̃|�C���^
	CCylinderHitbox* m_pHitbox;				//�q�b�g�{�b�N�X�ւ̃|�C���^

};




#endif