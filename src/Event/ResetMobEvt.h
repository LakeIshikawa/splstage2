#pragma once

#include "Event.h"
#include "..\\Management\\GameControl.h"

/*
	Mob���X�g�����Z�b�g����
*/
class ResetMobEvt : public Event
{
public:
	ResetMobEvt();
	~ResetMobEvt();

	void Trigger();
};
