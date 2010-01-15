#include "RollingApple.h"
#include "..\\..\\Management\\GameControl.h"

RollingApple::RollingApple(int rXPx, int rYPx, int rType) : Apple( rXPx, rYPx )
{
	APPLE_RLSP = GF("APPLE_RLSP");
	APPLE_KTSP = GF("APPLE_KTSP");

	mStatus = FALL;
	mType = rType;
}

RollingApple::~RollingApple()
{}

/*
	���C������
*/
void RollingApple::Move()
{
	RollIfHitGround();
	Kaiten();
	Apple::Move();
}


/*
	�n�ʂƂ��������u�Ԃɓ]����n�߂�
*/
void RollingApple::RollIfHitGround()
{
	if( mStatus == FALL && IsHittingGround() ){
		mStatus = ROLL;

		mAngle = 0;
	
		if( mType == 2) mType = 2 + (rand()%2?-1:1);
		switch( mType ){
			case 3: { mSpX = -APPLE_RLSP; mAngSp = -APPLE_KTSP; } break;
			case 1: { mSpX = APPLE_RLSP; mAngSp = APPLE_KTSP; } break;
		}
	}
}

/*
	��]���ē]����
*/
void RollingApple::Kaiten()
{
	mAngle += mAngSp;
	if( mAngle >= D3DX_PI*2 ) mAngle = 0;
}

/*
	�`��
*/
void RollingApple::Draw()
{
	if( mStatus == ROLL ){
		DX_SCROLL_ROT_DRAW("graphics\\teki\\apple.png", mX, mY, mNo*APPLESZX, 0, (APPLESZX)*(mNo+1), APPLESZY, mAngle);
	}
	else{
		Apple::Draw();
	}
}