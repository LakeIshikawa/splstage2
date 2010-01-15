#pragma once

#include "RollingApple.h"

/*
	“Š‚°—p‚Ì‚è‚ñ‚²
*/
class ThrowApple : public RollingApple
{
public:
	ThrowApple(int rXPx, int rYPx, int rMuki);
	~ThrowApple();

	void Rebound();
	void Move();

	void Throw();

private:

	int mMuki;
	int mRebounds;

	// İ’è’è”
	float APPLE_THROW_HG;
	float APPLE_THROW_SPX;
};