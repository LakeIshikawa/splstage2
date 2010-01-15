#pragma once

#include "Event.h"
#include "..\\Management\\GameControl.h"

/*
	画面がフェードアウトし、
	ゲームオーバー画面に移します
*/
class GameOverEvt : public Event
{
public:
	GameOverEvt();
	~GameOverEvt();

	void Trigger();
};
