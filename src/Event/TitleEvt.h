#pragma once

#include "Event.h"
#include "..\\Management\\GameControl.h"

/*
	���ى��
*/
class TitleEvt : public Event
{
public:
	TitleEvt();
	~TitleEvt();

	void Trigger();
};
