#pragma once

#include "Event.h"
#include "..\\Management\\GameControl.h"

/*
	画面がフェードアウトし、
	ゲームオーバー画面に移します
*/
class StageClearEvt : public Event
{
public:
	StageClearEvt();
	~StageClearEvt();

	void Trigger();
};
