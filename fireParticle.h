//=============================================================================
//
// fireParticle.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _FIRE_PARTICLE_H
#define _FIRE_PARTICLE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

class CFireParticle : public CObject
{
public:
	CFireParticle();								//�R���X�g���N�^
	~CFireParticle() override;						//�f�X�g���N�^


	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;	//�ʒu�̐ݒ菈��
	void SetActiveState(const bool bActive);		//�G�t�F�N�g���X�|�[�����邩�ǂ����̐ݒ菈��

	const D3DXVECTOR3 GetPos(void) override;		//�ʒu�̎擾����
	const bool GetActiveState(void);				//�G�t�F�N�g���X�|�[�����邩�ǂ����̎擾����

	static CFireParticle* Create(const D3DXVECTOR3 pos);	//��������

private:

	const int DEFAULT_EFFECT_NUMBER = 7;

	D3DXVECTOR3 m_pos;								//�ʒu
	bool		m_bActive;							//�G�t�F�N�g���X�|�[�����邩�ǂ���

};


#endif
