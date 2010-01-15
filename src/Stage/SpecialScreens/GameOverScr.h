#pragma once

#include "..\\Stage.h"
/*
	ゲームオーバー画面
*/
class GameOverScr : public Stage
{
public:
	GameOverScr();
	~GameOverScr();

	void Process();
	void Load();
	void UnLoad();

private:
	float mTimer;
	bool mFading;

};