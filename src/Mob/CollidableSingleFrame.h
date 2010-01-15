#include <exception>
using namespace std;

#pragma once

#include "Movable.h"
#include "ICollidable.h"
#include "..\\Collision\\Collision.h"
#include "..\\Collision\\CollisionDrawer.h"

class CollidableSingleFrame;

//! 当たり判定可能なMobの単フレーム版
/****************************************************************//**
*	継承するクラスがCollisionの単一フレームを指定します。
*	このクラスはActionControllable基本クラスのために作ってあります。
*	\see ActionControllable
*	\nosubgrouping
********************************************************************/
class CollidableSingleFrame: public Movable, public ICollidable
{
public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	CollidableSingleFrame();

	//! あたり判定の執行
	void RunTask();

	//! 当たり判定のターゲットを追加する
	void AddTarget(ICollidable* rTarget);

	//! 当たり判定のターゲットを解除する
	void RemoveTarget(ICollidable* rTarget);

	//! 判定のフレームを取得する方法
	virtual Collision* GetCurFrame() = 0;

	//! 当たり判定の応答
	virtual void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId) = 0;

	protected: 
		list<ICollidable*> mlTargets;
		CollisionDrawer* mDrawer;
};
