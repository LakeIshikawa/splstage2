#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\Mob\\Collidable.h"
#include "..\\..\\..\\Mob\\MobDrawer\\SimpleDrawer.h"
#include "..\\..\\..\\Animation\\Animation.h"

//! 家の基本ｸﾗｽ
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class Storm: public Collidable
{

public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	Storm(bool rMuki);

	//! 1ﾌﾚｰﾑ処理
	void Move();

	//! 当たり判定応答
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId);

protected:
	
	Animation* mAnimation;
	SimpleDrawer* mDrawer;

	//設定定数
	float STORM_SP;

};

