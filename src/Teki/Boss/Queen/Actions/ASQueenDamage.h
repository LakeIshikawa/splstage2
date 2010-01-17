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

//! ��������Ұ��
/****************************************************************//**
*	�s���Ă��铮����ꎞ��~���A��Ұ�ނ�H�炢�܂��B
*
*	\nosubgrouping
********************************************************************/
class ASQueenDamage: public ASQueenBase
{

public:

	//! �ݽ�׸�
	ASQueenDamage(ASQueenBase* rCurAction) : mCurAction(rCurAction){}

	//! @see ActionState
	void BuildAnimation(ActionState* rPrevState)
	{
		mAnimation = Animation::ParseFromFile( "data\\animdata\\queen\\Damage.txt" );
	}
	
	//! @see ActionState
	void OnEnter()
	{
		// HP�����
		mHp--;

		// �q���C���ɂ������Ƃ��v���[���g����
		GAMECONTROL->GetJiki()->IncreaseTensEmpa();
		GAMECONTROL->GetJiki()->IncrementChain();

		// ���S�̏ꍇ
		if( mHp <= 0 ) {
			// ����
			mKagami->SetHibiStage(3);
			GAMECONTROL->GetJiki()->SetSuperPause();
			GAMECONTROL->GetJiki()->DisableCollision();
			GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();

			GAMECONTROL->GetMobManager()->RemoveAll<TrumpSoldier>();
			GAMECONTROL->GetMobManager()->RemoveAll<Thorn>();

			mParent->RemoveAllActions(this);
			mParent->BreakInActionNoResume( new ASFadeOutAndStageClear() );
			
			// �������
			GAMECONTROL->GetMaku()->Close();
			mParent->QueueAction( new ASWaitForMaku(true) );

			// ̪��ޱ��
			mParent->QueueAction( new ASFadeOutAndStageClear() );
			
		}

		// ��Ұ�ނ�H�炤�����̏ꍇ
		else{
			// �ɂ�
			mMutekiJikan->Start();
			mKagami->StartVibrate();

			// ��������
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



			