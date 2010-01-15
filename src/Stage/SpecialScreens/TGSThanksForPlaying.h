#pragma once

#include "..\\Stage.h"

/*
	TGS����
*/
class TGSThanksForPlaying : public Stage
{
public:
	TGSThanksForPlaying();
	~TGSThanksForPlaying();

	void Load();
	void UnLoad();
	void Process();

private:
	float mTimer;
	bool mFading;
};