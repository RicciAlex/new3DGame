//=============================================================================
//
// stageSelectCursor.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _STAGE_SELECT_CURSOR_H_
#define _STAGE_SELECT_CURSOR_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CModel;


class CStageSelectCursor : public CObject
{
public:

	CStageSelectCursor();							//�R���X�g���N�^
	~CStageSelectCursor() override;					//�f�X�g���N�^

	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;	//�ʒu�̐ݒ菈��

	const D3DXVECTOR3 GetPos(void) override;		//�ʒu�̎擾����

	static CStageSelectCursor* Create(const D3DXVECTOR3 pos);		//��������

private:

	static const int JEWEL_NUMBER = 12;			//��΂̐�
	static const D3DXVECTOR3 RELATIVE_POS[JEWEL_NUMBER];		//��΂̑��Έʒu
	static const D3DXCOLOR JEWEL_COLOR[JEWEL_NUMBER / 2];		//��΂̐F

	D3DXVECTOR3 m_pos;							//�ʒu

	CModel* m_pModel[JEWEL_NUMBER];				//���f���ւ̃|�C���^

};


#endif