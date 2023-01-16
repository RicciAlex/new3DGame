//=============================================================================
//
// accelerationFloor.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef ACCELERATION_FLOOR_H
#define ACCELERATION_FLOOR_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object3D.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBoxHitbox;


class CAccelerationFloor : public CObject_3D
{
public:
	CAccelerationFloor();						//�R���X�g���N�^
	~CAccelerationFloor() override;				//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	void SetSpeed(const D3DXVECTOR2 speed);		//���x�̐ݒ菈��
	void SetSpeed(const float speedX, const float speedY);			//���x�̐ݒ菈��

	void SetTextureTiling(const D3DXVECTOR2 tiling) override;					//�e�N�X�`���̑傫���̐ݒ菈��
	void SetTextureTiling(const float fTiling) override;				//�e�N�X�`���̑傫���̐ݒ菈��
	void SetTextureTiling(const float fTilingX, const float fTilingY) override;					//�e�N�X�`���̑傫���̐ݒ菈��

	
	static CAccelerationFloor* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXVECTOR2 speed);		//��������
	static CAccelerationFloor* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXVECTOR2 speed, CObject::TextType texture);		//��������

private:

	bool m_bActive;
	D3DXVECTOR2 m_speed;

	CBoxHitbox* m_pHitbox;

};


#endif