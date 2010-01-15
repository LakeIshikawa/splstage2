#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\..\\Mob\\Collidable.h"

//! トランプ兵
/****************************************************************//**
*	左右歩いて壁に反転する
*	\nosubgrouping
********************************************************************/
class TrumpSoldier : public Collidable
{

public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	TrumpSoldier(int rX, int rY, string rGraphic);

	//! @see Movable
	void Move();
	//! 描画
	void Draw();
	
	//! あたり判定応答
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId,
		int rOpGroupId);

private:

	string mGraphic;

	enum STATUS {
		WALK
	} mStatus;

	// 設定定数
	int FLOORY;
	int TRUMPTOPY;
};
