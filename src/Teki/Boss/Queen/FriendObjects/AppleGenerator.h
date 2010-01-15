#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\..\\Mob\\Collidable.h"

//! 定期的に林檎を出す
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class AppleGenerator: public Collidable
{

public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	AppleGenerator(int rX, int rY);

	//! @see ActionThread
	void Move();
	//! 描画
	void Draw();

	//! ﾘﾝｺﾞを消し停止する
	void StopAndClear();

	//! 威力の設定 ( 0-短時間出現 1-長時間出現 )
	void SetStage(int rSt);

	//! あたり判定応答
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId,
		int rOpGroupId);

private:
	float mTimer;
	float mAlpha;
	int mStage;
	int mFlashNum;
	bool mFlashFl;

	enum STATUS {
		APPEAR,
		ACTIVE,
		DISAPPEAR,
		INACTIVE
	} mStatus;

	// 設定定数
	float APPLE_BEFOREAPP;
	float APPLE_BEFOREDISAPP1;
	float APPLE_BEFOREDISAPP2;

	float STD_FADEIN_SP;
};

