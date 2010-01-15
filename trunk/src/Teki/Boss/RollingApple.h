#pragma once

#include "Apple.h"

/*
	床に落ちたら転がり始めるりんご
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

	// 設定定数
	float APPLE_RLSP;
	float APPLE_KTSP;
};