#pragma once

#include "Event.h"
#include "..\\Management\\GameControl.h"

/*
	画面がフェードアウトし、
	ゲームオーバー画面に移します
*/
class ResetAllEvt : public Event
{
public:
	ResetAllEvt();
	~ResetAllEvt();

	void Trigger();
};
