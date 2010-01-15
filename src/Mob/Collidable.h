#pragma once

#include "..\\Collision\\CollisionSet.h"
#include "..\\Collision\\CollisionDrawer.h"
#include "Movable.h"
#include "ICollidable.h"

/*
	当たり判定範囲を持つｴﾝﾃｨﾃｨ
*/
class Collidable : public virtual Movable, public ICollidable
{
public:
	Collidable(void);
	virtual ~Collidable(void);

	void RunTask();

	// 当たり判定
	void AddTarget(ICollidable* rTarget);
	void RemoveTarget(ICollidable* rTarget);

	//! 現フレームの取得
	Collision* GetCurFrame();

	//! 幅の取得
	int GetFrameSizeX() { return Movable::GetFrameSizeX(); }

	//! 縦幅の取得
	int GetFrameSizeY() { return Movable::GetFrameSizeY(); }

	//! X座標の取
	float GetX() { return Movable::GetX(); }

	//! Y座標を取得
	float GetY() { return Movable::GetY(); }

	//! 向きを取得
	bool GetMuki() { return Movable::GetMuki(); }

protected:
	//変数
	CollisionSet* pCollision;
	list<ICollidable*> mlTargets;
	CollisionDrawer* mDrawer;


	//関数
	void AddRect(int rFrameIdx, int rGroupId, int rLeft, int rTop, int rRight, int rBottom);
	void AddIndexedRect(int rFrameIdx, int rGroupId, int rShapeIdx, int rLeft, int rTop, int rRight, int rBottom);
	void AddCircle(int rFrameIdx, int rGroupId, int rX, int rY, int rHankei);
	void AddMovableCircle(int rFrameIdx, int rGroupId, int rShapeIdx, int rX, int rY, int rHankei);
	void SetCircle(int rFrameIdx, int rShapeIdx, int rX, int rY, int rHankei);

	void AddFrame(int rBango);
	void SetCurFrame(int rBango);
};
