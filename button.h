//=============================================================================
//
// button.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _BUTTON_H_
#define _BUTTON_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCylinderHitbox;

class CButton : public CModel
{
public:
	CButton();						//�R���X�g���N�^
	~CButton() override;			//�f�X�g���N�^

	HRESULT Init(void) override;	//����������
	void Uninit(void) override;		//�I������
	void Update(void) override;		//�X�V����

	bool GetTrigger(void);			//�����ꂽ���ǂ����̎擾����

	static CButton* Create(const D3DXVECTOR3 pos);															//��������	
	static CButton* Create(const D3DXVECTOR3 pos, const D3DXCOLOR normalCol, const D3DXCOLOR pressedCol);	//��������	

private:

	bool m_bTriggered;					//�����ꂽ���ǂ���
		
	CCylinderHitbox* m_pHitbox;			//�q�b�g�{�b�N�X

};



#endif