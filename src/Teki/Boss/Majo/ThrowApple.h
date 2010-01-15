#pragma once

#include "RollingApple.h"

/*
	�����p�̂��
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

	// �ݒ�萔
	float APPLE_THROW_HG;
	float APPLE_THROW_SPX;
};