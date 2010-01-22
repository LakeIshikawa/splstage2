#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "OokamiHouseBrick.h"
#include "..\\..\\..\\Management\\GameControl.h"

/************************************************************//**
*	“–‚½‚è”»’è‚ðÝ’è‚·‚é
****************************************************************/
OokamiHouseBrick::OokamiHouseBrick() 
{
	AddFrame(0);
	AddRect(0, SP->GRID_BOGYO, 8,-168,128,0);

	AddTarget(GAMECONTROL->GetJiki());
}

/************************************************************//**
*	Á–Å‚·‚é
****************************************************************/
void OokamiHouseBrick::Disappear() 
{
	if( mAppearedHeight > 0){
		mAppearedHeight -= OOKAMI_HSSP;
	}
	else GAMECONTROL->GetMobManager()->Remove(this);
}

/************************************************************//**
*	“–‚½‚è”»’è‰ž“š
****************************************************************/
void OokamiHouseBrick::CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId)
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	if(jiki && rOpGroupId==SP->GRID_HOUSE){
		jiki->SetHouseProtected();
	}
}
