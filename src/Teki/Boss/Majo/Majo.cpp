#include "Majo.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "RollingApple.h"
#include "LightKobitoBlue.h"
#include "LightKobitoRed.h"
#include "LightKobitoGreen.h"
#include "..\\..\\..\\Event\\StageClearEvt.h"
#include "..\\..\\..\\Light\\Light.h"

#include<typeinfo>

/* ｱﾆﾒｰｼｮﾝﾃﾞｰﾀ */
int Majo::sAniData[][MAX_DATA] =
{
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 99 },	// WIN
	{ 6, 5, 4, 3, 2, 3, 4, 3, 2, 1, 99 },		// WINBACK
	{ 12, 13, 14, 15, 99 },							// WINDAMAGE
	{ 0, 1, 2, 1, 99 },								// DOOR
	{ 3, 4, 5, 6, 7, 8, 9, 10, 99 },				// DOORTHROW
	{ 3, 99 },										// DOORTHROWEND
	{ 0, 1, 2, 1, 99 },								// DOOREXIT
	{ 11, 12, 13, 14, 99 },							// DOORDAMAGE
	{ 14, 99 },										// DIYING
	{ 14, 99 }										// DEAD

};

float Majo::sAniTimeData[][MAX_DATA] =
{
	{ 1.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f },	// WIN
	{ 0.6f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f, 0.3f },				// WINBACK
	{ 0.2f, 0.2f, 0.2f, 0.2f },													// WINDAMAGE
	{ 0.2f, 0.2f, 0.2f, 0.2f, },												// DOOR
	{ 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f },							// DOORTHROW
	{ 0.2f },																	// DOORTHROWEND
	{ 0.2f, 0.2f, 0.2f, 0.2f },													// DOOREXIT
	{ 0.2f, 0.2f, 0.2f, 0.2f },													// DOORDAMAGE
	{ 0.2f },																	// DIYING
	{ 0.2f }																	// DEAD

};

/* ｸﾞﾗﾌｨｯｸﾃﾞｰﾀ */
char Majo::sGraphicData[][MAX_NLEN] = 
{
	"graphics\\teki\\boss_witch_front.png",			// WIN
	"graphics\\teki\\boss_witch_front.png",			// WINBACK
	"graphics\\teki\\boss_witch_front.png",			// WINDAMAGE
	"graphics\\teki\\boss_witch_side.png",			// DOOR
	"graphics\\teki\\boss_witch_side.png",			// DOORTHROW
	"graphics\\teki\\boss_witch_side.png",			// DOORTHROWEND
	"graphics\\teki\\boss_witch_side.png",			// DOOREXIT
	"graphics\\teki\\boss_witch_side.png",			// DOORDAMAGE
	"graphics\\teki\\boss_witch_side.png",			// DIYING
	"graphics\\teki\\boss_witch_side.png",			// DEAD
};

int Majo::sMapAtHanteiX[4][MAX_TEN] = 
{
	{ 40, 16, -1 },	//下
	{ -1 },		//上
	{ 51, -1 },	//前
	{ -1 }		//後
};

int Majo::sMapAtHanteiY[4][MAX_TEN] = 
{ 
	{ 54, 54, -1 },	//下
	{ -1 },		//上
	{ 35, -1 },	//前
	{ -1 }		//後
};

int Majo::sShutugenX[5] = { 188, 365, 540, -56, 736 };
int Majo::sShutugenY[5] = { 249, 249, 249, 416, 416 };
int Majo::sRingoX[5] = { 179, 356, 531, 160, 616 };
int Majo::sRingoY[5] = { 285, 285, 285, 472, 472 };

float Majo::sDieSpX[5] = { 0.0f, 0.0f, 0.0f, -1.5f, 1.5f };


Majo::Majo()
{
	mSizeX = GI("MAJOSX");
	mSizeY = GI("MAJOSY");
	MAJO_ARUKI_SPX = GF("MAJO_ARUKI_SPX");
	
	mZ = -1.0f;

	mDropMe = NULL;
	mKobitoOut = false;

	mHp = GI("MAJO_HP");
	mDieTimer = 0.0f;
	mActive = false;
	dmgFlag = false;

	// 当たり判定用
	AddFrame(FR_WIN);
	AddCircle(FR_WIN, SP->GRID_BOGYO, 36, 10, 18);
	AddCircle(FR_WIN, SP->GRID_BOGYO, 36, 46, 18);

	AddFrame(FR_DOOR);
	AddCircle(FR_DOOR, SP->GRID_BOGYO, 60, 50, 18);
	AddCircle(FR_DOOR, SP->GRID_BOGYO, 64, 91, 18);

}

