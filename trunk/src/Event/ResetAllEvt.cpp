#include "ResetAllEvt.h"

ResetAllEvt::ResetAllEvt()
{}

ResetAllEvt::~ResetAllEvt()
{}

void ResetAllEvt::Trigger()
{
	GAMECONTROL->GetStageManager()->GoToStartScreen();
}