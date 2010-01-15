#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASQueenBase.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"

//! 攻撃の呼び動作
/****************************************************************//**
*	鏡が虹のようになり、色で次の攻撃を知らせる
*
*	\nosubgrouping
********************************************************************/
template<class T> class ASQueenAttackInit: public ASQueenBase
{

public:

	//! @see ActionState
	void OnEnter() 
	{
		mKagami->StartShuffle();
		mTimer = 0;
		mStatus = 0;

		KAGAMI_SHFTIME = GF("KAGAMI_SHFTIME");
		KAGAMI_STILLTIME = GF("KAGAMI_STILLTIME");
	}

	//! @see ActionState
	bool Update()
	{
		// 威力切り替えの場合は、やめる
		if( (mHp<7 && mPowerStage==0) || (mHp<4 && mPowerStage<=1) )
		{
			// 鏡の色を戻す
			mKagami->SetToColor(Kagami::Color(1.0f, 1.0f, 1.0f));
			return true;
		}

		// 挙動
		switch(mStatus){

			// ｼｬｯﾌﾙ
			case 0:
				{
					if( mKagami->GetShuffleLoops() > 0 ){
						mKagami->SetToColor(T::GetColor());
						mKagami->StopShuffle();
						mStatus = 1;
					}
					break;
				}

			// 固定の色
			case 1:
				{
					WAIT_TIMER(mTimer, KAGAMI_STILLTIME)
						return true;
					WAIT_END
					break;
				}
		}

		return false;
	}

	//! @see ActionState
	void OnExit()
	{
		mParent->AddNextAction( new T() );
		ASQueenBase::OnExit();
	}

private:
	bool mStatus;
	float mTimer;
	float KAGAMI_SHFTIME;
	float KAGAMI_STILLTIME;
};
