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
class Rod : public Collidable
{

public:

	//! �W���ݽ�׸�
	Rod(float rStartAngle, bool rDir);

	//! @see Movable
	void Move();
	//! �`��
	void Draw();
	
	//! �����蔻�艞��
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId,
		int rOpGroupId);

	//! ���ʁE�۲݂Ƃ̓����蔻��(�l�p�ŉ�]���Ă���A�B��Ȃ��̂Ƃ��Ă̓��ʂȈ���)
	bool CollidesWithHeroine();

	//! �I����
	bool HasFinished();

private:
	float mStartAngle;
	float mAngle;
	float mAlpha;
	int mHeartShot;
	bool mDir;

	enum STATUS {
		APPEAR,
		ROTATE,
		DISAPPEAR,
		INACTIVE
	} mStatus;


	// �ݒ�萔
	float RODSPANG;
	float STD_FADEIN_SP;
};
