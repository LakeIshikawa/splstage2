#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Chandelier.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\..\\Jiki\\Jiki.h"

/************************************************************//**
*　設定定数を読み込む
****************************************************************/
Chandelier::Chandelier()
{
	// 位置
	mSizeX = GI("CHANDSX");
	mSizeY = GI("CHANDSY");
	CHANDCHAINDX = GI("CHANDCHAINDX");
	CHANDCHAINDY = GI("CHANDCHAINDY");
	CHANDCHAINSX = GI("CHANDCHAINSX");
	CHANDCHAINSY = GI("CHANDCHAINSY");
	FLOORY = GI("FLOORY");

	SetStage(false);

	mX = GI("CHANDX");
	mY = GI("CHANDY");
	mZ = -0.01f;

	// 当たり判定
	AddFrame(0);
	AddIndexedRect(0, SP->GRID_BOUND, 0, 13, 34, 360, 42);
	AddFrame(1);
	AddIndexedRect(1, SP->GRID_BOUND, 0, 13, 34, 360, 42);
	AddRect(1, SP->GRID_KOUGEKI, 3, 84, 371, 108);
	AddTarget(GAMECONTROL->GetJiki());

	// 初期化
	mStatus = STOP;
	mTimer = 0.0f;
}

/************************************************************//**
*	設定定数を設定する
*	\param rStrong 威力強か
****************************************************************/
void Chandelier::SetStage(bool rStrong)
{
	if(rStrong){
		CHANDRAISESP = GF("CHANDRAISESP2");
		CHANDWTTIME = GF("CHANDWTTIME2");
		GRAVITY = SP->GRAVITY*5/4;
	}
	else{
		CHANDRAISESP = GF("CHANDRAISESP");
		CHANDWTTIME = GF("CHANDWTTIME");
		GRAVITY = SP->GRAVITY;
	}
}

/************************************************************//**
*	ｱﾆﾒｰｼｮﾝと描画を行う
****************************************************************/
void Chandelier::Move()
{
	switch( mStatus )
	{
		case STOP: break;
		case FALL:	Fall(); break;
		case FLOOR: Floor(); break;
		case RAISE: Raise();break;
	}

	// 移動
	mSpY += mAccY;
	mY += mSpY;

	Ashiba::Move();
}

/************************************************************//**
*	描画
****************************************************************/
void Chandelier::Draw()
{
	// 鎖
	DX_DRAW("graphics\\teki\\queen\\boss4_light_chain.png", 
		mX+CHANDCHAINDX, mY+CHANDCHAINDY, 0, 0, CHANDCHAINSX, CHANDCHAINSY);
	// 本体
	DX_DRAW("graphics\\teki\\queen\\boss4_light.png", 
		mX, mY, 0, 0, mSizeX, mSizeY);
}

/************************************************************//**
*	落とす(一回呼び)
****************************************************************/
void Chandelier::Drop()
{
	mStatus = FALL;
	SetCurFrame(1);
}

/************************************************************//**
*		戻す(一回呼び)
****************************************************************/
void Chandelier::PickUp()
{
	mAccY = 0;
	mSpY = -CHANDRAISESP;
	mStatus = RAISE;
}

/************************************************************//**
*	\return このｵﾌﾞｼﾞｪｸﾄのｺﾋﾟｰ
****************************************************************/
Chandelier* Chandelier::Clone()
{
	Chandelier* newobj = new Chandelier();
	newobj->mStatus = mStatus;
	
	return newobj;
}

/************************************************************//**
*	落ちる
****************************************************************/
void Chandelier::Fall()
{
	mAccY = SP->GRAVITY;

	// 地面にぶつかる
	if( mY + mSizeY >= FLOORY ){
		mAccY = 0;
		mSpY = 0;
		mY = FLOORY - mSizeY;
		mStatus = FLOOR;
		SetCurFrame(0);
	}
}

/************************************************************//**
*	眠る
****************************************************************/
void Chandelier::Floor()
{
	WAIT_TIMER(mTimer, CHANDWTTIME)
		PickUp();
	WAIT_END
}

/************************************************************//**
*	戻る
****************************************************************/
void Chandelier::Raise()
{
	if( mY <= GI("CHANDY") ){
		mSpY = 0;
		mY = GI("CHANDY");
		mStatus = STOP;
	}
}

/************************************************************//**
*	攻撃あたり判定
****************************************************************/
void Chandelier::CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId)
{
	// 足場の判定
	Ashiba::CollisionResponse(rCollObject, rThisGroupId, rOpGroupId);

	// 攻撃の判定
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);
	if( jiki && rThisGroupId == SP->GRID_KOUGEKI && rOpGroupId == SP->GRID_BOGYO && mStatus == FALL ){
		jiki->InflictDamage();
	}
}

/************************************************************//**
*	\return 停止の状態か
****************************************************************/
bool Chandelier::IsStopped()
{
	return mStatus == STOP;
}
