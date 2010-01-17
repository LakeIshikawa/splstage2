#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "OokamiHouseBrick.h"
#include "..\\..\\..\\Management\\GameControl.h"

/************************************************************//**
*	当たり判定を設定する
****************************************************************/
OokamiHouseBrick::OokamiHouseBrick() 
{
	AddFrame(0);
	AddRect(0, SP->GRID_BOGYO, 8,-168,128,0);

	AddTarget(GAMECONTROL->GetJiki());

	mZ = 101.0f;
}

/************************************************************//**
*	消滅する
****************************************************************/
void OokamiHouseBrick::Disappear() 
{
	if( mAppearedHeight > 0){
		mAppearedHeight -= OOKAMI_HSSP;
	}
	else GAMECONTROL->GetMobManager()->Remove(this);
}

/************************************************************//**
*	当たり判定応答
****************************************************************/
void OokamiHouseBrick::CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId)
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	if(jiki && rOpGroupId==SP->GRID_HOUSE){
		jiki->SetHouseProtected();
	}
}
