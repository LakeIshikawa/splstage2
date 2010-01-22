#include "GameOverScr.h"
#include "..\\..\\Management\\GameControl.h"
#include "..\\..\\Event\\ResetAllEvt.h"

GameOverScr::GameOverScr()
{
}

GameOverScr::~GameOverScr()
{}

void GameOverScr::Process()
{

	if( !mIsSEPlayed ){
		mIsSEPlayed = true;
		//SE
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\game_over.wav");
	}

	if( !mFading ){
		if( GAMECONTROL->GetFader()->FadeIn() ){
			WAIT_TIMER(mTimer, 7.0f)
				mFading = true;
			WAIT_END
		}
	}
	else{
		if( GAMECONTROL->GetFader()->FadeOut() )
			GAMECONTROL->GetEventManager()->Request(new ResetAllEvt());
	}


	//•`‰æ
	DX_DRAW("graphics\\screen\\back_gameover.png",	//”wŒi
		  0,   0,  0, 0, 800, 600);
	DX_DRAW("graphics\\screen\\Gameover.png", 	//GAMEOVER
		150, 150, 0, 0, 490, 120);

}

void GameOverScr::Load()
{
	mTimer = 0.0f;
	mFading = false;
	mIsSEPlayed = false;
}

void GameOverScr::UnLoad()
{

}