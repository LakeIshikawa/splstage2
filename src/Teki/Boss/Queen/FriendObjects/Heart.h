#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\..\\Mob\\Collidable.h"

//! ‹¾
/****************************************************************//**
*	“ø‚İ‚½‚¢‚É‚È‚é‚æ[
*	\nosubgrouping
********************************************************************/
class Heart : public Collidable
{

public:

	//! •W€ºİ½Ä×¸À
	Heart(int rX, int rY, float rAngle);

	//! @see Movable
	void Move();
	//! •`‰æ
	void Draw();
	
	//! ‚ ‚½‚è”»’è‰“š
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId,
		int rOpGroupId);

	// ‰ñ“]‚·‚é
	void Kaiten();

private:
	float mAngle;
	
	// İ’è’è”
	float HEARTSP;
};
