#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASOokamiBlowAttackFaint.h"
#include "ASOokamiBlowAttackHitback.h"
#include "ASOokamiJumpingDeath.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Animation\\Animation.h"
#include "..\\..\\..\\Light\\Light.h"


/************************************************************//**
*	±ÆÒ°¼®İ‚ğì‚èo‚·
****************************************************************/
void ASOokamiBlowAttackFaint::BuildAnimation(ActionState* rPrevState) 
{
	mAnimation = Animation::ParseFromFile( "data\\animdata\\ookami\\BlowAttackFaint.txt" );
}

/************************************************************//**
*	˜T‚Ì•W€‚Ì“–‚½‚è”»’è‚Ì‰“š
****************************************************************/
void ASOokamiBlowAttackFaint::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	// ËÛ²İ
	if( jiki && !mMutekiJikan->IsMuteki() ){

		// ËÛ²İ‚ÌUŒ‚A˜T‚Ì–hŒä
		if( rOpGroupId == SP->GRID_KOUGEKI && rThisGroupId == SP->GRID_BOGYO ){
			// HP‚ğí‚é
			mHp--;

			// €–S‚Ìê‡
			if( mHp <= 0 ) {
				// €‚Ê
				mParent->BreakInActionNoResume( new ASOokamiJumpingDeath() );
			}
			// ÀŞÒ°¼Ş‚¾‚¯‚Ìê‡
			else{
				// ˜T‚ª’É‚Ş
				mParent->BreakInActionNoResume( new ASOokamiBlowAttackHitback() ); // TODO: OokamiDamage
			}
		}

		// ËÛ²İ‚Ì–hŒä
		else if( rOpGroupId == SP->GRID_BOGYO ){
			// ËÛ²İ‚ª’É‚Ş
			jiki->InflictDamage();
		}
	}
}

/************************************************************//**
*	‰æ–Ê‚É“ü‚Á‚ÄI‚í‚è
****************************************************************/
bool ASOokamiBlowAttackFaint::Update() {
	// I—¹ğŒ
	return mAnimation->GetLoopCount() == 6;
}

/************************************************************//**
*	Ÿ‚Ì½Ã°Ä‚ÉˆÚ‚é
****************************************************************/
void ASOokamiBlowAttackFaint::OnExit() 
{
	// ‚±‚±‚Å‰Æ‚ªŸ‚Ì‹­•—“®ì‚Å‚¿‚á‚ñ‚Æì‚è’¼‚³‚ê‚é‚æ‚¤A
	// ‚ÌÊİÄŞÙ‚ğŠJ•ú‚·‚é
	rog = NULL;
	straw = NULL;
	brick = NULL;
}
