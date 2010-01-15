#include "GameOverEvt.h"

GameOverEvt::GameOverEvt()
{}

GameOverEvt::~GameOverEvt()
{}

void GameOverEvt::Trigger()
{
	GAMECONTROL->GetStageManager()->GoToGameOver();
}