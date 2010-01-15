#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\..\\Mob\\Collidable.h"

class Chandelier;
class ASQueenTrumpsAttack;

//! �g�����v
/****************************************************************//**
*	�㏸���ė�������
*	\nosubgrouping
********************************************************************/
class Trump : public Collidable
{

public:

	//! �W���ݽ�׸�
	Trump(int rX, int rY, string rGraphic, int rZ, int rRow, ASQueenTrumpsAttack* rParent);

	//! @see Movable
	void Move();
	//! �`��
	void Draw();
	
	//! �����蔻�艞��
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId,
		int rOpGroupId);


	//! �O�Ă�
	void TransformToSoldier(Chandelier* rChandelier);
	//! �����Ă��邩
	bool HasFallen();

private:

	string mGraphic;
	int mRow;
	float mAlpha;
	float mTimer;

	ASQueenTrumpsAttack* mParent;

	enum STATUS {
		WAIT,
		APPEAR,
		THROW,
		FALL
	} mStatus;

	// �ݒ�萔
	int FLOORY;
	int TRUMPTOPY;
	float STD_FADEIN_SP;
};
