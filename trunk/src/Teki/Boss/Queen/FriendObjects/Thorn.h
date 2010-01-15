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
class Thorn : public Collidable
{

public:

	//! •W€ºİ½Ä×¸À
	Thorn(int rX, int rY, float rSp);

	//! @see Movable
	void Move();
	//! •`‰æ
	void Draw();
	
	//! ‚ ‚½‚è”»’è‰“š
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId,
		int rOpGroupId);

	//! ¾¯Ä
	void SetPos(int rX, int rY);

	//! ”­ËI
	void Pull();

	//! ¸´Ø°
	float GetHeight() { return mHeight; }

private:
	enum {
		STANDBY,
		ACTION
	} mStatus;

	float mHeight;
	float mSpeed;
};
