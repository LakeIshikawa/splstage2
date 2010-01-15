#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\..\\Mob\\Collidable.h"

//! ��
/****************************************************************//**
*	���݂����ɂȂ��[
*	\nosubgrouping
********************************************************************/
class Heart : public Collidable
{

public:

	//! �W���ݽ�׸�
	Heart(int rX, int rY, float rAngle);

	//! @see Movable
	void Move();
	//! �`��
	void Draw();
	
	//! �����蔻�艞��
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId,
		int rOpGroupId);

	// ��]����
	void Kaiten();

private:
	float mAngle;
	
	// �ݒ�萔
	float HEARTSP;
};
