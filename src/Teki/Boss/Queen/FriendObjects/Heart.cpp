#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Heart.h"
#include "..\\..\\..\\TrumpSoldier.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\..\\Jiki\\Jiki.h"

/************************************************************//**
*　設定定数を読み込む
****************************************************************/
Heart::Heart(int rX, int rY, float rAngle) : mAngle( rAngle )
{
	HEARTSP = GF("HEARTSP");

	// 位置
	mSizeX = GI("HEARTSX");
	mSizeY = GI("HEARTSY");

	mX = rX - mSizeX/2;
	mY = rY - mSizeY/2;
	mSpX = cos( rAngle - D3DX_PI/2 ) * HEARTSP;
	mSpY = sin( rAngle - D3DX_PI/2 ) * HEARTSP;
	
	// 当たり判定
	AddFrame(0);
	AddIndexedRect(0, SP->GRID_KOUGEKI, 0, 0, 0, mSizeX, mSizeY);
	AddTarget(GAMECONTROL->GetJiki());

	// トランプ兵
	//GAMECONTROL->GetMobManager()->AddAsTargetToAllOf<TrumpSoldier>(this);

	// 初期化
	
}

/************************************************************//**
*	1ﾌﾚｰﾑ処理
****************************************************************/
void Heart::Move()
{
	DieIfGamenGai();
	Kaiten();

	// 移動
	mX += mSpX;
	mY += mSpY;

	// 描画
	Draw();
}
/************************************************************//**
*	回転する
****************************************************************/
void Heart::Kaiten()
{
	mAngle += GF("HEART_KAITENSP");
	if( mAngle >= D3DX_PI*2 ){
		mAngle = 0;
	}
}

/************************************************************//**
*	描画
****************************************************************/
void Heart::Draw()
{
	DX_SCROLL_ROT_DRAW("graphics\\teki\\queen\\boss4_heart.png", 
		mX, mY, 0, 0, mSizeX, mSizeY, mAngle);
}

/************************************************************//**
*	当たり判定の応答
****************************************************************/
void Heart::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	// ﾋﾛｲﾝ
	if( jiki && rOpGroupId == SP->GRID_BOGYO  || rOpGroupId == SP->GRID_KOUGEKI ){
		jiki->InflictDamage();
	}
}
