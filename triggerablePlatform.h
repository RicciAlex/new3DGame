//=============================================================================
//
// triggerablePlatform.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef TRIGGERABLE_PLATFORM_H
#define TRIGGERABLE_PLATFORM_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CButton;
class CMovingCube;

class CTriggerablePlatform : public CObject
{
public:
	CTriggerablePlatform();						//�R���X�g���N�^
	~CTriggerablePlatform() override;			//�f�X�g���N�^

	HRESULT Init(void) override;										//����������
	void Uninit(void) override;											//�I������
	void Update(void) override;											//�X�V����
	void Draw(void) override;											//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;						//�ʒu�̐ݒ菈��
	void SetOriginalPos(const D3DXVECTOR3 oPos);						//���̈ʒu�̐ݒ菈��
	void SetButtonPos(const D3DXVECTOR3 pos);							//�{�^���̈ʒu�̐ݒ菈��

	const D3DXVECTOR3 GetPos(void) override;							//�ʒu�̎擾����
	const D3DXVECTOR3 GetButtonPos(void);								//�{�^���̈ʒu�̎擾����
	const bool GetTriggeredState(void);									//�{�^���������ꂽ�炩�ǂ����̎擾����

	static CTriggerablePlatform* Create(const D3DXVECTOR3 pos, 
		const D3DXVECTOR3 buttonPos, const D3DXVECTOR3 move, const float fRange);		//��������

private:

	D3DXVECTOR3 m_move;							//�{�^������������̑��x
	bool		m_bTriggered;					//�{�^���������ꂽ���ǂ���

	CButton* m_pButton;							//�{�^���ւ̃|�C���^
	CMovingCube* m_pPlatform;					//�v���b�g�t�H�[���ւ̃|�C���^
};

#endif