#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASOokamiBlowAttackHitback.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Animation\\Animation.h"


/************************************************************//**
*	‰Æ‚ð‰ó‚·
****************************************************************/
void ASOokamiBlowAttackHitback::OnEnter() 
{
	mSpX = GF("OOKAMI_BKHTSPX") * mMuki?-1:1;
	mSpY = -GF("OOKAMI_BKHTSPY");
}


/************************************************************//**
*	‰æ–Ê‚É“ü‚Á‚ÄI‚í‚è
****************************************************************/
bool ASOokamiBlowAttackHitback::Update() {
	
	//Ë¯ÄÊÞ¯¸
	mSpY += SP->GRAVITY;
	mY += mSpY;
	mX += mSpX;

	// ’…’n
	if( mY >= OOKAMI_STARTY ){
		mY = OOKAMI_STARTY;
		mSpY = 0;
		mSpX = 0;
	}

	// I—¹ðŒ
	return mAnimation->GetLoopCount() == 15;
}

/************************************************************//**
*	ŽŸ‚Ì½Ã°Ä‚ÉˆÚ‚é
****************************************************************/
void ASOokamiBlowAttackHitback::OnExit() 
{
}
