#pragma once

#include "CollisionShape.h"

/*
	�����`�̓����蔻��͈�
*/
class CollRect : public CollisionShape
{
public:
	CollRect(void);
	~CollRect(void);

	bool Collide(CollisionShape* rOperand);
};
