#pragma once

#include "Event.h"
#include "..\\Management\\GameControl.h"

/*
	Mobリストをリセットする
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
