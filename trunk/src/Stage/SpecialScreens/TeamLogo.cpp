#include "TeamLogo.h"
#include "..\\..\\Management\\GameControl.h"
#include "..\\..\\Event\\StageClearEvt.h"

TeamLogo::TeamLogo()
{

}

TeamLogo::~TeamLogo()
{}

/*
	‰æ‘œ‚Ì•\Ž¦
*/
void TeamLogo::Process()
{
	switch( mStatus){
	case FADEIN:
		mAlpha += 0.02f;
		if( mAlpha >= 1.0f ){
			mAlpha = 1.0f;
			mStatus = WAIT;
		}
		break;

	case WAIT:
		WAIT_TIMER(mTimer, 3.0f)
			mStatus = FADEOUT;
		WAIT_END
		break;

	case FADEOUT:
		mAlpha -= 0.02f;
		if( mAlpha <= 0.0f ){
			mAlpha = 0.0f;
			if( GAMECONTROL->GetFader()->FadeOut() )
				STAGE_CLEAR;
		}
		break;

	}

	// •`‰æ
	DX_DRAWALPHA("graphics\\screen\\team_logo.png", 120, 220, 0, 0, 560, 160, mAlpha);
}

void TeamLogo::Load()
{	
	mAlpha = 0;
	mTimer = 0.0f;
	mStatus = FADEIN;
}

void TeamLogo::UnLoad()
{}
