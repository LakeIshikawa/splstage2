#include "SeigenJikan.h"
#include "..\\Management\\GameControl.h"
#include "..\\Event\\GameOverEvt.h"
#include "..\\Light\\Light.h"

/**
	�W���ݽ�׸�
*/
SeigenJikan::SeigenJikan()
{
	mTimer		 = 0.0f;
	mTimeUpTimer = 0.0f;
	mTimeFl		 = false;
	mMax		 = 0.0f;
}

/**
	�W���޽�׸�
*/
SeigenJikan::~SeigenJikan()
{}


/************************************************************//**
*	���Ԃ��o������
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
			//�۲݂��~�߂�
			GAMECONTROL->GetJiki()->SetSuperPause();
			//ײĂ��~�߂�
			GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();
		}

	}
	//TIME UP�\�����I�������c
	if( GAMECONTROL->GetTxtGraphicController()->IsFinished() && mTimer >= mMax ){
		if( !GAMECONTROL->GetJiki()->IsDying() ){
			GAMECONTROL->GetJiki()->SetSuperControl();
			GAMECONTROL->GetJiki()->Die();
		}
	}

	//�������� ON/OFF
	if( GAMECONTROL->GetJiki()->IsDying() || !GAMECONTROL->GetJiki()->IsControl()){
		SeigenJikanOff();
	}else{
		SeigenJikanOn();
	}

}
/*
	���b�o���Ă��邩
*/
float SeigenJikan::GetRemainingTime()
{
	return mTimer;

}

/*
	�������Խ���
*/
void SeigenJikan::SeigenJikanOn()
{
	mTimeFl = true;
}
/*
	�������Խį��
*/
void SeigenJikan::SeigenJikanOff()
{
	mTimeFl = false;
}

/*
	�ð�ޖ���MAX����
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
	��������ؾ��
*/
void SeigenJikan::SeigenJikanReset()
{
	mTimer = 0.0f;
}

