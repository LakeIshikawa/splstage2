#pragma once

#include "RollingApple.h"

/*
	投げ用のりんご
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

	// 設定定数
	float APPLE_THROW_HG;
	float APPLE_THROW_SPX;
};