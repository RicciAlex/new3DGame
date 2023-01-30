//=============================================================================
//
// fallBoard.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef _FALL_BOARD_H_
#define _FALL_BOARD_H_

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "model.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBoxHitbox;


class CFallBoard : public CModel
{
public:

	static const int DEFAULT_FALL_DELAY = 60;				//��������O�̃t���[����

	CFallBoard();							//�R���X�g���N�^
	~CFallBoard() override;					//�f�X�g���N�^

	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	void Update(void) override;				//�X�V����

	static CFallBoard* Create(const D3DXVECTOR3 pos);								//��������
	static CFallBoard* Create(const D3DXVECTOR3 pos, const int nFallDelay);			//��������

private:

	static const float DEFAULT_FALL_ACCELERATION;			//�f�B�t�H���g�̗�������
	static const D3DXVECTOR3 DEFAULT_BOARD_SIZE;			//�f�B�t�H���g�̃��f���T�C�Y

	D3DXVECTOR3 m_startingPos;				//���̈ʒu
	int	  m_nCntFall;						//�����p�̃J�E���^�[
	int   m_nFallDelay;						//��������܂ł̃t���[����
	float m_fFallSpeed;						//�������x
	bool  m_bFall;							//�������邩�ǂ���

	CBoxHitbox* m_pHitbox;					//�q�b�g�{�b�N�X

};




#endif