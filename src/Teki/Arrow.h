#pragma once
#include "..\\Mob\Collidable.h"
#include "..\\Management\\GameControl.h"

/*
	��
*/
class Arrow :
	public Collidable
{
public:
	Arrow(int rX, int rY, int rMtX, int MtY);
	~Arrow(void);

	void Move();

	void CollisionResponse(ICollidable* rCollObject, int rThisGroudId, int rOpGroupId);

	int GetSizeX() { return GI("ARROWSX"); }

private:
	float mMtX;
	float mMtY;

	float mAngle;

	float mShoumetsuTimer;

	enum STATUS{
		NORMAL,
		SASARE
	}
	mStatus;

	// �ݒ�萔
	int ARROWSX;
	int ARROWSY;

	float ARROWSPXDIV;
	float ARROWMAXSPY;

	float ARROWSHMTTIME;
};
