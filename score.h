//=============================================================================
//
// score.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef _SCORE_H
#define _SCORE_H

//=============================================================================
//インクルードファイル
//=============================================================================


class CScore
{
public:

	static const int DEFAULT_STAR_SCORE;			//１つの星のスコア
	static const int RANKING_SCORE = 5;		//ランキングのスコア数

	enum STAGE
	{
		FIRST_STAGE = 0,
		SECOND_STAGE,

		STAGE_MAX
	};

	CScore();		//コンストラクタ
	~CScore();		//デストラクタ

	void AddScore(const int nScore);	//スコアの加算処理
	void AddStar(void);					//星のスコアの加算処理
	void SetTime(const float nTime);	//時間の設定処理
	void GotDamaged(void);				//ダメージを受けた時、呼び出す関数
	void SetStage(const STAGE stage);	//ステージの設定処理
	void LoadRanking(void);				//ランキングのロード処理
	void SaveRanking(void);				//ランキングのセーブ処理

	const int GetScore(void);			//スコアの取得処理
	const int GetStarNumber(void);		//星の数の取得処理
	const int GetTimeScore(void);		//クリア時間のボーナスの取得処理
	const int GetPerfectBonus(void);	//ボーナスの取得処理
	const STAGE GetStage(void);			//ステージの取得処理
	int* GetRanking(const int nStage);	//ランキングの取得処理

	void Clear(void);					//クリア処理
	
	static CScore* Create(void);		//生成処理

private:

	int SortRanking(const STAGE stage);	//ランキングのソート処理
	void CalcScore(void);				//スコアの計算処理

	static const int MAX_TIME_BONUS;		//最大の時間ボーナス
	static const int PERFECT_CLEAR_BONUS;	//ダメージを受けない場合のボーナス
	static const char m_rankingPass[STAGE_MAX][248];	//ランキングの外部ファイルの相対パス

	static int m_ranking[STAGE_MAX][RANKING_SCORE];		//ランキングのスコア

	int m_nScore;			//スコア
	int m_nRank;			//ランク
	int m_nStarNum;			//拾った星数
	int m_nTimeScore;		//クリア時間のボーナス
	bool m_bPerfect;		//一度もダメージを受けなかったかどうか

	STAGE m_stage;			//現在のステージ

};


#endif