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
#include "ASQueenJumpingDeath.h"


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

		// 痛む
		mMutekiJikan->Start();
		mKagami->StartVibrate();

		// 鏡が壊れる
		if( mHp <7 ) mKagami->SetHibiStage(1);
		if( mHp <4 ) mKagami->SetHibiStage(2);

		// SE
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_boss3_kagami1.wav");
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_kougekimeityuu.wav");

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



			