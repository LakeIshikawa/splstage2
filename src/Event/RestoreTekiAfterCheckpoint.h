#pragma once

#include "Event.h"
#include "..\\Management\\GameControl.h"

/*
	Mob���X�g�����Z�b�g����
*/
class RestoreTekiAfterCheckpoint : public Event
{
public:
	RestoreTekiAfterCheckpoint(int rCheckpointX);
	~RestoreTekiAfterCheckpoint();

	void Trigger();

private:
	int mCheckpointX;
};
