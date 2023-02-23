//=============================================================================
//
// ranking.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _RANKING_H
#define _RANKING_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"
#include "object.h"
#include "score.h"

//=============================================================================
//�O���錾
//=============================================================================
class CObject_2D;
class CUIString;


class CRanking : public CMode
{
public:

	CRanking();							//�R���X�g���N�^
	~CRanking() override;				//�f�X�g���N�^

	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����

	static CRanking* Create(void);		//��������

private:

	static CObject::TextType TEXT_TYPE[CScore::STAGE_MAX][2];		//�w�i�̃e�N�X�`���̎��

	static const D3DXVECTOR3 STRING_POS;		//�����L���O�̕�����̈ʒu
	static const D3DXVECTOR3 ARROW_POS[2];		//�A���[UI�̈ʒu
	static const D3DXVECTOR2 ARROW_SIZE;		//�A���[UI�̃T�C�Y
	static const D3DXVECTOR2 BG_SIZE[2];		//�w�i�̃T�C�Y

	int m_nPresentStage;				//���݂̃X�e�[�W

	CObject_2D* m_pBg[2];				//�w�i�ւ̃|�C���^
	CUIString* m_pRank[CScore::RANKING_SCORE];		//�����L���O�ւ̃|�C���^

};


#endif