#include "LightKobitoGreen.h"

LightKobitoGreen::LightKobitoGreen()
{
	Init();
}

LightKobitoGreen::LightKobitoGreen( Majo* rParent ) : LightKobito( rParent )
{
	Init();
}

void LightKobitoGreen::Init()
{
	mSpX = - GF("LKOBITO_BLUESPX");
}

/* ｱﾆﾒｰｼｮﾝﾃﾞｰﾀ */
int LightKobitoGreen::sAniData[][MAX_DATA] =
{
	{ 0, 1, 2, 1, 0, 3, 4, 3, 99 },					// WALK
	{ 0, 1, 2, 1, 0, 3, 4, 3, 99 },					// FALL

};

float LightKobitoGreen::sAniTimeData[][MAX_DATA] =
{
	{ 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f },	// WALK
	{ 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f },	// FALL

};

/* ｸﾞﾗﾌｨｯｸﾃﾞｰﾀ */
char LightKobitoGreen::sGraphicData[][MAX_NLEN] = 
{
	"graphics\\object\\mkobito_walk_c.png",				// WALK
	"graphics\\object\\mkobito_walk_c.png",				// FALL

};

void LightKobitoGreen::_Move()
{
	LightKobito::_Move();

	SetAnim( mStatus );

	mSpX += mAccX;
	mSpY += mAccY;
	mX += mSpX;
	mY += mSpY;

	Teki::Draw();
}

/*
	ライト応答
*/
void LightKobitoGreen::ResponseMidori()
{
	Fall();
}
