#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\..\\Mob\\Collidable.h"

//! ����I�ɗь���o��
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class AppleGenerator: public Collidable
{

public:

	//! �W���ݽ�׸�
	AppleGenerator(int rX, int rY);

	//! @see ActionThread
	void Move();
	//! �`��
	void Draw();

	//! �ݺނ�������~����
	void StopAndClear();

	//! �З͂̐ݒ� ( 0-�Z���ԏo�� 1-�����ԏo�� )
	void SetStage(int rSt);

	//! �����蔻�艞��
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId,
		int rOpGroupId);

private:
	float mTimer;
	float mAlpha;
	int mStage;
	int mFlashNum;
	bool mFlashFl;

	enum STATUS {
		APPEAR,
		ACTIVE,
		DISAPPEAR,
		INACTIVE
	} mStatus;

	// �ݒ�萔
	float APPLE_BEFOREAPP;
	float APPLE_BEFOREDISAPP1;
	float APPLE_BEFOREDISAPP2;

	float STD_FADEIN_SP;
};

