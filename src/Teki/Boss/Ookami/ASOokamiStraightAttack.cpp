#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASOokamiStraightAttack.h"
#include "..\\..\\..\\Animation\\Animation.h"
#include "..\\..\\..\\Management\\GameControl.h"

/************************************************************//**
*	��Ұ��݂̍쐬
****************************************************************/
void ASOokamiStraightAttack::BuildAnimation(ActionState* rPrevState)
{
	mAnimation = Animation::ParseFromFile( "data\\animdata\\ookami\\StraightAttack.txt" );
}

/************************************************************//**
*	�ʒu���̍쐬
****************************************************************/
void ASOokamiStraightAttack::BuildPosInfo(ActionState* rPrevState)
{
	// �Œ���
	ASOokamiBase::BuildPosInfo(rPrevState);
	mY = GI("OOKAMI_STARTY");

	// �����ȊO�̂�
	if( rPrevState ){
		// �E���ɂ���ꍇ
		if( rPrevState->GetX() >= SP->SCRSZX ){
			mMuki = 0;
		}
		// �����ɂ���ꍇ
		else if( rPrevState->GetX() <= 0 ){
			mMuki = 1;
		}
	}

	// X���x
	mSpX = (mMuki?1:-1) * OOKAMI_STRATKSPX;
}

void ASOokamiStraightAttack::OnEnter()
{}

/************************************************************//**
*	���i�ړ��ƏI������
****************************************************************/
bool ASOokamiStraightAttack::Update() 
{
	// ���i
	mX += mSpX;

	// �I������
	return ((mMuki && mX > SP->SCRSZX) || (!mMuki && mX < -mFrameSizeX));
}

void ASOokamiStraightAttack::OnExit() 
{}

