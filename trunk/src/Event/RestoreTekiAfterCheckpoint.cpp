#include "RestoreTekiAfterCheckpoint.h"

RestoreTekiAfterCheckpoint::RestoreTekiAfterCheckpoint(int rCheckpointX)
{
	mCheckpointX = rCheckpointX;
}

RestoreTekiAfterCheckpoint::~RestoreTekiAfterCheckpoint()
{}

void RestoreTekiAfterCheckpoint::Trigger()
{
	GAMECONTROL->GetStageManager()->GetCurrentStage()->GetHaichi()->RestoreTekiAfter(mCheckpointX);
}
