#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\..\\Mob\\Collidable.h"

//! �g�����v��
/****************************************************************//**
*	���E�����ĕǂɔ��]����
*	\nosubgrouping
********************************************************************/
class TrumpSoldier : public Collidable
{

public:

	//! �W���ݽ�׸�
	TrumpSoldier(int rX, int rY, string rGraphic);

	//! @see Movable
	void Move();
	//! �`��
	void Draw();
	
	//! �����蔻�艞��
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId,
		int rOpGroupId);

private:

	string mGraphic;

	enum STATUS {
		WALK
	} mStatus;

	// �ݒ�萔
	int FLOORY;
	int TRUMPTOPY;
};
