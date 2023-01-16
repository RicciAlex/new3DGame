//=============================================================================
//
// cameraSetter.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef CAMERA_SETTER_H
#define CAMERA_SETTER_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"
#include "player.h"

//=============================================================================
//�O���錾
//=============================================================================

class CCameraSetter : public CObject
{
public:
	CCameraSetter();						//�R���X�g���N�^
	~CCameraSetter() override;				//�f�X�g���N�^

	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	void Update(void) override;				//�X�V����
	void Draw(void) override;				//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;	//�ʒu�̐ݒ菈��
	const D3DXVECTOR3 GetPos(void) override;		//�ʒu�̎擾����

	static CCameraSetter* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, CPlayer::CAMERA_POS target);		//��������

private:

	bool TestOverlap(void);			//�v���C���[�Əd�Ȃ��Ă��邩�ǂ���

	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_size;				//�T�C�Y
	CPlayer::CAMERA_POS m_CameraTarget;		//�J�����̖ړI�̈ʒu

	bool m_bActive;					//�g�p���ł��邩�ǂ���
};



#endif