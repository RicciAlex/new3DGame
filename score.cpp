//=============================================================================
//
// score.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "score.h"
#include "timer.h"
#include <stdio.h>

//=============================================================================
//								静的変数の初期化
//=============================================================================
const int CScore::DEFAULT_STAR_SCORE = 5000;			//１つの星のスコア
const int CScore::MAX_TIME_BONUS = 100000;				//最大の時間ボーナス
const int CScore::PERFECT_CLEAR_BONUS = 50000;			//ダメージを受けない場合のボーナス

const char CScore::m_rankingPass[CScore::STAGE_MAX][248] =
{
	{ "data\\RANKING\\stage1Ranking.txt" },
	{ "data\\RANKING\\stage2Ranking.txt" }
};	//ランキングの外部ファイルの相対パス

int CScore::m_ranking[CScore::STAGE_MAX][CScore::RANKING_SCORE] = 
{
	{ 0, 0, 0, 0, 0},
	{ 0, 0, 0, 0, 0},
};		//ランキングのスコア


//コンストラクタ
CScore::CScore()
{
	//メンバー変数をクリアする
	m_nScore = 0;
	m_nRank = 0;
	m_nStarNum = 0;
	m_nTimeScore = 0;
	m_bPerfect = true;

	m_stage = (STAGE)0;
}

//デストラクタ
CScore::~CScore()
{

}

//スコアの加算処理
void CScore::AddScore(const int nScore)
{
	m_nScore += nScore;

	if (m_nScore < 0)
	{
		m_nScore = 0;
	}
}

//星のスコアの加算処理
void CScore::AddStar(void)
{
	m_nStarNum++;
}

//時間の設定処理
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

//ステージの設定処理
void CScore::SetStage(const STAGE stage)
{
	m_stage = stage;
}

//ランキングのロード処理
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

//ランキングのセーブ処理
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

//スコアの取得処理
const int CScore::GetScore(void)
{
	CalcScore();

	return m_nScore;
}

//星の数の取得処理
const int CScore::GetStarNumber(void)
{
	return m_nStarNum;
}

//クリア時間のボーナスの取得処理
const int CScore::GetTimeScore(void)
{
	return m_nTimeScore;
}

//ボーナスの取得処理
const int CScore::GetPerfectBonus(void)
{
	int nBonus = 0;

	if (m_bPerfect)
	{
		nBonus = PERFECT_CLEAR_BONUS;
	}

	return nBonus;
}

//ステージの取得処理
const CScore::STAGE CScore::GetStage(void)
{
	return m_stage;
}

//ランキングの取得処理
int* CScore::GetRanking(const int nStage)
{
	if (nStage < 0 || nStage >= STAGE_MAX)
	{
		return nullptr;
	}

	return m_ranking[nStage];
}

//クリア処理
void CScore::Clear(void)
{
	//メンバー変数をクリアする
	m_nScore = 0;
	m_nRank = 0;
	m_nStarNum = 0;
	m_nTimeScore = 0;
	m_bPerfect = true;

	m_stage = (STAGE)0;
}



//=============================================================================
//
//									静的関数
//
//=============================================================================



//生成処理
CScore * CScore::Create(void)
{
	CScore* pScore = new CScore;		//インスタンスを生成する


	return pScore;						//生成したインスタンスを返す
}



//=============================================================================
//
//								プライベート関数
//
//=============================================================================




//ランキングのソート処理
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

//スコアの計算処理
void CScore::CalcScore(void)
{
	int nPerfectClear = 0;

	if (m_bPerfect)
	{
		nPerfectClear = PERFECT_CLEAR_BONUS;
	}

	m_nScore = m_nTimeScore + nPerfectClear + (m_nStarNum * DEFAULT_STAR_SCORE);
}
