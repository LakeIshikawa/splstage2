#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ActionState.h"
#include "ActionControllable.h"
#include "..\..\MapCollision\\MapCollider.h"
#include "..\\..\\Animation\\Animation.h"

/************************************************************//**
*	ﾎﾟｲﾝﾀｰの初期化
****************************************************************/
ActionState::ActionState() 
{
	mCollision = NULL;		//当たり判定
	mMapCollider = NULL;	//ﾏｯﾌﾟあたり判定
	mAnimation = NULL;		//ｱﾆﾒｰｼｮﾝ
	mMobDrawer = NULL;		//描画方法

	mWasInterrupted = false; //中断されたかのﾌﾗｸﾞの初期化
}


/************************************************************//**
*	所属のｵﾌﾞｼﾞｪｸﾄを開放する
****************************************************************/
ActionState::~ActionState() 
{
	if( mCollision )	delete mCollision;		//当たり判定
	if( mMapCollider)	delete mMapCollider;	//ﾏｯﾌﾟあたり判定
	if( mAnimation )	delete mAnimation;		//ｱﾆﾒｰｼｮﾝ
	if( mMobDrawer )	delete mMobDrawer;		//描画方法
}


/************************************************************//**
*	ｱﾆﾒｰｼｮﾝ時間を経過させるラップ。
****************************************************************/
void ActionState::ElapseTime(float rElapsedTime) 
{
	if( mAnimation ){
		mAnimation->ElapseTime( rElapsedTime );
	}
}

/************************************************************//**
*	\param state 前回ｽﾃｰﾄ
*	\param rParent このｱｸｼｮﾝの親となるｵﾌﾞｼﾞｪｸﾄ
*	ｽﾃｰﾄのﾃﾞｰﾀを作り出す
****************************************************************/
void ActionState::BuildState(ActionState* state, ActionControllable* rParent) 
{
	// 親の設定
	mParent = rParent;

	// 当たり判定
	BuildCollision( state );
	// ﾏｯﾌﾟあたり判定
	BuildMapCollider( state );
	// ｱﾆﾒｰｼｮﾝ
	BuildAnimation( state );
	// 描画
	BuildMobDrawer( state );
	// 派生ｸﾗｽの特別情報
	BuildOtherInfo( state );
	// 位置情報
	BuildPosInfo( state );
}

/************************************************************//**
*	\param rX 配置X
*	\param rY 配置Y
*	\param rParent このｱｸｼｮﾝの親となるｵﾌﾞｼﾞｪｸﾄ
*	初期ｽﾃｰﾄとして作り出す
****************************************************************/
void ActionState::BuildState(int rX, int rY, ActionControllable* rParent) 
{
	
	// 親の設定
	mParent = rParent;
	
	// 当たり判定
	BuildCollision( NULL );
	// ﾏｯﾌﾟあたり判定
	BuildMapCollider( NULL );
	// ｱﾆﾒｰｼｮﾝ
	BuildAnimation( NULL );
	// 描画
	BuildMobDrawer( NULL );
	// 派生ｸﾗｽの特別情報
	BuildOtherInfo( NULL );
	// 位置情報
	BuildPosInfo(rX, rY);
}


/************************************************************//**
*	\param state 前回ｽﾃｰﾄ
*	標準として前回ｽﾃｰﾄから位置情報がｺﾋﾟｰされる
****************************************************************/
void ActionState::BuildPosInfo(ActionState* state) 
{
	mX			= state->GetX();
	mY			= state->GetY();
	mSpX		= state->GetSpX();
	mSpY		= state->GetSpY();
	mAccX		= state->GetAccX();
	mAccY		= state->GetAccY();
	mMuki		= state->GetMuki();
	mFrameSizeX	= state->GetFrameSizeX();
	mFrameSizeY	= state->GetFrameSizeY();
}

/************************************************************//**
*	\param rX 配置X
*	\param rY 配置Y
****************************************************************/
void ActionState::BuildPosInfo(int rX, int rY) 
{
	mX			= rX;
	mY			= rY;
	mSpX		= 0;
	mSpY		= 0;
	mAccX		= 0;
	mAccY		= 0;
	mMuki		= 0;
	mFrameSizeX = 0;
	mFrameSizeY = 0;
}
