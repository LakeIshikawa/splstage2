#include ".\collshape.h"

/************************************************************//**
*	\param rParent この図形が所属する、親となるCollision
*	\param rGroupId	この図形を共する属性の整数\n
*					ｺｰﾙﾊﾞｯｸの時にこの整数が返されます
****************************************************************/
CollShape::CollShape(Collision* rParent, int rGroupId)
{
	mParent = rParent;
	mGroupId = rGroupId;
}

CollShape::~CollShape(void)
{
}

/*
	判定
*/
bool CollShape::Collides(CollShape* rOperand)
{
	return false;
}

// ｹﾞｯﾀｰ
Collision* CollShape::GetCollision()
{
	return mParent;
}

int CollShape::GetGroupId()
{
	return mGroupId;
}