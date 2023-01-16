//=============================================================================
//
// checkpoint.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef CHECKPOINT_H
#define CHECKPOINT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CModel;

class CCheckpoint : public CObject
{
public:

	CCheckpoint();						//�R���X�g���N�^
	~CCheckpoint() override;			//�f�X�g���N�^

	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	void Update(void) override;				//�X�V����
	void Draw(void) override;				//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;	//�ʒu�̐ݒ菈��
	const D3DXVECTOR3 GetPos(void) override;		//�ʒu�̎擾����

	static CCheckpoint* Create(const D3DXVECTOR3 pos);			//��������
	static CCheckpoint* Create(const D3DXVECTOR3 pos, const float fRange);			//��������
	static CCheckpoint* Create(const D3DXVECTOR3 pos, const float fRange, const D3DXCOLOR normalCol);			//��������
	static CCheckpoint* Create(const D3DXVECTOR3 pos, const float fRange, const D3DXCOLOR normalCol, const D3DXCOLOR activeCol);			//��������

private:

	static const int			ANIMATION_FRAMES = 120;		//�A�j���[�V�����̃t���[����
	static const float			ANIMATION_AMPLITUDE;		
	static const float			DEFAULT_RANGE;				//�f�B�t�H���g�̔��a
	static const D3DXCOLOR		DEFAULT_NORMAL_COLOR;		//�f�B�t�H���g�̕��ʂ̐F
	static const D3DXCOLOR		DEFAULT_ACTIVE_COLOR;		//�f�B�t�H���g�̃A�N�e�B�u�̐F

	static bool m_bChange;
	static bool	m_bFirst;				//�ŏ��̃`�F�b�N�|�C���g�ł��邩�ǂ���

	D3DXVECTOR3 m_pos;					//�ʒu
	float		m_fRange;				//���a
	D3DXCOLOR	m_normalCol;			//���ʂ̐F
	D3DXCOLOR	m_activeCol;			//�A�N�e�B�u�ł���Ƃ��̐F
	int			m_nScaleAnimCnt;		//�A�j���[�V�����p�̃J�E���^�[
	float		m_fScaleAnim;			//�A�j���[�V�����p�̕ϐ�
	bool		m_bActive;				//�A�N�e�B�u�ł��邩�ǂ���

	CModel*		m_pFlag;				//�`�F�b�N�|�C���g�̃t���O���f��
	CModel*		m_pAura;				//�`�F�b�N�|�C���g�̃I�[���̃��f��
};

#endif