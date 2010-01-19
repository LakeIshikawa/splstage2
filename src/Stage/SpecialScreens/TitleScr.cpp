#include "TitleScr.h"
#include "..\\..\\Management\\GameControl.h"
#include "..\\..\\Light\\Light.h"
#include "..\\..\\Event\\StageClearEvt.h"
#include "..\\..\\Stage\\FixScrollMap.h"

TitleScr::TitleScr(string rDataFname, string rTekiFname, string rScrollBckgImg, string rMapChipGr, SoundController::BGMS rBgm)
{
	mDataFname = rDataFname;
	mTekiFname = rTekiFname;
	mMapChipGr = rMapChipGr;
	mBgm = rBgm;
	
	mpScrollBackground = new ScrollBackground(rScrollBckgImg);
	mpMap = new FixScrollMap();
	mpHaichi = new Haichi();

	Init();
}

void TitleScr::Init()
{
	mFading = false;
	AniNo	= 0;
	mGoTugi = false;
	mLightOn = false;
}

TitleScr::~TitleScr(void)
{
}

void TitleScr::Process()
{
	if( !mFading ){
		if( GAMECONTROL->GetFader()->FadeIn() ){
			mFading = true;
			//–‹‚ð‚ ‚°‚é
			GAMECONTROL->GetMaku()->Open();
			GAMECONTROL->GetSoundController()->SetBGM(mBgm);
		}
	}
	// ƒqƒƒCƒ“‚ðŽ~‚ß‚é
	GAMECONTROL->GetJiki()->SetSuperPause();

	//–‹‚ª‚ ‚ª‚Á‚½‚ç×²Äon
	if( GAMECONTROL->GetMaku()->IsOpen() && !mLightOn ){
		mLightOn = true;
		GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOn();
	}

	//–‹‚ª‚¨‚è‚½‚ç½Ã°¼Þ‚Ö
	if( GAMECONTROL->GetMaku()->IsClosed() && mFading ) mGoTugi = true;

	if( CONTROLLIGHT->GetX() > GI("PUSHSTARTX") && CONTROLLIGHT->GetX() < GI("PUSHSTARTX")+GI("PUSHSTARTSX") &&
		 CONTROLLIGHT->GetY() > GI("PUSHSTARTY") && CONTROLLIGHT->GetY() < GI("PUSHSTARTY")+GI("PUSHSTARTSY") ){
		if( AniNo != 2 ) AniNo = 1;
		if( GAMECONTROL->GetDXController()->IsMouseClicked() &&
			GAMECONTROL->GetMaku()->IsOpen() ){
			AniNo = 2;
			//–‹‚ð‚³‚°‚é
			GAMECONTROL->GetMaku()->Close();
			GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();
			//SE
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_kettei.wav");
		}
	}else{
		if( AniNo == 1 ) AniNo = 0;
	}

	if( mGoTugi ){
		if( GAMECONTROL->GetFader()->FadeOut() )
			GAMECONTROL->GetEventManager()->Request(new StageClearEvt());
	}


	//•`‰æ
	mpScrollBackground->SetScrollP(mpMap->GetScrollP());
	mpScrollBackground->Draw();

	GetMap()->Process();

	//GAMECONTROL->GetLightManager()->Move();

	GAMECONTROL->GetMobManager()->Process();

	DX_DRAW("graphics\\screen\\game start0.png",//Ìß¯¼­½À°Ä
		GI("PUSHSTARTX"), GI("PUSHSTARTY"), GI("PUSHSTARTSX")*AniNo, 0, 
		GI("PUSHSTARTSX")+GI("PUSHSTARTSX")*AniNo, GI("PUSHSTARTSY"));

	GAMECONTROL->GetLightManager()->Draw();

	DX_DRAW("graphics\\screen\\game title.png", //½ÌßØ¯Ã¯ÄÞ½Ã°¼Þ
		GI("TITLEX"), GI("TITLEY"), 0, 0, GI("TITLESX"), GI("TITLESY"));

	GAMECONTROL->GetMaku()->Draw();

}

void TitleScr::Load()
{
	mpMap->Load( mDataFname, mMapChipGr );
	mpHaichi->Load( mTekiFname, mpCheckpointController );
	GAMECONTROL->GetJiki()->SetPos(GF("HERINITX")+500, GF("HERINITY"));
	GAMECONTROL->GetJiki()->ResetLife();
	GAMECONTROL->GetJiki()->ResetTension();
	GAMECONTROL->GetJiki()->ResetEmpacy();
	GAMECONTROL->GetJiki()->ResetTempParams();
	GAMECONTROL->GetJiki()->SetSuperPause();
	GAMECONTROL->GetJiki()->SetMuki(1);

	GAMECONTROL->GetUserLightControl()->GetControlLight()->SetPos( SP->SCRSZX/2, SP->SCRSZY/2 );
	
	Init();

}

void TitleScr::UnLoad()
{
	mpMap->UnLoad();
	mpHaichi->UnLoad();
}
