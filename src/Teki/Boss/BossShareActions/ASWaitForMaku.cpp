#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASWaitForMaku.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionState.h"
#include "..\\..\\..\\Mob\\MobDrawer\\SimpleDrawer.h"
#include "..\\..\\..\\Jiki\\Jiki.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Animation\\Animation.h"

/************************************************************//**
*	“–‚½‚è”»’è‚È‚µ
****************************************************************/
void ASWaitForMaku::BuildCollision(ActionState* rPrevState) 
{
	mCollision = NULL;
}

/************************************************************//**
*	Ï¯Ìß‚ ‚½‚è”»’è‚È‚µ
****************************************************************/
void ASWaitForMaku::BuildMapCollider(ActionState* rPrevState) 
{
	mMapCollider = NULL; // Ï¯Ìß‚ ‚½‚è”»’è‚È‚µ
}

/************************************************************//**
*	±ÆÒ°¼®Ý‚ðŒp³
****************************************************************/
void ASWaitForMaku::BuildAnimation(ActionState* rPrevState) 
{
	// ‰Šú½Ã°Ä‚Ìê‡
	if( !rPrevState ){
		mAnimation = NULL;
	}

	// ‚»‚êˆÈŠO‚Ìê‡
	else{
		mAnimation = rPrevState->GetAnimation()->Clone();
	}
}

/************************************************************//**
*	•`‰æ•û–@‚ðºËß°‚·‚é
****************************************************************/
void ASWaitForMaku::BuildMobDrawer(ActionState* rPrevState) 
{
	// ‰Šú½Ã°Ä‚Ìê‡
	if( !rPrevState ){
		mMobDrawer = NULL;
	}

	// ‚»‚êˆÈŠO‚Ìê‡
	else {
		mMobDrawer = rPrevState->GetMobDrawer()->Clone();
		((SimpleDrawer*)mMobDrawer)->SetAnimation(mAnimation);
	}
}

/************************************************************//**
*	‘¼î•ñ‚ÌËÞÙÄÞ‚È‚µ
****************************************************************/
void ASWaitForMaku::BuildOtherInfo(ActionState* rPrevState) 
{}

/************************************************************//**
*	“–‚½‚è”»’è‚Ì‰ž“š‚È‚µ
****************************************************************/
void ASWaitForMaku::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{}

/************************************************************//**
*	
****************************************************************/
void ASWaitForMaku::OnEnter() 
{
	
}

/************************************************************//**
*	–‹‚ªã‚ª‚Á‚Ä‚¢‚é‚Ì‚ð‘Ò‚Â
****************************************************************/
bool ASWaitForMaku::Update() {
	if( mOpenClose )
		return GAMECONTROL->GetMaku()->IsClosed();
	else
		return GAMECONTROL->GetMaku()->IsOpen();
}

/************************************************************//**
*	
****************************************************************/
void ASWaitForMaku::OnExit() {
	
}
