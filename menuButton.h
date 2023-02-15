//=============================================================================
//
// menuButton.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CUIString;
class CObject_2D;


class CMenuButton : public CObject
{
public:

	enum BUTTON_TYPE
	{
		BUTTON_TYPE_CONTINUE = 0,
		BUTTON_TYPE_START,
		BUTTON_TYPE_QUIT,
		BUTTON_TYPE_RANKING,

		BUTTON_TYPE_MAX
	};



	CMenuButton();							//�R���X�g���N�^
	~CMenuButton() override;				//�f�X�g���N�^
											
	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	void Update(void) override;				//�X�V����
	void Draw(void) override;				//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��
	void SetOverlap(const bool bOverlap);				

	const D3DXVECTOR3 GetPos(void) override;			//�ʒu�̎擾����
	const bool GetTriggerState(void);					//������Ă��邩�ǂ����̎擾����
	const bool GetOverlap(void);						//�}�E�X�Əd�Ȃ��Ă��邩�ǂ����̎擾����

	static CMenuButton* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char* pString);		//��������
	static CMenuButton* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, D3DXCOLOR stringCol, const char* pString);		//��������
	static CMenuButton* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, D3DXCOLOR stringCol, D3DXCOLOR triggeredCol, const char* pString);		//��������
	static CMenuButton* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char* pString, BUTTON_TYPE type);		//��������
	static CMenuButton* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, D3DXCOLOR stringCol, const char* pString, BUTTON_TYPE type);		//��������
	static CMenuButton* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, D3DXCOLOR stringCol, D3DXCOLOR triggeredCol, const char* pString, BUTTON_TYPE type);		//��������

private:

	bool MouseOnButton(void);			//�}�E�X�J�[�\�����{�^�����d�Ȃ��Ă��邩�ǂ����𔻒f����֐�

	D3DXVECTOR3 m_pos;					//�{�^���̈ʒu
	D3DXVECTOR2 m_size;					//�{�^���̃T�C�Y
	BUTTON_TYPE m_type;					//�{�^���̎��
	D3DXCOLOR   m_normalCol;			//���ʂ̃J���[
	D3DXCOLOR   m_TriggeredCol;			//�}�E�X�J�[�\���Əd�Ȃ������̃J���[
	bool		m_bOverlap;				//�}�E�X�J�[�\���Əd�Ȃ��Ă��邩�ǂ���
	bool		m_bTriggered;			//������Ă��邩�ǂ���

	CUIString*  m_pString;				//�{�^���̔z��

};



#endif