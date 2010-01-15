#pragma once

#include "Event.h"
#include "..\\Management\\GameControl.h"

/*
	Mobリストをリセットする
*/
class ResetMobEvt : public Event
{
public:
	ResetMobEvt();
	~ResetMobEvt();

	void Trigger();
};
