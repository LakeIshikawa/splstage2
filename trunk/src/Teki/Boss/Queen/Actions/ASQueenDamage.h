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

		// �ɂ�
		mMutekiJikan->Start();
		mKagami->StartVibrate();

		// ��������
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



			