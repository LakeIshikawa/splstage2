#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASOokamiStraightAttack.h"
#include "..\\..\\..\\Animation\\Animation.h"
#include "..\\..\\..\\Management\\GameControl.h"

/************************************************************//**
*	ｱﾆﾒｰｼｮﾝの作成
****************************************************************/
void ASOokamiStraightAttack::BuildAnimation(ActionState* rPrevState)
{
	mAnimation = Animation::ParseFromFile( "data\\animdata\\ookami\\StraightAttack.txt" );
}

/************************************************************//**
*	位置情報の作成
****************************************************************/
void ASOokamiStraightAttack::BuildPosInfo(ActionState* rPrevState)
{
	// 固定情報
	ASOokamiBase::BuildPosInfo(rPrevState);
	mY = GI("OOKAMI_STARTY");

	// 初期以外のみ
	if( rPrevState ){
		// 右側にいる場合
		if( rPrevState->GetX() >= SP->SCRSZX ){
			mMuki = 0;
		}
		// 左側にいる場合
		else if( rPrevState->GetX() <= 0 ){
			mMuki = 1;
		}
	}

	// X速度
	mSpX = (mMuki?1:-1) * OOKAMI_STRATKSPX;
}

void ASOokamiStraightAttack::OnEnter()
{}

/************************************************************//**
*	直進移動と終了条件
****************************************************************/
bool ASOokamiStraightAttack::Update() 
{
	// 直進
	mX += mSpX;

	// 終了条件
	return ((mMuki && mX > SP->SCRSZX) || (!mMuki && mX < -mFrameSizeX));
}

void ASOokamiStraightAttack::OnExit() 
{}

