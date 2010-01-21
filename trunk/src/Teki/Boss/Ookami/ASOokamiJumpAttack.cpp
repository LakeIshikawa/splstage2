#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASOokamiJumpAttack.h"
#include "..\\..\\..\\Management\\GameControl.h"

/************************************************************//**
*	位置情報の作成
****************************************************************/
void ASOokamiJumpAttack::BuildPosInfo(ActionState* rPrevState)
{
	// 固定情報
	ASOokamiBase::BuildPosInfo(rPrevState);

	// 初期以外のみ
	if( rPrevState ){
		// 右側にいる場合
		if( rPrevState->GetX() >= SP->SCRSZX ){
			mMuki = 0;
			mY = GI("OOKAMI_STARTY");
		}
		// 左側にいる場合
		else if( rPrevState->GetX() <= 0 ){
			mMuki = 1;
			mY = GI("OOKAMI_STARTY");
		}
	}

	// X速度
	mSpX = (mMuki?1:-1) * OOKAMI_STRATKSPX;
}

/************************************************************//**
*	ｱﾆﾒｰｼｮﾝの作成
****************************************************************/
void ASOokamiJumpAttack::BuildAnimation(ActionState* rPrevState)
{
	mAnimation = Animation::ParseFromFile( "data\\animdata\\ookami\\JumpAttack.txt" );
}

/************************************************************//**
*	OnEnter
****************************************************************/
void ASOokamiJumpAttack::OnEnter()
{
	// SE
	GAMECONTROL->GetSoundController()->LoopSE("audio\\se\\se_boss2_bress_out.wav");
}

/************************************************************//**
*	ｼﾞｬﾝﾌﾟしながら攻撃してくる
****************************************************************/
bool ASOokamiJumpAttack::Update()
{

	// ｼﾞｬﾝﾌﾟ
	if( mY >= OOKAMI_STARTY ){
		mSpY = -OOKAMI_JMPSHOSOKUY;
	}
	else{
		mSpY += SP->GRAVITY;
	}
	mY += mSpY;

	return ASOokamiStraightAttack::Update();
}


/************************************************************//**
*	OnExit
****************************************************************/
void ASOokamiJumpAttack::OnExit()
{
	// SE
	GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_boss2_bress_out.wav");
}