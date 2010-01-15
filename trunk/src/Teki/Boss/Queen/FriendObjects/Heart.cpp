#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Heart.h"
#include "..\\..\\..\\TrumpSoldier.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\..\\Jiki\\Jiki.h"

/************************************************************//**
*@Ý’è’è”‚ð“Ç‚Ýž‚Þ
****************************************************************/
Heart::Heart(int rX, int rY, float rAngle) : mAngle( rAngle )
{
	HEARTSP = GF("HEARTSP");

	// ˆÊ’u
	mSizeX = GI("HEARTSX");
	mSizeY = GI("HEARTSY");

	mX = rX - mSizeX/2;
	mY = rY - mSizeY/2;
	mSpX = cos( rAngle - D3DX_PI/2 ) * HEARTSP;
	mSpY = sin( rAngle - D3DX_PI/2 ) * HEARTSP;
	
	// “–‚½‚è”»’è
	AddFrame(0);
	AddIndexedRect(0, SP->GRID_KOUGEKI, 0, 0, 0, mSizeX, mSizeY);
	AddTarget(GAMECONTROL->GetJiki());

	// ƒgƒ‰ƒ“ƒv•º
	GAMECONTROL->GetMobManager()->AddAsTargetToAllOf<TrumpSoldier>(this);

	// ‰Šú‰»
	
}

/************************************************************//**
*	1ÌÚ°Ñˆ—
****************************************************************/
void Heart::Move()
{
	DieIfGamenGai();
	Kaiten();

	// ˆÚ“®
	mX += mSpX;
	mY += mSpY;

	// •`‰æ
	Draw();
}
/************************************************************//**
*	‰ñ“]‚·‚é
****************************************************************/
void Heart::Kaiten()
{
	mAngle += GF("HEART_KAITENSP");
	if( mAngle >= D3DX_PI*2 ){
		mAngle = 0;
	}
}

/************************************************************//**
*	•`‰æ
****************************************************************/
void Heart::Draw()
{
	DX_SCROLL_ROT_DRAW("graphics\\teki\\queen\\boss4_heart.png", 
		mX, mY, 0, 0, mSizeX, mSizeY, mAngle);
}

/************************************************************//**
*	“–‚½‚è”»’è‚Ì‰ž“š
****************************************************************/
void Heart::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	// ËÛ²Ý
	if( jiki && rOpGroupId == SP->GRID_BOGYO  || rOpGroupId == SP->GRID_KOUGEKI ){
		jiki->InflictDamage();
	}
}
