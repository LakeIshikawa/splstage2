#pragma once

#include "Apple.h"

/*
	���ɗ�������]����n�߂���
*/
class RollingApple : public Apple
{
public:
	RollingApple(int rXPx, int rYPx, int rType);
	~RollingApple();

	void RollIfHitGround();
	void Kaiten();
	void Move();
	void Draw();

private:
	enum STATUS
	{
		FALL,
		ROLL
	};
	STATUS mStatus;

	int mType;

	float mAngle;
	float mAngSp;

	// �ݒ�萔
	float APPLE_RLSP;
	float APPLE_KTSP;
};