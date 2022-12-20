//=============================================================================
//
// spikeTrap.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SPIKE_TRAP_H
#define SPIKE_TRAP_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBoxHitbox;

class CSpikeTrap : public CModel
{
public:

	CSpikeTrap();							//�R���X�g���N�^
	~CSpikeTrap() override;					//�f�X�g���N�^

	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	void Update(void) override;				//�X�V����
	void Draw(void) override;				//�`�揈��

	void SetStartingDelay(const int nDelay);//�������̃f�B���C�̐ݒ菈��

	static CSpikeTrap* Create(const D3DXVECTOR3 pos);										//��������
	static CSpikeTrap* Create(const D3DXVECTOR3 pos, const float fSpeed);					//��������
	static CSpikeTrap* Create(const D3DXVECTOR3 pos, const float fSpeed, const int nDelay);	//��������(delay�Ƃ����͉̂�������A�O��オ��܂ł̃t���[���ł��B�f�t�H���g��60)
	static CSpikeTrap* Create(const D3DXVECTOR3 pos, const float fSpeed, const int nDelay, const int nStartDelay);	//��������

private:

	int m_nDelay;			//�f�B���C
	int m_nCntTime;			//�A�j���[�V�����J�E���^�[
	float m_fSpeed;			//���x
	float m_fStartingHeight;//�������̍���
	bool m_bMoving;			//�����Ă��邩�ǂ���

	CBoxHitbox* m_pHitbox;	//�q�b�g�{�b�N�X�ւ̃|�C���^	

};



#endif