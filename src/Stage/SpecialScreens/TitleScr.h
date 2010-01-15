#pragma once

#include "..\\Stage.h"

/*
	À²ÄÙ‰æ–Ê
*/
class TitleScr : public Stage
{
public:
	TitleScr(string rDataFname, string rTekiFname, string rScrollBckgImg, 
		string rMapChipGr, SoundController::BGMS rBgm);
	~TitleScr();

	void Process();
	void Load();
	void UnLoad();


private:

	void Init();

	bool  mFading;
	int	  AniNo;
	bool  mGoTugi;
	bool  mLightOn;

};