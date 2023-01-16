//=============================================================================
//
// fogbot.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _FOGBOT_H
#define _FOGBOT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CFogParticle;
class CBoxHitbox;


class CFogbot : public CModel
{
public:
	CFogbot();								//�R���X�g���N�^
	~CFogbot() override;					//�f�X�g���N�^

	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	void Update(void) override;				//�X�V����

	static CFogbot* Create(const D3DXVECTOR3 pos, const float shadowPos);		//��������

private:

	void UpdateParticle(void);

	static const float DEFAULT_VIEW_RANGE;	//�f�B�t�H���g�̌�����͈͂̔��a
	static D3DXVECTOR3 DEFAULT_PARTICLE_RELATIVE_POS;		//�p�[�e�B�N���̃f�B�t�H���g�̑��Έʒu
	static const float DEFAULT_FRAME_ANGLE;	//�A�j���[�V�����p�̊p�x
	static const float DEFAULT_ANIM_AMPLITUDE;

	float m_fAnimAngle;						//�A�j���[�V�����p�̊p�x
	float m_fRange;							//������͈͂̔��a
	bool  m_bActive;						//�v���C���[�������邩�ǂ���

	CFogParticle* m_pParticle;				//�p�[�e�B�N���ւ̃|�C���^
	CBoxHitbox*   m_pHitbox;				//�q�b�g�{�b�N�X�ւ̃|�C���^

};




#endif