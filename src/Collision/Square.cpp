#include ".\square.h"

Square::Square(Collision* rParent, int rGroupId) : CollShape(rParent, rGroupId)
{
}

Square::~Square(void)
{
}

bool Square::Collides(CollShape* rOperand, int rPosX, int rPoxY, int rPosOpX, int PosOpY)
{
	return false;
}