#pragma once

#include "CollisionShape.h"

/*
	’·•ûŒ`‚Ì“–‚½‚è”»’è”ÍˆÍ
*/
class CollRect : public CollisionShape
{
public:
	CollRect(void);
	~CollRect(void);

	bool Collide(CollisionShape* rOperand);
};
