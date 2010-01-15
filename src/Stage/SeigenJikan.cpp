#include "SeigenJikan.h"
#include "..\\Management\\GameControl.h"
#include "..\\Event\\GameOverEvt.h"
#include "..\\Light\\Light.h"

/**
	標準ｺﾝｽﾄﾗｸﾀ
*/
SeigenJikan::SeigenJikan()
{
	mTimer		 = 0.0f;
	mTimeUpTimer = 0.0f;
	mTimeFl		 = false;
	mMax		 = 0.0f;
}

/**
	標準ﾃﾞｽﾄﾗｸﾀ
*/
SeigenJikan::~SeigenJikan()
{}


/************************************************************//**
*	時間を経たせる
****************************************************************/
void SeigenJikan::Process()
{
	if( mTimeFl && !GAMECONTROL->GetJiki()->IsDying() ){
		mTimer += SP->FrameTime;

		//TIME UP
		if( mTimer >= mMax ){
			SeigenJikanOff();
			GAMECONTROL->GetTxtGraphicController()->ShowWithAlphaFade(
				TxtGraphicController::CENTER, GI("TIMEUPMOJI_SX"),GI("TIMEUPMOJI_SY"), 
				"graphics\\txtgraphic\\time_up.png",
				GF("TIMEUPMOJI_DTIME"), GF("TIMEUPMOJI_FSP") );
			//ﾋﾛｲﾝを止める
			GAMECONTROL->GetJiki()->SetSuperPause();
			//ﾗｲﾄを止める
			GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();
		}

	}
	//TIME UP表示が終わったら…
	if( GAMECONTROL->GetTxtGraphicController()->IsFinished() && mTimer >= mMax ){
		if( !GAMECONTROL->GetJiki()->IsDying() ){
			GAMECONTROL->GetJiki()->SetSuperControl();
			GAMECONTROL->GetJiki()->Die();
		}
	}

	//制限時間 ON/OFF
	if( GAMECONTROL->GetJiki()->IsDying() || !GAMECONTROL->GetJiki()->IsControl()){
		SeigenJikanOff();
	}else{
		SeigenJikanOn();
	}

}
/*
	何秒経っているか
*/
float SeigenJikan::GetRemainingTime()
{
	return mTimer;

}

/*
	制限時間ｽﾀｰﾄ
*/
void SeigenJikan::SeigenJikanOn()
{
	mTimeFl = true;
}
/*
	制限時間ｽﾄｯﾌﾟ
*/
void SeigenJikan::SeigenJikanOff()
{
	mTimeFl = false;
}

/*
	ｽﾃｰｼﾞ毎のMAX時間
*/
void SeigenJikan::SetMaxJikan(float rSeigenjikan)
{
	mMax = rSeigenjikan;
}
float SeigenJikan::GetMaxJikan()
{
	return mMax;
}

/*
	制限時間ﾘｾｯﾄ
*/
void SeigenJikan::SeigenJikanReset()
{
	mTimer = 0.0f;
}

