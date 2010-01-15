#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASQueenBase.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"

//! �U���̌Ăѓ���
/****************************************************************//**
*	�������̂悤�ɂȂ�A�F�Ŏ��̍U����m�点��
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
		// �З͐؂�ւ��̏ꍇ�́A��߂�
		if( (mHp<7 && mPowerStage==0) || (mHp<4 && mPowerStage<=1) )
		{
			// ���̐F��߂�
			mKagami->SetToColor(Kagami::Color(1.0f, 1.0f, 1.0f));
			return true;
		}

		// ����
		switch(mStatus){

			// �����
			case 0:
				{
					if( mKagami->GetShuffleLoops() > 0 ){
						mKagami->SetToColor(T::GetColor());
						mKagami->StopShuffle();
						mStatus = 1;
					}
					break;
				}

			// �Œ�̐F
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
