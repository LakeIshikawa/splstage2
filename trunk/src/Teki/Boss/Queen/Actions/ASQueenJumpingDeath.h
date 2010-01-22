#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once
#include "..\\..\\BossShareActions\\ASJumpingDeath.h"
#include "ASQueenBase.h"


//! 女王おの基本ｱｸｼｮﾝ
/****************************************************************//**
*	女王にとって標準の情報やを準備する。
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

		// 鏡を落とす
		mKagami->JumpingDie();

		//SE
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_boss3_kagami2.wav");
	}

	//! @see ActionState
	void OnExit(){
		ASJumpingDeath::OnExit();
	}

	//! 標準の当たり判定応答
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId){}

};

