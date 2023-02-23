//=============================================================================
//
// explosion.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CFireEffect;


class CExplosion : public CObject
{
public:

	CExplosion();
	~CExplosion() override;

	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;	//�ʒu�̐ݒ菈��

	const D3DXVECTOR3 GetPos(void) override;		//�ʒu�̎擾����

	static CExplosion* Create(const D3DXVECTOR3 pos);		//��������

private:

	static const int DEFAULT_LIFE;	//�f�B�t�H���g�̃��C�t
	static const int EFFECT_NUMBER;	//���t���[�����������G�t�F�N�g��

	D3DXVECTOR3 m_pos;				//�ʒu
	int m_nLife;					//���C�t

};


#endif