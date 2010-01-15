#pragma once
#include "CollShape.h"

class Circle :
	public CollShape
{
public:
	Circle(Collision* rParent, int rGroupId, int rX, int rY, int rHankei);
	~Circle(void);

	bool Collides(CollShape* rOperand);

	//±¸¾½
	int X();
	int Y();
	int Hankei();

	void Set(int rX, int rY, int rHankei) { mX=rX; mY=rY; mHankei=rHankei; }

private:
	int mX;
	int mY;
	int mHankei;

	static bool CircleCircle(Circle* rCircle1, Circle* rCircle2, 
		int rC1PosX, int rC1PosY, bool rC1Muki, int rC1SizeX,
		int rC2PosX, int rC2PosY, bool rC2Muki, int rC2SizeX);
};
