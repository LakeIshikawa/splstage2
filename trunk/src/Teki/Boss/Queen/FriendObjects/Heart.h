#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\..\\Mob\\Collidable.h"

//! 鏡
/****************************************************************//**
*	虹みたいになるよー
*	\nosubgrouping
********************************************************************/
class Heart : public Collidable
{

public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	Heart(int rX, int rY, float rAngle);

	//! @see Movable
	void Move();
	//! 描画
	void Draw();
	
	//! あたり判定応答
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId,
		int rOpGroupId);

	// 回転する
	void Kaiten();

private:
	float mAngle;
	
	// 設定定数
	float HEARTSP;
};
