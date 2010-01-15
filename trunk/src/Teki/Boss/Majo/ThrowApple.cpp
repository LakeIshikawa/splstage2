#include "ThrowApple.h"
#include "..\\..\\..\\Management\\GameControl.h"

ThrowApple::ThrowApple(int rXPx, int rYPx, int rMuki) : RollingApple( rXPx, rYPx, rMuki?1:3 )
{
	mMuki = rMuki;
	mRebounds = 0;

	APPLE_THROW_HG = GI("APPLE_THROW_HG");
	APPLE_THROW_SPX = GF("APPLE_THROW_SPX");
}

ThrowApple::~ThrowApple()
{}

/*
	ƒƒCƒ“ˆ—
*/
void ThrowApple::Move()
{
	Rebound();
	Kaiten();
	Apple::Move();
}

/*
	’e‚Þ
*/
void ThrowApple::Rebound()
{
	if( IsHittingGround() ){
		if( mRebounds == 0){ // Å‰‚Ì’µ‚Ë•Ô‚èB@‰ñ“]‚·‚é
			RollIfHitGround();
		}
			Fall();
			mRebounds++;
			mSpY = -sqrt( 2 * SP->GRAVITY * (APPLE_THROW_HG)) / (mRebounds +1);
	}
}

/*
	“Š‚°‚é
*/
void ThrowApple::Throw()
{
	mSpX = (mMuki?1:-1) * APPLE_THROW_SPX;
	mSpY = -sqrt( 2 * SP->GRAVITY * (APPLE_THROW_HG));
	Fall();
}