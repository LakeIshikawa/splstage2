#pragma once

#include "Collision.h"

class CollisionDrawer
{
public:
	CollisionDrawer();
	~CollisionDrawer(void);

	void SetCollision(Collision* rCollision);

	void Draw();

private:
	Collision* mCollision;
};
