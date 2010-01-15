#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once
#include "..\\..\\..\\Mob\\ActionControllable\\ActionState.h"


//! 狼の基本ｱｸｼｮﾝ
/****************************************************************//**
*	ｼﾞｬﾝﾌﾟ(ﾋｯﾄﾊﾞｯｸっぽいやつ)して画面の下から抜ける
*
*	\nosubgrouping
********************************************************************/
class ASJumpingDeath: virtual public ActionState
{

public:
	
	virtual ~ASJumpingDeath() {}

	//! @see ActionState
	void OnEnter();
	//! @see ActionState
	bool Update();
	//! @see ActionState
	void OnExit();

	//! 標準の当たり判定応答
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId){}


};

