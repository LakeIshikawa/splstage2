#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\Mob\\Collidable.h"
#include "..\\..\\..\\Mob\\MobDrawer\\SimpleDrawer.h"
#include "..\\..\\..\\Animation\\Animation.h"

//! ‰Æ‚ÌŠî–{¸×½
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class Storm: public Collidable
{

public:

	//! •W€ºİ½Ä×¸À
	Storm(bool rMuki);

	//! 1ÌÚ°Ñˆ—
	void Move();

	//! “–‚½‚è”»’è‰“š
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId);

protected:
	
	Animation* mAnimation;
	SimpleDrawer* mDrawer;

	//İ’è’è”
	float STORM_SP;

};

