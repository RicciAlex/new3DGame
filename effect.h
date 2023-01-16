//=============================================================================
//
// effect.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _EFFECT_H_
#define _EFFECT_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "billboard.h"

class CEffect : public CBillboard
{
public:
	CEffect();								//�R���X�g���N�^
	~CEffect() override;					//�f�X�g���N�^

	virtual HRESULT Init(void) override;	//����������
	virtual void Uninit(void) override;		//�I������
	virtual void Update(void) override;		//�X�V����
	virtual void Draw(void) override;		//�`�揈��
	
	void SetMove(const D3DXVECTOR3 move);	//���x�̐ݒ菈��
	void SetLife(const int nLife);			//���C�t�̐ݒ菈��

	const D3DXVECTOR3 GetMove(void);		//���x�̎擾����

	static CEffect* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col);
	static CEffect* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const int nLife);
	static CEffect* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const D3DXVECTOR3 move);
	static CEffect* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR col, const int nLife, const D3DXVECTOR3 move);

private:

	static const int DEFAULT_LIFE = 60;

	D3DXVECTOR3 m_move;				//���x
	int			m_nLife;			//���C�t
};




#endif