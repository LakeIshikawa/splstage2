#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once
#include "..\\BossShareActions\\ASJumpingDeath.h"
#include "ASOokamiBase.h"


//! 狼の基本ｱｸｼｮﾝ
/****************************************************************//**
*	狼にとって標準の情報やを準備する。
*
*	\nosubgrouping
********************************************************************/
class ASOokamiJumpingDeath: virtual public ASJumpingDeath, virtual public ASOokamiBase
{

public:

	//! @se ActionState
	void BuildAnimation(ActionState* rPrevState);

	//! @see ActionState
	void OnEnter();

	//! 標準の当たり判定応答
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId){}

};

