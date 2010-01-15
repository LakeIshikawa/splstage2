#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "ASJumpingDeath.h"
#include "ASWaitForMaku.h"
#include "ASFadeOutAndStageClear.h"
#include "..\\..\\..\\Light\\Light.h"

/************************************************************//**
*	
****************************************************************/
void ASJumpingDeath::OnEnter() 
{
	// ｼﾞｬﾝﾌﾟ
	mSpX = GF("SHINIPATT_SPX");
	mAccX = 0;
	mSpY = -GF("SHINIPATT_SHOSP");
	mAccY = SP->GRAVITY;

	// ﾋﾛｲﾝとﾗｲﾄをとめる
	GAMECONTROL->GetJiki()->SetSuperPause();
	GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();

	// ｱｸｼｮﾝﾘｽﾄ
	mParent->RemoveAllActions(this);
}


/************************************************************//**
*	画面に入って終わり
****************************************************************/
bool ASJumpingDeath::Update() 
{

	mSpY += mAccY;
	mX += mSpX;
	mY += mSpY;

	// 終了条件
	return mY > SP->SCRSZY*2;
}

/************************************************************//**
*	次のｽﾃｰﾄに移る
****************************************************************/
void ASJumpingDeath::OnExit() 
{
	// 幕を閉じる
	GAMECONTROL->GetMaku()->Close();
	mParent->QueueAction( new ASWaitForMaku(true) );

	// ﾌｪｰﾄﾞｱｳﾄ
	mParent->QueueAction( new ASFadeOutAndStageClear() );

}
