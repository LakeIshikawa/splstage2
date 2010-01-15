#include "ResetMobEvt.h"

ResetMobEvt::ResetMobEvt()
{}

ResetMobEvt::~ResetMobEvt()
{}

void ResetMobEvt::Trigger()
{
	GAMECONTROL->GetMobManager()->InstantReset();
}
