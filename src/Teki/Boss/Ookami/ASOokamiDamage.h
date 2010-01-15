#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASOokamiBase.h"

//! 狼のﾀﾞﾒｰｼﾞｽﾃｰﾄ
/****************************************************************//**
*	硬直して、一周りのｱﾆﾒｰｼｮﾝが終わった終了する
*	\nosubgrouping
********************************************************************/
class ASOokamiDamage: public ASOokamiBase
{

public:

	//! @see ActionState
	void BuildAnimation(ActionState* rPrevState);

	//! @see ActionState
	virtual void OnEnter();
	//! @see ActionState
	virtual bool Update();
	//! @see ActionState
	virtual void OnExit();

	//! 標準の当たり判定応答
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId){}
};
