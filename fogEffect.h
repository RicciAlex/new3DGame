//=============================================================================
//
// fogEffect.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _FOG_EFFECT_H
#define _FOG_EFFECT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "effect.h"


class CFogEffect : public CEffect
{
public:

	CFogEffect();					//�R���X�g���N�^
	~CFogEffect() override;			//�f�X�g���N�^

	HRESULT Init(void) override;	//����������
	void Uninit(void) override;		//�I������
	void Update(void) override;		//�X�V����

	static CFogEffect* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);		//��������

private:

	static const D3DXVECTOR2 DEFAULT_SIZE;
	static const int		 DEFAULT_LIFE;
	static const D3DXCOLOR   DEFAULT_COLOR;

	float m_fAcceleration;				//����

};




#endif