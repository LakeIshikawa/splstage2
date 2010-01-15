#include "LightKobitoBlue.h"

LightKobitoBlue::LightKobitoBlue()
{
	Init();
}

LightKobitoBlue::LightKobitoBlue( Majo* rParent ) : LightKobito( rParent )
{
	Init();
}

void LightKobitoBlue::Init()
{
	mSpX = - GF("LKOBITO_BLUESPX");
}


LightKobitoBlue::~LightKobitoBlue()
{}

/* ��Ұ����ް� */
int LightKobitoBlue::sAniData[][MAX_DATA] =
{
	{ 0, 1, 2, 1, 0, 3, 4, 3, 99 },					// WALK
	{ 0, 1, 2, 1, 0, 3, 4, 3, 99 },					// FALL

};

float LightKobitoBlue::sAniTimeData[][MAX_DATA] =
{
	{ 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f },	// WALK
	{ 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f, 0.2f },	// FALL

};

/* ���̨���ް� */
char LightKobitoBlue::sGraphicData[][MAX_NLEN] = 
{
	"graphics\\teki\\npc_betsu_dwarfa.png",				// WALK
	"graphics\\teki\\npc_betsu_dwarfa.png",				// FALL

};

void LightKobitoBlue::_Move()
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
	���C�g����
*/
void LightKobitoBlue::ResponseAo()
{
	Fall();
}
