#pragma once
#include "CollShape.h"
#include "Circle.h"

class Square :
	public CollShape
{
public:
	Square(Collision* rParent, int rGroupId);
	~Square(void);

	bool Collides(CollShape* rOperand, int rPosX, int rPoxY, int rPosOpX, int PosOpY);

private:
	bool SquareSquareColl(Square* rSquare1, Square* rSquare2);
	bool SquareCircleColl(Square* rSquare, Circle* eCircle);

};
