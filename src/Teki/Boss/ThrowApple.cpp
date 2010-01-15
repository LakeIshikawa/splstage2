#include "ThrowApple.h"
#include "..\\..\\Management\\GameControl.h"

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
	メイン処理
*/
void ThrowApple::Move()
{
	Rebound();
	Kaiten();
	Apple::Move();
}

/*
	弾む
*/
void ThrowApple::Rebound()
{
	if( IsHittingGround() ){
		if( mRebounds == 0){ // 最初の跳ね返り。　回転する
			RollIfHitGround();
		}
			Fall();
			mRebounds++;
			mSpY = -sqrt( 2 * SP->GRAVITY * (APPLE_THROW_HG)) / (mRebounds +1);
	}
}

/*
	投げる
*/
void ThrowApple::Throw()
{
	mSpX = (mMuki?1:-1) * APPLE_THROW_SPX;
	mSpY = -sqrt( 2 * SP->GRAVITY * (APPLE_THROW_HG));
	Fall();
}