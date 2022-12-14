//=============================================================================
//
// ShurikenTrap.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SHURIKEN_TRAP_H
#define SHURIKEN_TRAP_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCylinderHitbox;
class CButton;


class CShurikenTrap : CObject
{
public:
	CShurikenTrap();									//�R���X�g���N�^
	~CShurikenTrap() override;							//�f�X�g���N�^
														
	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��
	const D3DXVECTOR3 GetPos(void) override;			//�ʒu�̎擾����

	static CShurikenTrap* Create(const D3DXVECTOR3 pos, const float Yrot, const float fDistance);	//��������
	static CShurikenTrap* Create(const D3DXVECTOR3 pos, const float Yrot, const float fDistance, 
								 const D3DXCOLOR buttonCol, const D3DXCOLOR triggeredCol);			//��������

private:

	D3DXVECTOR3 m_spawnPos;				//�e�̔����ʒu
	D3DXVECTOR3 m_rot;					//����
	int			m_nDelay;				//�f�B���C

	CButton*	m_pButton;				//�{�^���ւ̃|�C���^
	CCylinderHitbox* m_pHitbox;			//�q�b�g�{�b�N�X
};



#endif