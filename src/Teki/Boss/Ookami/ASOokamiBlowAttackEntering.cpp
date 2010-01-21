#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASOokamiBlowAttackEntering.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "ASOokamiBlowAttackInspire.h"

/************************************************************//**
*	位置情報の作成
****************************************************************/
void ASOokamiBlowAttackEntering::BuildPosInfo(ActionState* rPrevState)
{
	// 固定情報
	ASOokamiStraightAttack::BuildPosInfo(rPrevState);
	
	// X速度
	mSpX = (mMuki?1:-1) * GI("OOKAMI_ENTERSPX");
}

/************************************************************//**
*	OnEnter
****************************************************************/
void ASOokamiBlowAttackEntering::OnEnter() {
	// SE
	GAMECONTROL->GetSoundController()->LoopSE("audio\\se\\se_boss2_move.wav");
}

/************************************************************//**
*	画面に入って終わり
****************************************************************/
bool ASOokamiBlowAttackEntering::Update() {
	// 直進
	mX += mSpX;

	// 終了条件
	return ((mMuki && mX > OOKAMI_ENTERLX) || (!mMuki && mX < OOKAMI_ENTERRX));
}

/************************************************************//**
*	次のｽﾃｰﾄに移る
****************************************************************/
void ASOokamiBlowAttackEntering::OnExit() 
{
	mParent->AddNextAction(new ASOokamiBlowAttackInspire());
}
