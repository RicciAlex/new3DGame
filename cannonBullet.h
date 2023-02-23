//=============================================================================
//
// cannonBullet.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _CANNON_BULLET_H_
#define _CANNON_BULLET_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBoss;


class CCannonBullet : public CModel
{
public:

	CCannonBullet();				//�R���X�g���N�^
	~CCannonBullet() override;		//�f�X�g���N�^

	HRESULT Init(void) override;	//����������
	void Uninit(void) override;		//�I������
	void Update(void) override;		//�X�V����

	static CCannonBullet* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 target);			//��������
	static CCannonBullet* Create(const D3DXVECTOR3 pos, CBoss* pBoss);			//��������

private:

	void SetSpeed(const D3DXVECTOR3 target);		//���x�̐ݒ菈��

	static const float GRAVITY_ACCELERATION;		//�d�͉����x
	static const int DEFAULT_LIFE;					//�f�B�t�H���g�̃��C�t

	D3DXVECTOR3 m_move;		//���x
	int m_nLife;			//���C�t
	CBoss* m_pBoss;			//�{�X�ւ̃|�C���^

};


#endif