Majo::~Majo()
{}

/*
	どこから入ってくるかを決める
*/
void Majo::SelectEntPoint()
{
	mEntPt = rand()%5;
	dmgFlag = false;

	if( mEntPt < 3 ){ //窓
		mStatus = WIN;
		mSpX = 0;
		mSizeX = GI("MAJOSX");
		mSizeY = GI("MAJOSY");
		mMuki = 0;
		SetCurFrame(FR_WIN);
	}
	else{
		mStatus = DOOR;
		if( mEntPt == 4 ){ // 左
			mMuki = 0;
		}
		else{ // 右
			mMuki = 1;
		}
		SetCurFrame(FR_DOOR);

		mSizeX = GI("MAJO_DOORSX");
		mSizeY = GI("MAJO_DOORSY");
		mSpX = (mMuki?1:-1) * MAJO_ARUKI_SPX;
	}
			
	mX = sShutugenX[mEntPt];
	mY = sShutugenY[mEntPt];

	SetAnim(mStatus);
}

/*
	メイン処理
*/
void Majo::_Move()
{
	if( !mActive ){
		if( GAMECONTROL->GetMaku()->IsOpen() ){
			Activate();
		}
		return;
	}

	switch( mStatus ){
		case DOOR:
			if( !mMuki && mX <= 616 ){
				mStatus = DOORTHROW;
				mSpX = 0;
			}
			else if( mMuki && mX >= 64 ){
				mStatus = DOORTHROW;
				mSpX = 0;
			}
			break;

		case DOOREXIT :
			if ( mX > SP->SCRSZX || mX + mSizeX < 0){
				SelectEntPoint();
			}
			break;

		case DIYING:
			WAIT_TIMER(mDieTimer, GF("STGCLMOJI_BFTIME"))
				mStatus = DEAD;
				GAMECONTROL->GetTxtGraphicController()->ShowWithAlphaFade(
					TxtGraphicController::CENTER, GI("STGCLRMOJI_SX"),GI("STGCLRMOJI_SY"), 
					"graphics\\txtgraphic\\stage_clear_01.png",
					GF("STGCLMOJI_DTIME"), GF("STGCLMOJI_FSP"));
				GAMECONTROL->GetMaku()->Close();
				GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();			
				//BGM
				GAMECONTROL->GetSoundController()->SetBGM(SoundController::STGCLEAR);

			WAIT_END
			break;

		case DEAD:
			if( GAMECONTROL->GetTxtGraphicController()->IsFinished() && GAMECONTROL->GetMaku()->IsClosed() ){
				if( GAMECONTROL->GetFader()->FadeOut() ){
					GAMECONTROL->GetEventManager()->Request(new StageClearEvt());
					GAMECONTROL->GetJiki()->ResetTension();
					GAMECONTROL->GetJiki()->ResetEmpacy();
				}
			}
			break;
	}


	SetAnim(mStatus);

	mSpX += mAccX;
	mSpY += mAccY;
	mX += mSpX; 
	mY += mSpY;
	Teki::Draw();

	// 小人の召喚
	if( mStatus != DIYING )
	{
		KobitoCreate();
	}
}

/*
	落としりんごを生み出す
*/
void Majo::RollingAppleCreate(int rXPx, int rYPx, int rType)
{
	Apple* newapple = new RollingApple(rXPx, rYPx, rType);
	newapple->AddTarget(GAMECONTROL->GetJiki());
	newapple->DisableCollision();

	GAMECONTROL->GetMobManager()->Request(newapple, true);
	mDropMe = newapple;

	// SE
	GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_boss1_atack.wav");
}


/*
	投げりんごを生み出す
*/
void Majo::ThrowAppleCreate(int rXPx, int rYPx, int muki)
{
	ThrowApple* newapple = new ThrowApple(rXPx, rYPx, muki);
	newapple->AddTarget(GAMECONTROL->GetJiki());
	newapple->DisableCollision();

	GAMECONTROL->GetMobManager()->Request(newapple, true);
	mThrowMe = newapple;

	// SE
	GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_boss1_atack.wav");
}

