#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Chandelier.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\..\\Jiki\\Jiki.h"

/************************************************************//**
*Å@ê›íËíËêîÇì«Ç›çûÇﬁ
****************************************************************/
Chandelier::Chandelier()
{
	// à íu
	mSizeX = GI("CHANDSX");
	mSizeY = GI("CHANDSY");
	CHANDCHAINDX = GI("CHANDCHAINDX");
	CHANDCHAINDY = GI("CHANDCHAINDY");
	CHANDCHAINSX = GI("CHANDCHAINSX");
	CHANDCHAINSY = GI("CHANDCHAINSY");
	FLOORY = GI("FLOORY");

	SetStage(false);

	mX = GI("CHANDX");
	mY = GI("CHANDY");
	mZ = -0.01f;

	// ìñÇΩÇËîªíË
	AddFrame(0);
	AddIndexedRect(0, SP->GRID_BOUND, 0, 13, 34, 360, 42);
	AddFrame(1);
	AddIndexedRect(1, SP->GRID_BOUND, 0, 13, 34, 360, 42);
	AddRect(1, SP->GRID_KOUGEKI, 3, 84, 371, 108);
	AddTarget(GAMECONTROL->GetJiki());

	// èâä˙âª
	mStatus = STOP;
	mTimer = 0.0f;
}

/************************************************************//**
*	ê›íËíËêîÇê›íËÇ∑ÇÈ
*	\param rStrong à–óÕã≠Ç©
****************************************************************/
void Chandelier::SetStage(bool rStrong)
{
	if(rStrong){
		CHANDRAISESP = GF("CHANDRAISESP2");
		CHANDWTTIME = GF("CHANDWTTIME2");
		GRAVITY = SP->GRAVITY*5/4;
	}
	else{
		CHANDRAISESP = GF("CHANDRAISESP");
		CHANDWTTIME = GF("CHANDWTTIME");
		GRAVITY = SP->GRAVITY;
	}
}

/************************************************************//**
*	±∆“∞ºÆ›Ç∆ï`âÊÇçsÇ§
****************************************************************/
void Chandelier::Move()
{
	switch( mStatus )
	{
		case STOP: break;
		case FALL:	Fall(); break;
		case FLOOR: Floor(); break;
		case RAISE: Raise();break;
	}

	// à⁄ìÆ
	mSpY += mAccY;
	mY += mSpY;

	Ashiba::Move();
}

/************************************************************//**
*	ï`âÊ
****************************************************************/
void Chandelier::Draw()
{
	// çΩ
	DX_DRAW("graphics\\teki\\queen\\boss4_light_chain.png", 
		mX+CHANDCHAINDX, mY+CHANDCHAINDY, 0, 0, CHANDCHAINSX, CHANDCHAINSY);
	// ñ{ëÃ
	DX_DRAW("graphics\\teki\\queen\\boss4_light.png", 
		mX, mY, 0, 0, mSizeX, mSizeY);
}

/************************************************************//**
*	óéÇ∆Ç∑(àÍâÒåƒÇ—)
****************************************************************/
void Chandelier::Drop()
{
	mStatus = FALL;
	SetCurFrame(1);
}

/************************************************************//**
*		ñﬂÇ∑(àÍâÒåƒÇ—)
****************************************************************/
void Chandelier::PickUp()
{
	mAccY = 0;
	mSpY = -CHANDRAISESP;
	mStatus = RAISE;
}

/************************************************************//**
*	\return Ç±ÇÃµÃﬁºﬁ™∏ƒÇÃ∫Àﬂ∞
****************************************************************/
Chandelier* Chandelier::Clone()
{
	Chandelier* newobj = new Chandelier();
	newobj->mStatus = mStatus;
	
	return newobj;
}

/************************************************************//**
*	óéÇøÇÈ
****************************************************************/
void Chandelier::Fall()
{
	mAccY = SP->GRAVITY;

	// ínñ Ç…Ç‘Ç¬Ç©ÇÈ
	if( mY + mSizeY >= FLOORY ){
		// SE
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_boss3_syannderia.wav");
		mAccY = 0;
		mSpY = 0;
		mY = FLOORY - mSizeY;
		mStatus = FLOOR;
		SetCurFrame(0);
	}
}

/************************************************************//**
*	ñ∞ÇÈ
****************************************************************/
void Chandelier::Floor()
{
	WAIT_TIMER(mTimer, CHANDWTTIME)
		PickUp();
	WAIT_END
}

/************************************************************//**
*	ñﬂÇÈ
****************************************************************/
void Chandelier::Raise()
{
	if( mY <= GI("CHANDY") ){
		mSpY = 0;
		mY = GI("CHANDY");
		mStatus = STOP;
	}
}

/************************************************************//**
*	çUåÇÇ†ÇΩÇËîªíË
****************************************************************/
void Chandelier::CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId)
{
	// ë´èÍÇÃîªíË
	Ashiba::CollisionResponse(rCollObject, rThisGroupId, rOpGroupId);

	// çUåÇÇÃîªíË
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);
	if( jiki && rThisGroupId == SP->GRID_KOUGEKI && rOpGroupId == SP->GRID_BOGYO && mStatus == FALL ){
		jiki->InflictDamage();
	}
}

/************************************************************//**
*	\return í‚é~ÇÃèÛë‘Ç©
****************************************************************/
bool Chandelier::IsStopped()
{
	return mStatus == STOP;
}
