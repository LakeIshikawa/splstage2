#include "TGSThanksForPlaying.h"
#include "..\\..\\Management\\GameControl.h"
#include "..\\..\\Event\\StageClearEvt.h"

TGSThanksForPlaying::TGSThanksForPlaying()
{
	mTimer = 0.0f;
	mFading = false;
}

TGSThanksForPlaying::~TGSThanksForPlaying()
{}

/*
	‰æ‘œ‚Ì•\Ž¦
*/
void TGSThanksForPlaying::Process(){
	if( !mFading ){
		if( GAMECONTROL->GetFader()->FadeIn() ){
			WAIT_TIMER(mTimer, 5.0f)
				mFading = true;
			WAIT_END
		}
	}
	else{
		if( GAMECONTROL->GetFader()->FadeOut() )
			GAMECONTROL->GetEventManager()->Request(new StageClearEvt());
	}

	//•`‰æ
	DX_DRAW("graphics\\screen\\TGS.png", 
		0, 0, 0, 0, SP->SCRSZX, SP->SCRSZY);
}

void TGSThanksForPlaying::Load()
{}

void TGSThanksForPlaying::UnLoad()
{}