/*
	りんごを落とす
*/
void Majo::AppleOtosu()
{
	RollingAppleCreate(sRingoX[mEntPt], sRingoY[mEntPt], mEntPt+1);

	mDropMe->Fall();
	mDropMe->EnableCollision();
}

/*
	りんごを投げる
*/
void Majo::AppleThrow()
{
	ThrowAppleCreate(sRingoX[mEntPt], sRingoY[mEntPt], 4 - mEntPt);

	mThrowMe->Throw();
	mThrowMe->EnableCollision();
}

/*
	小人がいなければリクエストする
*/
void Majo::KobitoCreate()
{
	if( !mKobitoOut )
	{
		mKobitoOut = true;
		LightKobito* mKobito;

		int choice = rand()%3;
		switch(choice){
			case 0: mKobito = new LightKobitoBlue(this);  break;
			case 1: mKobito = new LightKobitoRed(this);   break;
			case 2: mKobito = new LightKobitoGreen(this); break;
		}

		mKobito->AddTarget(this);

		GAMECONTROL->GetMobManager()->Request(mKobito, true);
	}
}

/*
	動作終了
*/
void Majo::DousaEnd()
{
	if( !mActive ) return;

	switch( mStatus ){
		case WIN:
			{
				// りんごを落とす
				AppleOtosu();
				mStatus = WINBACK;

				break;
			}

		case WINBACK: 
			{
				SelectEntPoint();
				break;
			}

		case WINDAMAGE:
			{
				if( mHp <= 0 ) Die();
				else mStatus = WINBACK;

				break;
			}

		case DOORTHROW:
			{
				mStatus = DOORTHROWEND;
				AppleThrow();
				break;
			}

		case DOORTHROWEND:
			{
				mStatus = DOOREXIT;
				mMuki = !mMuki;
				mSpX = (mMuki?1:-1) * MAJO_ARUKI_SPX;
				break;
			}

		case DOORDAMAGE:
			{
				if( mHp <= 0 ) Die();
				else {
					mStatus = mSaveStatus;
					mSpX = mSaveSpX;
				}
				break;
			}
	}

	SetAnim(mStatus);
}

/*
	自機との当たり判定
*/
void Majo::CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId)
{
	if( mStatus == DIYING ) return;

	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	if(jiki){ //当たり！
		if( rOpGroupId == SP->GRID_KOUGEKI && rThisGroupId == SP->GRID_BOGYO ){
			InflictDamage();
			}
	}
}


/*
	ライト小人が死亡したときのコールバック
*/
void Majo::KobitoDied()
{
	mKobitoOut = false;
}

/*
	ダメージを与える
*/
void Majo::InflictDamage()
{
	if( dmgFlag ) return;

	if( mStatus == WIN || mStatus == WINBACK ){
		mStatus = WINDAMAGE;
		if( mStatus == WIN) AppleOtosu();
		mHp--;
		dmgFlag = true;

		// SE
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_kougekimeityuu.wav");
	}
	else if( mStatus == DOOR || mStatus == DOOREXIT || mStatus == DOORTHROW || mStatus == DOORTHROWEND ){
		mSaveStatus = mStatus;
		mStatus = DOORDAMAGE;
		mSaveSpX = mSpX;
		mSpX = 0;
		mHp--;
		dmgFlag = true;

		SetAnim(mStatus);
		// SE
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_kougekimeityuu.wav");

	}

	GAMECONTROL->GetJiki()->IncreaseTensEmpa();
	GAMECONTROL->GetJiki()->IncrementChain();
}

/*
	死ぬ
*/
void Majo::Die()
{
	mSpX = sDieSpX[mEntPt];
	mSpY = -SHINIPATT_SHOSP;
	mAccY = SP->GRAVITY;

	if( mStatus != DIYING ){
		if( mStatus == WINDAMAGE ){
			mSizeX = GI("MAJO_DOORSX");
			mSizeY = GI("MAJO_DOORSY");
			SetAnim(mStatus);
		}
		mStatus = DIYING;

		// りんごを消去させる
		GAMECONTROL->GetMobManager()->RemoveAll<ThrowApple>();
		GAMECONTROL->GetMobManager()->RemoveAll<RollingApple>();

		// ヒロインを止める
		GAMECONTROL->GetJiki()->SetSuperPause();

		//SE
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_teki_down.wav");

	}
}

/*
	動きをオンにする
*/
void Majo::Activate()
{
	mActive = true;
	SelectEntPoint();
}
