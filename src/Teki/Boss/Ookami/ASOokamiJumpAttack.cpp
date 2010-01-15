#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASOokamiJumpAttack.h"
#include "..\\..\\..\\Management\\GameControl.h"

/************************************************************//**
*	�ʒu���̍쐬
****************************************************************/
void ASOokamiJumpAttack::BuildPosInfo(ActionState* rPrevState)
{
	// �Œ���
	ASOokamiBase::BuildPosInfo(rPrevState);

	// �����ȊO�̂�
	if( rPrevState ){
		// �E���ɂ���ꍇ
		if( rPrevState->GetX() >= SP->SCRSZX ){
			mMuki = 0;
			mY = GI("OOKAMI_STARTY");
		}
		// �����ɂ���ꍇ
		else if( rPrevState->GetX() <= 0 ){
			mMuki = 1;
			mY = GI("OOKAMI_STARTY");
		}
	}

	// X���x
	mSpX = (mMuki?1:-1) * OOKAMI_STRATKSPX;
}

/************************************************************//**
*	��Ұ��݂̍쐬
****************************************************************/
void ASOokamiJumpAttack::BuildAnimation(ActionState* rPrevState)
{
	mAnimation = Animation::ParseFromFile( "data\\animdata\\ookami\\JumpAttack.txt" );
}

/************************************************************//**
*	�ެ��߂��Ȃ���U�����Ă���
****************************************************************/
bool ASOokamiJumpAttack::Update()
{

	// �ެ���
	if( mY >= OOKAMI_STARTY ){
		mSpY = -OOKAMI_JMPSHOSOKUY;
	}
	else{
		mSpY += SP->GRAVITY;
	}
	mY += mSpY;

	return ASOokamiStraightAttack::Update();
}


