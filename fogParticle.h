//=============================================================================
//
// fogParticle.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _FOG_PARTICLE_H
#define _FOG_PARTICLE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

class CFogParticle : public CObject
{
public:
	CFogParticle();								//�R���X�g���N�^
	~CFogParticle() override;						//�f�X�g���N�^


	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;	//�ʒu�̐ݒ菈��
	void SetActiveState(const bool bActive);		//�G�t�F�N�g���X�|�[�����邩�ǂ����̐ݒ菈��

	const D3DXVECTOR3 GetPos(void) override;		//�ʒu�̎擾����
	const bool GetActiveState(void);				//�G�t�F�N�g���X�|�[�����邩�ǂ����̎擾����

	static CFogParticle* Create(const D3DXVECTOR3 pos);	//��������

private:

	const int DEFAULT_EFFECT_NUMBER = 5;

	D3DXVECTOR3 m_pos;								//�ʒu
	bool		m_bActive;							//�G�t�F�N�g���X�|�[�����邩�ǂ���

};


#endif
