#pragma once

#include "..\\Stage.h"
/*
	�Q�[���I�[�o�[���
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