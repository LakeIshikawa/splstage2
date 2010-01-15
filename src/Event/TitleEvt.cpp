#include "TitleEvt.h"

TitleEvt::TitleEvt()
{}

TitleEvt::~TitleEvt()
{}

void TitleEvt::Trigger()
{
	GAMECONTROL->GetStageManager()->GoToTitle();
}