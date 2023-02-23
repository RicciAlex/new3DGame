//=============================================================================
//
// sound.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SOUND_H
#define SOUND_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "xaudio2.h"					// 音楽処理に必要

class CSound
{
public:

	enum SOUND_LABEL
	{
		SOUND_LABEL_BGM_TITLE = 0,
		SOUND_LABEL_BGM_STAGE_SELECTION,
		SOUND_LABEL_BGM_TUTORIAL,
		SOUND_LABEL_BGM_STAGE1,
		SOUND_LABEL_BGM_STAGE2,
		SOUND_LABEL_BGM_BOSS,
		SOUND_LABEL_BGM_RESULTS,

		SOUND_LABEL_SE_BUTTON,
		SOUND_LABEL_SE_DAMAGE,
		SOUND_LABEL_SE_FALL_WHISTLE,
		SOUND_LABEL_SE_FIRE,
		SOUND_LABEL_SE_ITEM,
		SOUND_LABEL_SE_GEM,
		SOUND_LABEL_SE_JUMP,
		SOUND_LABEL_SE_SLASH,
		SOUND_LABEL_SE_ROAR,
		SOUND_LABEL_SE_ICE_BROKEN,
		SOUND_LABEL_SE_STEAM,
		SOUND_LABEL_SE_METAL_IMPACT,
		SOUND_LABEL_SE_SWORD,
		SOUND_LABEL_SE_CLOCK,
		SOUND_LABEL_SE_ICE_BOULDER,
		SOUND_LABEL_SE_THROW,
		SOUND_LABEL_SE_ICICLE,
		SOUND_LABEL_SE_TWISTER,
		SOUND_LABEL_SE_CANNON,
		SOUND_LABEL_SE_CANNONBALL,
		SOUND_LABEL_SE_TAP,
		SOUND_LABEL_SE_WHOOSH,
		SOUND_LABEL_SE_WIN,
		
		SOUND_LABEL_SE_AMBIENT_1,
		SOUND_LABEL_SE_AMBIENT_2,
		SOUND_LABEL_SE_AMBIENT_3,

		SOUND_LABEL_MAX
	};

	CSound();								//コンストラクタ
	~CSound();								//デストラクタ

	HRESULT Init(HWND hWnd);				//初期化処理
	void Uninit(void);						//終了処理
	HRESULT Play(SOUND_LABEL label);		//再生処理
	void Stop(SOUND_LABEL label);			//停止処理
	void Stop(void);						//停止処理

	static CSound* Create(HWND hWnd);		//生成処理

private:

	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;


	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);


	static SOUNDPARAM g_aParam[SOUND_LABEL_MAX];

	IXAudio2 *g_pXAudio2 = nullptr;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *g_pMasteringVoice = nullptr;		// マスターボイス
	IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

};

#endif