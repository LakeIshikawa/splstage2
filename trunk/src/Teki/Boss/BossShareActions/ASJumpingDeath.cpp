#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "ASJumpingDeath.h"
#include "ASWaitForMaku.h"
#include "ASFadeOutAndStageClear.h"
#include "..\\..\\..\\Light\\Light.h"

/************************************************************//**
*	
****************************************************************/
void ASJumpingDeath::OnEnter() 
{
	// ¼Þ¬ÝÌß
	mSpX = GF("SHINIPATT_SPX");
	mAccX = 0;
	mSpY = -GF("SHINIPATT_SHOSP");
	mAccY = SP->GRAVITY;

	// ËÛ²Ý‚Æ×²Ä‚ð‚Æ‚ß‚é
	GAMECONTROL->GetJiki()->SetSuperPause();
	GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();

	// ±¸¼®ÝØ½Ä
	mParent->RemoveAllActions(this);
}


/************************************************************//**
*	‰æ–Ê‚É“ü‚Á‚ÄI‚í‚è
****************************************************************/
bool ASJumpingDeath::Update() 
{

	mSpY += mAccY;
	mX += mSpX;
	mY += mSpY;

	// I—¹ðŒ
	return mY > SP->SCRSZY*2;
}

/************************************************************//**
*	ŽŸ‚Ì½Ã°Ä‚ÉˆÚ‚é
****************************************************************/
void ASJumpingDeath::OnExit() 
{
	// –‹‚ð•Â‚¶‚é
	GAMECONTROL->GetMaku()->Close();
	mParent->QueueAction( new ASWaitForMaku(true) );

	// Ìª°ÄÞ±³Ä
	mParent->QueueAction( new ASFadeOutAndStageClear() );

}
