//=============================================================================
//
// bg.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef BG_H
#define BG_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBillboard;

class CBg : public CObject
{
public:
	CBg();
	~CBg() override;

	virtual HRESULT Init(void);						//����������
	virtual void Uninit(void);						//�I������
	virtual void Update(void);						//�X�V����
	virtual void Draw(void);						//�`�揈��

	virtual void SetPos(const D3DXVECTOR3 pos);		//�ʒu�̐ݒ菈��

	virtual const D3DXVECTOR3 GetPos(void);			//�ʒu�̎擾����

	void SetBg(const D3DXVECTOR3 relativePos, const D3DXCOLOR col);				//�w�i�̒ǉ�����
	void SetBg(const D3DXVECTOR3 relativePos, const D3DXCOLOR col, CObject::TextType type);				//�w�i�̒ǉ�����

	static CBg* Create(const D3DXVECTOR3 pos, const float fDistance);			//��������

private:

	static const int MaxBgLayers = 3;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_relativePos[MaxBgLayers];

	float m_fFar;

	CBillboard* m_pBg[MaxBgLayers];

};




#endif