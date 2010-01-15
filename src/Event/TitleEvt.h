#pragma once

#include "Event.h"
#include "..\\Management\\GameControl.h"

/*
	À²ÄÙ‰æ–Ê
*/
class TitleEvt : public Event
{
public:
	TitleEvt();
	~TitleEvt();

	void Trigger();
};
