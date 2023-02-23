//=============================================================================
//
// score.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _SCORE_H
#define _SCORE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================


class CScore
{
public:

	static const int DEFAULT_STAR_SCORE;			//�P�̐��̃X�R�A
	static const int RANKING_SCORE = 5;		//�����L���O�̃X�R�A��

	enum STAGE
	{
		FIRST_STAGE = 0,
		SECOND_STAGE,

		STAGE_MAX
	};

	CScore();		//�R���X�g���N�^
	~CScore();		//�f�X�g���N�^

	void AddScore(const int nScore);	//�X�R�A�̉��Z����
	void AddStar(void);					//���̃X�R�A�̉��Z����
	void SetTime(const float nTime);	//���Ԃ̐ݒ菈��
	void GotDamaged(void);				//�_���[�W���󂯂����A�Ăяo���֐�
	void SetStage(const STAGE stage);	//�X�e�[�W�̐ݒ菈��
	void LoadRanking(void);				//�����L���O�̃��[�h����
	void SaveRanking(void);				//�����L���O�̃Z�[�u����

	const int GetScore(void);			//�X�R�A�̎擾����
	const int GetStarNumber(void);		//���̐��̎擾����
	const int GetTimeScore(void);		//�N���A���Ԃ̃{�[�i�X�̎擾����
	const int GetPerfectBonus(void);	//�{�[�i�X�̎擾����
	const STAGE GetStage(void);			//�X�e�[�W�̎擾����
	int* GetRanking(const int nStage);	//�����L���O�̎擾����

	void Clear(void);					//�N���A����
	
	static CScore* Create(void);		//��������

private:

	int SortRanking(const STAGE stage);	//�����L���O�̃\�[�g����
	void CalcScore(void);				//�X�R�A�̌v�Z����

	static const int MAX_TIME_BONUS;		//�ő�̎��ԃ{�[�i�X
	static const int PERFECT_CLEAR_BONUS;	//�_���[�W���󂯂Ȃ��ꍇ�̃{�[�i�X
	static const char m_rankingPass[STAGE_MAX][248];	//�����L���O�̊O���t�@�C���̑��΃p�X

	static int m_ranking[STAGE_MAX][RANKING_SCORE];		//�����L���O�̃X�R�A

	int m_nScore;			//�X�R�A
	int m_nRank;			//�����N
	int m_nStarNum;			//�E��������
	int m_nTimeScore;		//�N���A���Ԃ̃{�[�i�X
	bool m_bPerfect;		//��x���_���[�W���󂯂Ȃ��������ǂ���

	STAGE m_stage;			//���݂̃X�e�[�W

};


#endif