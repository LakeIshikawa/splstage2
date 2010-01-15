#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASOokamiBlowAttackAspire.h"
#include "ASOokamiBlowAttackFaint.h"
#include "OokamiHouseStraw.h"
#include "OokamiHouseRog.h"
#include "OokamiHouseBrick.h"
#include "Storm.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Animation\\Animation.h"

/************************************************************//**
*	位置情報の作成
****************************************************************/
void ASOokamiBlowAttackAspire::BuildAnimation(ActionState* rPrevState)
{
	if( !mAnimation ){
		mAnimation = Animation::ParseFromFile( "data\\animdata\\ookami\\BlowAttackAspire.txt");
	}
}

/************************************************************//**
*	家を壊す
****************************************************************/
void ASOokamiBlowAttackAspire::OnEnter() 
{
	// 家を壊す
	if( !storm ){ //最初に呼ばれた一回のみ
		straw->Destroy();
		rog->Destroy();
	}

	// 息を出す(一回のみ)
	if( !storm ){
		storm = new Storm(mMuki);
		GAMECONTROL->GetMobManager()->Request(storm, true);
	}
}


/************************************************************//**
*	画面に入って終わり
****************************************************************/
bool ASOokamiBlowAttackAspire::Update() {
	// 終了条件
	return mAnimation->GetLoopCount() == 10;
}

/************************************************************//**
*	次のｽﾃｰﾄに移る
****************************************************************/
void ASOokamiBlowAttackAspire::OnExit() 
{
	// 次のｽﾃｯﾌﾟ
	mParent->AddNextAction(new ASOokamiBlowAttackFaint());
	
	// 息を止める
	GAMECONTROL->GetMobManager()->Remove(storm);
	storm = NULL;

	// ﾚﾝｶﾞの家を戻させる
	brick->Destroy();
}
