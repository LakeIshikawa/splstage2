#pragma once

#include "Apple.h"

/*
	°‚É—‚¿‚½‚ç“]‚ª‚èn‚ß‚é‚è‚ñ‚²
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

	// İ’è’è”
	float APPLE_RLSP;
	float APPLE_KTSP;
};