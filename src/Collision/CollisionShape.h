#pragma once

/*
	�����蔻��̴ر(�}�`)�̊�{�׽
*/
class CollisionShape
{
public:
	CollisionShape(void);
	virtual ~CollisionShape(void);

	virtual bool Collide(CollisionShape* rOperand) = 0;

	// �����蔻��̌v�Z
	//static bool 
};
