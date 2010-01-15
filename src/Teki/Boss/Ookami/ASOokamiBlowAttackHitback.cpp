#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASOokamiBlowAttackHitback.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Animation\\Animation.h"


/************************************************************//**
*	家を壊す
****************************************************************/
void ASOokamiBlowAttackHitback::OnEnter() 
{
	mSpX = GF("OOKAMI_BKHTSPX") * mMuki?-1:1;
	mSpY = -GF("OOKAMI_BKHTSPY");
}


/************************************************************//**
*	画面に入って終わり
****************************************************************/
bool ASOokamiBlowAttackHitback::Update() {
	
	//ﾋｯﾄﾊﾞｯｸ
	mSpY += SP->GRAVITY;
	mY += mSpY;
	mX += mSpX;

	// 着地
	if( mY >= OOKAMI_STARTY ){
		mY = OOKAMI_STARTY;
		mSpY = 0;
		mSpX = 0;
	}

	// 終了条件
	return mAnimation->GetLoopCount() == 15;
}

/************************************************************//**
*	次のｽﾃｰﾄに移る
****************************************************************/
void ASOokamiBlowAttackHitback::OnExit() 
{
}
