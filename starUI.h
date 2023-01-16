//=============================================================================
//
// starUI.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _STAR_UI_H_
#define _STAR_UI_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CObject_2D;
class CUIString;


class CStarUI : public CObject
{
public:

	CStarUI();										//�R���X�g���N�^
	~CStarUI() override;							//�f�X�g���N�^

	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	void AddStar(void);								//����1�����Z���鏈��

	void SetPos(const D3DXVECTOR3 pos) override;	//�ʒu�̐ݒ菈��
	void SetTargetStar(const int target);			//�ړI�̐����̐ݒ菈��

	const D3DXVECTOR3 GetPos(void) override;		//�ʒu�̎擾����


	static CStarUI* Create(const int nMaxStar);		//��������

private:

	int m_nStarNumber;					//���݂̐���
	int m_nTargetStar;					//�ړI�̐���
	bool m_bDone;						//�ړI�ɂ������ǂ���

	CObject_2D* m_pStar;				//2D�I�u�W�F�N�g�ւ̃|�C���^
	CUIString*	m_pString;				//�����ւ̃|�C���^

};





#endif