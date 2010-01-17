#pragma once

#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASQueenBase.h"
#include "..\\..\\..\\..\\Units\\MutekiJikan.h"
#include "..\\FriendObjects\\Kagami.h"

#include "..\\..\\BossShareActions\\ASFadeOutAndStageClear.h"
#include "..\\..\\BossShareActions\\ASWaitForMaku.h"

//! 女王のﾀﾞﾒｰｼﾞ
/****************************************************************//**
*	行っている動作を一時停止し、ﾀﾞﾒｰｼﾞを食らいます。
*
*	\nosubgrouping
********************************************************************/
class ASQueenDamage: public ASQueenBase
{

public:

	//! ｺﾝｽﾄﾗｸﾀ
	ASQueenDamage(ASQueenBase* rCurAction) : mCurAction(rCurAction){}

	//! @see ActionState
	void BuildAnimation(ActionState* rPrevState)
	{
		mAnimation = Animation::ParseFromFile( "data\\animdata\\queen\\Damage.txt" );
	}
	
	//! @see ActionState
	void OnEnter()
	{
		// HPを削る
		mHp--;

		// ヒロインにいいことをプレゼントする
		GAMECONTROL->GetJiki()->IncreaseTensEmpa();
		GAMECONTROL->GetJiki()->IncrementChain();

		// 死亡の場合
		if( mHp <= 0 ) {
			// 死ぬ
			mKagami->SetHibiStage(3);
			GAMECONTROL->GetJiki()->SetSuperPause();
			GAMECONTROL->GetJiki()->DisableCollision();
			GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();

			GAMECONTROL->GetMobManager()->RemoveAll<TrumpSoldier>();
			GAMECONTROL->GetMobManager()->RemoveAll<Thorn>();

			mParent->RemoveAllActions(this);
			mParent->BreakInActionNoResume( new ASFadeOutAndStageClear() );
			
			// 幕を閉じる
			GAMECONTROL->GetMaku()->Close();
			mParent->QueueAction( new ASWaitForMaku(true) );

			// ﾌｪｰﾄﾞｱｳﾄ
			mParent->QueueAction( new ASFadeOutAndStageClear() );
			
		}

		// ﾀﾞﾒｰｼﾞを食らうだけの場合
		else{
			// 痛む
			mMutekiJikan->Start();
			mKagami->StartVibrate();

			// 鏡が壊れる
			if( mHp <7 ) mKagami->SetHibiStage(1);
			if( mHp <4 ) mKagami->SetHibiStage(2);
		}
	}

	//! @see ActionState
	bool Update()
	{
		mCurAction->Update();
		return mAnimation->GetLoopCount() >= 1;
	}


protected:
	ASQueenBase* mCurAction;
};



			