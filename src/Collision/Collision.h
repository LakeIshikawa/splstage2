#pragma once

#include "CollShape.h"
#include <list>
#include <map>

using namespace std;

class ICollidable;
class IPositionable;

class Collision
{
	friend class CollisionDrawer;

public:
	/************************************************************//**
	*	\name ﾗｲﾌ循環
	****************************************************************/
	/*@{*/
	Collision(IPositionable* rParent);
	~Collision(void);
	/*@}*/
	
	bool Hantei(Collision* rOperand, ICollidable* rCallback, ICollidable* rCallbackOp);
	
	void AddShape(CollShape* rNewShape);
	void AddIndexedShape(CollShape* rNewShape, int rIdx);

	void AddRect(int rGroupId, int rLeft, int rTop, int rRight, int rBottom);
	void AddIndexedRect(int rGroupId, int rShapeIdx, int rLeft, int rTop, int rRight, int rBottom);
	void AddCircle(int rGroupId, int rX, int rY, int rHankei);
	void AddMovableCircle(int rGroupId, int rShapeIdx, int rX, int rY, int rHankei);
	void SetCircle(int rShapeIdx, int rX, int rY, int rHankei);

	CollShape* GetIndexedShape(int rIdx);
	IPositionable* GetParent();

	int LastThisGroupId() { return mThisGroupId; }
	int LastOperandGroupId() { return mOperandGroupId; }



private:
	//変数
	list<CollShape*> mlShapeLst;
	map<int, CollShape*> mmIdxToShape;

	IPositionable* mParent;

	int mThisGroupId;
	int mOperandGroupId;

	//関数
	bool Collides(CollShape* rShape, ICollidable* rCallback, ICollidable* rCallbackOp);
	
};
