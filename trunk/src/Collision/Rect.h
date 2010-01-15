#pragma once
#include "CollShape.h"
#include "Circle.h"

class Rect :
	public CollShape
{
public:
	Rect(Collision* rParent, int rGroupIdm, int rLeft, int rTop, int rRight, int rBottom);
	~Rect(void);

	int Top()		{return mTop;}
	int Bottom()	{return mBottom;}
	int Right()		{return mRight;}
	int Left()		{return mLeft;}
	void SetTop(int top) { mTop = top; }
	void SetBottom(int bottom) { mBottom = bottom; }
	void SetRight(int right) { mRight = right; }
	void SetLeft(int left) { mLeft = left; }

	bool Collides(CollShape* rOperand);

	bool Contains(int rX, int rY, int rSlX, int rSlY);

	static bool RectCircle(Rect* rRect, Circle* eCircle,
		int rC1PosX, int rC1PosY, bool rC1Muki, int rC1SizeX,
		int rC2PosX, int rC2PosY, bool rC2Muki, int rC2SizeX);

private:
	//ïœêî
	int mTop;
	int mBottom;
	int mRight;
	int mLeft;


	//ä÷êî
	static bool RectRect(Rect* rRect1, Rect* rRect2,
		int rC1PosX, int rC1PosY, bool rC1Muki, int rC1SizeX,
		int rC2PosX, int rC2PosY, bool rC2Muki, int rC2SizeX);

	static float PointDistance(int x1, int y1, int x2, int y2);

};
