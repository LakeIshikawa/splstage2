#pragma once

#include "..\\Sound\\dsutil.h"
#include "..\\Sound\\Bgm.h"

#include <windows.h>
#include <string>
#include <map>
using namespace std;

#define MAX_BGMS 15

/*
	オーディオの機能を提供します
*/
class SoundController
{
public:
	SoundController();
	~SoundController();

	void Init(HWND rHwnd);
	void Process();

	// インターフェース
	void PlaySE(string rPath);
	void LoopSE(string rPath);
	void StopSE(string rPath);

	enum BGMS{
		TITLE,
		STG1,
		BOSS1,
		HISATU,
		STGCLEAR,
		ENDING,
		STG2,
		BOSS2,
		STG3,
		BOSS3,

	};

	void PlayBGM();
	void PauseBGM();
	void SetBGM( BGMS rBgm );
	void ResetBGMs();
	bool IsBGMPlaying();

	void SetSound(bool mOnOff);

	// データ
	static LPTSTR sData[];

private:
	CSoundManager* mpSoundManager;
	map<string, CSound*> mMapStrToSnd;
	Bgm*	arBgms[MAX_BGMS];
	Bgm*	mCurBgm;

	bool	mSoundOn;

};
