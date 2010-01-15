#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\Mob\\Collidable.h"
#include "..\\..\\..\\Mob\\MobDrawer\\SimpleDrawer.h"
#include "..\\..\\..\\Animation\\Animation.h"

//! �Ƃ̊�{�׽
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class Storm: public Collidable
{

public:

	//! �W���ݽ�׸�
	Storm(bool rMuki);

	//! 1�ڰя���
	void Move();

	//! �����蔻�艞��
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId);

protected:
	
	Animation* mAnimation;
	SimpleDrawer* mDrawer;

	//�ݒ�萔
	float STORM_SP;

};

