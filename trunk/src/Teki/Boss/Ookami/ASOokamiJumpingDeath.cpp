#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "ASOokamiJumpingDeath.h"

/************************************************************//**
*	±ÆÒ°¼®İ
****************************************************************/
void ASOokamiJumpingDeath::BuildAnimation(ActionState* rPrevState)
{
	mAnimation = Animation::ParseFromFile( "data\\animdata\\ookami\\Death.txt" );
}

/************************************************************//**
*	”j•Ğ‚Ìì¬‚Æ•—‚ğ~‚ß‚é
****************************************************************/
void ASOokamiJumpingDeath::OnEnter() 
{
	// •—
	if( storm ) {
		GAMECONTROL->GetMobManager()->Remove(storm);
		storm = NULL;
	}

	// ‰Æ
	/*if( brick ) {
		brick->Destroy();
	}*/
	if( straw ) straw->StopParticles();
	if( rog ) straw->StopParticles();

	// Šî–{ˆ—
	ASJumpingDeath::OnEnter();
}
