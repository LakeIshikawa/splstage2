#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Thorn.h"
#include "..\\..\\..\\TrumpSoldier.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\..\\Jiki\\Jiki.h"

/************************************************************//**
*@Ý’è’è”‚ð“Ç‚Ýž‚Þ
****************************************************************/
Thorn::Thorn(int rX, int rY, float rSp)
{
	// ˆÊ’u
	mSizeX = GI("THORNSX");
	mSizeY = GI("THORNSY");

	mX = rX;
	mY = rY;

	mSpeed = rSp;

	// “–‚½‚è”»’è
	AddFrame(0);
	AddIndexedRect(0, SP->GRID_KOUGEKI, 0, 0, 0, mSizeX, mSizeY);
	AddTarget(GAMECONTROL->GetJiki());

	// Ž©•ª‚ðƒgƒ‰ƒ“ƒv•º‚ÌÀ°¹Þ¯Ä‚É“o˜^
	GAMECONTROL->GetMobManager()->AddAsTargetToAllOf<TrumpSoldier>(this);

	// ‰Šú‰»
	mHeight = 0;
	
	// SE
	GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_boss3_toge.wav");


}

/************************************************************//**
*	1ÌÚ°Ñˆ—
****************************************************************/
void Thorn::Move()
{
	mHeight += mSpeed;
	
	// ’¸“_
	if( mHeight >= mSizeY ){
		mHeight = mSizeY;
		mSpeed *= -1;
	}
	if( mHeight <=0 && mSpeed <0 ){
		GAMECONTROL->GetMobManager()->Remove(this);
	}

	// “–‚½‚è”»’è‚ð’¼‚·
	((Rect*)(pCollision->GetCurFrame()->GetIndexedShape(0)))->SetTop(-mHeight);
	((Rect*)(pCollision->GetCurFrame()->GetIndexedShape(0)))->SetBottom(0);

	Draw();
}

/************************************************************//**
*	•`‰æ
****************************************************************/
void Thorn::Draw()
{
	DX_DRAW("graphics\\teki\\queen\\boss4_thorn.png", 
		mX, mY-mHeight, 0, 0, mSizeX, mHeight);
}

/************************************************************//**
*	“–‚½‚è”»’è‚Ì‰ž“š
****************************************************************/
void Thorn::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	// ËÛ²Ý
	if( jiki && rOpGroupId == SP->GRID_BOGYO  || rOpGroupId == SP->GRID_KOUGEKI ){
		jiki->InflictDamage();
	}
}

