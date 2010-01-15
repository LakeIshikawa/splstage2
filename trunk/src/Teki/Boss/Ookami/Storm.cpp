#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Storm.h"
#include "..\\..\\..\\Management\\GameControl.h"

/************************************************************//**
*	初期化
****************************************************************/
Storm::Storm(bool rMuki)
{
	//設定定数
	STORM_SP = GF("STORM_SP");

	// 位置を決める
	if( rMuki ){
		mX = GI("OOKAMI_BRPX1");
		mY = GI("OOKAMI_BRPY1");
	}
	else{ 
		mX = GI("OOKAMI_BRPX2");
		mY = GI("OOKAMI_BRPY2");
	}

	mSizeX = GI("OOKAMI_BRSX");
	mSizeY = GI("OOKAMI_BRSY");
	mMuki = !rMuki;

	// ｱﾆﾒｰｼｮﾝ
	mAnimation = new Animation();
	mAnimation->SetAnimData(0, 1, 2, -1);
	mAnimation->SetAnimIntervals(0.08f, 0.16f, 0.24f, -1.0f);
	mAnimation->SetAnimMode(Animation::ANMD_LOOP);
	mAnimation->SetGraphicSource("graphics\\teki\\ookami\\effect_storm.png");

	// 描画
	mDrawer = new SimpleDrawer();
	mDrawer->SetAnimation(mAnimation);
	mDrawer->SetPositionInfo(this);

	// 当たり判定
	AddFrame(0);
	AddRect(0, SP->GRID_BOGYO, 0, 0, mSizeX, mSizeY);

	AddTarget(GAMECONTROL->GetJiki());
}

/************************************************************//**
*	ｱﾆﾒｰｼｮﾝと描画
****************************************************************/
void Storm::Move()
{
	// ｱﾆﾒｰｼｮﾝ
	mAnimation->ElapseTime(SP->FrameTime);

	// 描画
	mDrawer->Draw();
}

/************************************************************//**
*	当たり判定応答
****************************************************************/
void Storm::CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId)
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	if(jiki){
		jiki->SetWindForce( STORM_SP * (!mMuki?1:-1));
	}
}
