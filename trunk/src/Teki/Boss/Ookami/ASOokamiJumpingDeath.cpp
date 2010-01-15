#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "ASOokamiJumpingDeath.h"

/************************************************************//**
*	ｱﾆﾒｰｼｮﾝ
****************************************************************/
void ASOokamiJumpingDeath::BuildAnimation(ActionState* rPrevState)
{
	mAnimation = Animation::ParseFromFile( "data\\animdata\\ookami\\Death.txt" );
}

/************************************************************//**
*	破片の作成と風を止める
****************************************************************/
void ASOokamiJumpingDeath::OnEnter() 
{
	// 風
	if( storm ) {
		GAMECONTROL->GetMobManager()->Remove(storm);
		storm = NULL;
	}

	// 家
	/*if( brick ) {
		brick->Destroy();
	}*/
	if( straw ) straw->StopParticles();
	if( rog ) straw->StopParticles();

	// 基本処理
	ASJumpingDeath::OnEnter();
}
