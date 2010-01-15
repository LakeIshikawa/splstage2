#include "LightKobitoRed.h"

LightKobitoRed::LightKobitoRed()
{
	Init();
}

LightKobitoRed::LightKobitoRed( Majo* rParent ) : LightKobito( rParent )
{
	Init();
}

void LightKobitoRed::Init()
{
	mSpX = - GF("LKOBITO_REDSPX");
}


LightKobitoRed::~LightKobitoRed()
{}

/* ±ÆÒ°¼®ÝÃÞ°À */
int LightKobitoRed::sAniData[][MAX_DATA] =
{
	{ 0, 1, 2, 1, 0, 3, 4, 3, 99 },					// WALK
	{ 0, 1, 2, 1, 0, 3, 4, 3, 99 },					// FALL

};

float LightKobitoRed::sAniTimeData[][MAX_DATA] =
{
	{ 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f },	// WALK
	{ 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f },	// FALL

};

/* ¸Þ×Ì¨¯¸ÃÞ°À */
char LightKobitoRed::sGraphicData[][MAX_NLEN] = 
{
	"graphics\\teki\\npc_betsu_dwarfb.png",			// WALK
	"graphics\\teki\\npc_betsu_dwarfb.png",			// FALL

};

void LightKobitoRed::_Move()
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
	ƒ‰ƒCƒg‰ž“š
*/
void LightKobitoRed::ResponseAka()
{
	Fall();
}
