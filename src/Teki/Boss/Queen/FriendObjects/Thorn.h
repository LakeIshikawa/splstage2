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
class Thorn : public Collidable
{

public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	Thorn(int rX, int rY, float rSp);

	//! @see Movable
	void Move();
	//! 描画
	void Draw();
	
	//! あたり判定応答
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId,
		int rOpGroupId);

	//! ｾｯﾄ
	void SetPos(int rX, int rY);

	//! 発射！
	void Pull();

	//! ｸｴﾘｰ
	float GetHeight() { return mHeight; }

private:
	enum {
		STANDBY,
		ACTION
	} mStatus;

	float mHeight;
	float mSpeed;
};
