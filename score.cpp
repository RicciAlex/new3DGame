//=============================================================================
//
// score.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "score.h"
#include "timer.h"
#include <stdio.h>

//=============================================================================
//								�ÓI�ϐ��̏�����
//=============================================================================
const int CScore::DEFAULT_STAR_SCORE = 5000;			//�P�̐��̃X�R�A
const int CScore::MAX_TIME_BONUS = 100000;				//�ő�̎��ԃ{�[�i�X
const int CScore::PERFECT_CLEAR_BONUS = 50000;			//�_���[�W���󂯂Ȃ��ꍇ�̃{�[�i�X

const char CScore::m_rankingPass[CScore::STAGE_MAX][248] =
{
	{ "data\\RANKING\\stage1Ranking.txt" },
	{ "data\\RANKING\\stage2Ranking.txt" }
};	//�����L���O�̊O���t�@�C���̑��΃p�X

int CScore::m_ranking[CScore::STAGE_MAX][CScore::RANKING_SCORE] = 
{
	{ 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0},
};		//�����L���O�̃X�R�A


//�R���X�g���N�^
CScore::CScore()
{
	//�����o�[�ϐ����N���A����
	m_nScore = 0;
	m_nRank = 0;
	m_nStarNum = 0;
	m_nTimeScore = 0;
	m_bPerfect = true;

	m_stage = (STAGE)0;
}

//�f�X�g���N�^
CScore::~CScore()
{

}

//�X�R�A�̉��Z����
void CScore::AddScore(const int nScore)
{
	m_nScore += nScore;

	if (m_nScore < 0)
	{
		m_nScore = 0;
	}
}

//���̃X�R�A�̉��Z����
void CScore::AddStar(void)
{
	m_nStarNum++;
}

//���Ԃ̐ݒ菈��
void CScore::SetTime(const float nTime)
{
	int nMaxTime = CTimer::DEFAULT_MAX_TIME, nMaxScore = MAX_TIME_BONUS;

	int nScore = (int)(nTime * (float)nMaxScore / (float)nMaxTime);

	if (nScore > 0)
	{
		m_nTimeScore += nScore;
	}
}

void CScore::GotDamaged(void)
{
	m_bPerfect = false;
}

//�X�e�[�W�̐ݒ菈��
void CScore::SetStage(const STAGE stage)
{
	m_stage = stage;
}

//�����L���O�̃��[�h����
void CScore::LoadRanking(void)
{
	for (int nCnt = 0; nCnt < STAGE_MAX; nCnt++)
	{
		char aStr[248] = {};

		FILE* pFile = fopen(m_rankingPass[nCnt], "r");

		if (pFile)
		{
			int nRank = 0;

			while (true)
			{
				fscanf(pFile, "%s", aStr);

				if (strcmp(aStr, "RANK") == 0 || strcmp(aStr, "Rank") == 0)
				{
					fscanf(pFile, "%d", &nRank);
					fscanf(pFile, "%s", aStr);
					fscanf(pFile, "%d", &m_ranking[nCnt][nRank - 1]);

					if (nRank >= RANKING_SCORE)
					{
						break;
					}
				}
			}

			fclose(pFile);
		}
	}
}

//�����L���O�̃Z�[�u����
void CScore::SaveRanking(void)
{

	m_nRank = SortRanking(m_stage);

	for (int nCntStage = 0; nCntStage < STAGE_MAX; nCntStage++)
	{

		FILE* pFile = fopen(m_rankingPass[nCntStage], "w");

		if (pFile)
		{
			int nStage = (int)nCntStage + 1;

			fprintf(pFile, "RANK %d:\n\n", nStage);

			for (int nCnt = 0; nCnt < RANKING_SCORE; nCnt++)
			{
				fprintf(pFile, "RANK %d = %d \n", nCnt + 1, m_ranking[nCntStage][nCnt]);
			}

			fclose(pFile);
		}
	}
}

//�X�R�A�̎擾����
const int CScore::GetScore(void)
{
	CalcScore();

	return m_nScore;
}

//���̐��̎擾����
const int CScore::GetStarNumber(void)
{
	return m_nStarNum;
}

//�N���A���Ԃ̃{�[�i�X�̎擾����
const int CScore::GetTimeScore(void)
{
	return m_nTimeScore;
}

//�{�[�i�X�̎擾����
const int CScore::GetPerfectBonus(void)
{
	int nBonus = 0;

	if (m_bPerfect)
	{
		nBonus = PERFECT_CLEAR_BONUS;
	}

	return nBonus;
}

//�X�e�[�W�̎擾����
const CScore::STAGE CScore::GetStage(void)
{
	return m_stage;
}

//�����L���O�̎擾����
int* CScore::GetRanking(const int nStage)
{
	if (nStage < 0 || nStage >= STAGE_MAX)
	{
		return nullptr;
	}

	return m_ranking[nStage];
}

//�N���A����
void CScore::Clear(void)
{
	//�����o�[�ϐ����N���A����
	m_nScore = 0;
	m_nRank = 0;
	m_nStarNum = 0;
	m_nTimeScore = 0;
	m_bPerfect = true;

	m_stage = (STAGE)0;
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CScore * CScore::Create(void)
{
	CScore* pScore = new CScore;		//�C���X�^���X�𐶐�����


	return pScore;						//���������C���X�^���X��Ԃ�
}



//=============================================================================
//
//								�v���C�x�[�g�֐�
//
//=============================================================================




//�����L���O�̃\�[�g����
int CScore::SortRanking(const STAGE stage)
{
	if (stage >= STAGE_MAX)
	{
		return RANKING_SCORE;
	}

	CalcScore();

	int nScores[RANKING_SCORE + 1] = {};
	int nMemory = 0;
	int nRank = RANKING_SCORE;

	for (int nCnt = 0; nCnt < RANKING_SCORE; nCnt++)
	{
		nScores[nCnt] = m_ranking[stage][nCnt];
	}

	nScores[RANKING_SCORE] = m_nScore;

	for (int nCnt = RANKING_SCORE - 1; nCnt >= 0; nCnt--)
	{
		if (nScores[nCnt + 1] > nScores[nCnt])
		{
			nMemory = nScores[nCnt];
			nScores[nCnt] = nScores[nCnt + 1];
			nScores[nCnt + 1] = nMemory;
			nRank = nCnt;
		}
		else
		{
			break;
		}
	}

	for (int nCnt = 0; nCnt < RANKING_SCORE; nCnt++)
	{
		m_ranking[stage][nCnt] = nScores[nCnt];
	}

	return nRank;
}

//�X�R�A�̌v�Z����
void CScore::CalcScore(void)
{
	int nPerfectClear = 0;

	if (m_bPerfect)
	{
		nPerfectClear = PERFECT_CLEAR_BONUS;
	}

	m_nScore = m_nTimeScore + nPerfectClear + (m_nStarNum * DEFAULT_STAR_SCORE);
}
