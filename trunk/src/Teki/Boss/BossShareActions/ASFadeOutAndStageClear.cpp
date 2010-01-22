#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASFadeOutAndStageClear.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionState.h"
#include "..\\..\\..\\Mob\\MobDrawer\\SimpleDrawer.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Animation\\Animation.h"
#include "..\\..\\..\\Event\\StageClearEvt.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"

/************************************************************//**
*	当たり判定なし
****************************************************************/
void ASFadeOutAndStageClear::BuildCollision(ActionState* rPrevState) 
{
	mCollision = NULL;
}

/************************************************************//**
*	ﾏｯﾌﾟあたり判定なし
****************************************************************/
void ASFadeOutAndStageClear::BuildMapCollider(ActionState* rPrevState) 
{
	mMapCollider = NULL; // ﾏｯﾌﾟあたり判定なし
}

/************************************************************//**
*	ｱﾆﾒｰｼｮﾝを継承
****************************************************************/
void ASFadeOutAndStageClear::BuildAnimation(ActionState* rPrevState) 
{
	// 初期ｽﾃｰﾄの場合
	if( !rPrevState ){
		mAnimation = NULL;
	}

	// それ以外の場合
	else{
		mAnimation = rPrevState->GetAnimation()->Clone();
	}
}

/************************************************************//**
*	描画方法をｺﾋﾟｰする
****************************************************************/
void ASFadeOutAndStageClear::BuildMobDrawer(ActionState* rPrevState) 
{
	// 初期ｽﾃｰﾄの場合
	if( !rPrevState ){
		mMobDrawer = NULL;
	}

	// それ以外の場合
	else {
		mMobDrawer = rPrevState->GetMobDrawer()->Clone();
		((SimpleDrawer*)mMobDrawer)->SetAnimation(mAnimation);
	}
}

/************************************************************//**
*	他情報のﾋﾞﾙﾄﾞなし
****************************************************************/
void ASFadeOutAndStageClear::BuildOtherInfo(ActionState* rPrevState) 
{}

/************************************************************//**
*	当たり判定の応答なし
****************************************************************/
void ASFadeOutAndStageClear::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{}

/************************************************************//**
*	
****************************************************************/
void ASFadeOutAndStageClear::OnEnter() 
{
	GAMECONTROL->GetTxtGraphicController()->ShowWithAlphaFade(
					TxtGraphicController::CENTER, 
					GI("STGCLRMOJI_SX"),GI("STGCLRMOJI_SY"), 
					"graphics\\txtgraphic\\stage_clear_01.png",
					GF("STGCLMOJI_DTIME"), GF("STGCLMOJI_FSP"));
	//BGM
	GAMECONTROL->GetSoundController()->SetBGM(SoundController::STGCLEAR);

}

/************************************************************//**
*	ﾌｪｰﾄﾞを行い、ﾌｪｰﾄﾞが終わるのを待つ
****************************************************************/
bool ASFadeOutAndStageClear::Update() 
{
	// ｽﾃｰｼﾞｸﾘｱの文字を表示してからﾌｪｰﾄﾞｱｳﾄ
	if( GAMECONTROL->GetTxtGraphicController()->IsFinished() )
		return GAMECONTROL->GetFader()->FadeOut();

	return false;
}

/************************************************************//**
*	ｽﾃｰｼﾞｸﾘｱを呼ぶ
****************************************************************/
void ASFadeOutAndStageClear::OnExit() 
{
	mParent->SetDead();
	GAMECONTROL->GetMobManager()->Remove(mParent);
	GAMECONTROL->GetEventManager()->Request( new StageClearEvt() );
}
