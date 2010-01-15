#pragma once

#include "..\\Stage.h"


/*
	スタッフロール
*/
class TeamLogo : public Stage
{
public:
	TeamLogo();
	~TeamLogo();

	void Load();
	void UnLoad();
	void Process();

private:
	float mAlpha;

	enum STATUS{
		FADEIN,
		WAIT,
		FADEOUT
	} mStatus;

	float mTimer;
};