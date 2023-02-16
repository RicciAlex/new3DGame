//=============================================================================
//
// iceShard.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _ICE_SHARD_H_
#define _ICE_SHARD_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"


class CIceShard : public CModel
{
public:
	CIceShard();						//�R���X�g���N�^
	~CIceShard() override;				//�f�X�g���N�^
										
	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����

	static CIceShard* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);		//��������

private:

	static const int DEFAULT_LIFE = 90;		//�f�B�t�H���g�̃��C�t
	static const float DEFAULT_GRAVITY_ACCELERATION;		//�d��

	D3DXVECTOR3 m_move;			//���x
	int			m_nCntLife;		//���C�t�̃J�E���^�[

};


#endif