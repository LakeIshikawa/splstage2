#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASWaitForMaku.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionState.h"
#include "..\\..\\..\\Mob\\MobDrawer\\SimpleDrawer.h"
#include "..\\..\\..\\Jiki\\Jiki.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Animation\\Animation.h"

/************************************************************//**
*	当たり判定なし
****************************************************************/
void ASWaitForMaku::BuildCollision(ActionState* rPrevState) 
{
	mCollision = NULL;
}

/************************************************************//**
*	ﾏｯﾌﾟあたり判定なし
****************************************************************/
void ASWaitForMaku::BuildMapCollider(ActionState* rPrevState) 
{
	mMapCollider = NULL; // ﾏｯﾌﾟあたり判定なし
}

/************************************************************//**
*	ｱﾆﾒｰｼｮﾝを継承
****************************************************************/
void ASWaitForMaku::BuildAnimation(ActionState* rPrevState) 
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
void ASWaitForMaku::BuildMobDrawer(ActionState* rPrevState) 
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
void ASWaitForMaku::BuildOtherInfo(ActionState* rPrevState) 
{}

/************************************************************//**
*	当たり判定の応答なし
****************************************************************/
void ASWaitForMaku::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{}

/************************************************************//**
*	
****************************************************************/
void ASWaitForMaku::OnEnter() 
{
	
}

/************************************************************//**
*	幕が上がっているのを待つ
****************************************************************/
bool ASWaitForMaku::Update() {
	if( mOpenClose )
		return GAMECONTROL->GetMaku()->IsClosed();
	else
		return GAMECONTROL->GetMaku()->IsOpen();
}

/************************************************************//**
*	
****************************************************************/
void ASWaitForMaku::OnExit() {
	
}
