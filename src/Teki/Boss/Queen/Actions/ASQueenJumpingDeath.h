#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once
#include "..\\..\\BossShareActions\\ASJumpingDeath.h"
#include "ASQueenBase.h"


//! �������̊�{�����
/****************************************************************//**
*	�����ɂƂ��ĕW���̏������������B
*
*	\nosubgrouping
********************************************************************/
class ASQueenJumpingDeath: virtual public ASJumpingDeath, virtual public ASQueenBase
{

public:

	//! @se ActionState
	void BuildAnimation(ActionState* rPrevState){
		mAnimation = Animation::ParseFromFile( "data\\animdata\\queen\\Death.txt" );
	}

	//! @see ActionState
	void OnEnter(){
		ASJumpingDeath::OnEnter();

		// ���𗎂Ƃ�
		mKagami->JumpingDie();

		//SE
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_boss3_kagami2.wav");
	}

	//! @see ActionState
	void OnExit(){
		ASJumpingDeath::OnExit();
	}

	//! �W���̓����蔻�艞��
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId){}

};

