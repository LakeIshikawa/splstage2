#pragma once

#include "..\\Mob\\Collidable.h"
#include "..\\Mob\\MobDrawer\\SimpleDrawer.h"
#include "..\\Animation\\Animation.h"

/*
	“G
*/
class StgClrDoor : public virtual Collidable
{
public:

	StgClrDoor(int rXPx, int rYPx, float Z);
	virtual ~StgClrDoor(void);

	void Move();

	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId);

	int GetSizeX();


protected:
	bool stageclear;
	Animation* mAnimation;
	
};
