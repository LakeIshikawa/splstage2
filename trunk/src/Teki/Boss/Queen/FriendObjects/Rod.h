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
class Rod : public Collidable
{

public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	Rod(float rStartAngle, bool rDir);

	//! @see Movable
	void Move();
	//! 描画
	void Draw();
	
	//! あたり判定応答
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId,
		int rOpGroupId);

	//! 特別・ﾋﾛｲﾝとの当たり判定(四角で回転している、唯一なものとしての特別な扱い)
	bool CollidesWithHeroine();

	//! 終了か
	bool HasFinished();

private:
	float mStartAngle;
	float mAngle;
	float mAlpha;
	int mHeartShot;
	bool mDir;

	enum STATUS {
		APPEAR,
		ROTATE,
		DISAPPEAR,
		INACTIVE
	} mStatus;


	// 設定定数
	float RODSPANG;
	float STD_FADEIN_SP;
};
