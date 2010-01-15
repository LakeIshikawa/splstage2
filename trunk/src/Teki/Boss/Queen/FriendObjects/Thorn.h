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
class Thorn : public Collidable
{

public:

	//! �W���ݽ�׸�
	Thorn(int rX, int rY, float rSp);

	//! @see Movable
	void Move();
	//! �`��
	void Draw();
	
	//! �����蔻�艞��
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId,
		int rOpGroupId);

	//! ���
	void SetPos(int rX, int rY);

	//! ���ˁI
	void Pull();

	//! ��ذ
	float GetHeight() { return mHeight; }

private:
	enum {
		STANDBY,
		ACTION
	} mStatus;

	float mHeight;
	float mSpeed;
};
