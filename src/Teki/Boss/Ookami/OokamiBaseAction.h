#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once
#include "..\\..\\..\\Mob\\ActionControllable\\ActionState.h"

class ICollidable;

//! 狼の基本ｱｸｼｮﾝ
/****************************************************************//**
*	狼にとって標準の情報やを準備する。
*
*	\nosubgrouping
********************************************************************/
class OokamiBaseAction: public ActionState
{

public:

	//! @see ActionState
	Collision* BuildCollision(ActionState* rPrevState);
	//! @see ActionState
	MapCollider* BuildMapCollider(ActionState* rPrevState);
	//! @see ActionState
	Animation* BuildAnimation(ActionState* rPrevState);

	//! 標準の当たり判定応答
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId);

	//! 標準の描画
	void Draw();

	//! @see ActionState
	virtual void OnEnter();

	//! @see ActionState
	virtual bool Update();

	//! @see ActionState
	virtual void OnExit();
};

