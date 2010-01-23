#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Thorn.h"
#include "..\\..\\..\\TrumpSoldier.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\..\\Jiki\\Jiki.h"

/************************************************************//**
*　設定定数を読み込む
****************************************************************/
Thorn::Thorn(int rX, int rY, float rSp)
{
	// 位置
	mSizeX = GI("THORNSX");
	mSizeY = GI("THORNSY");

	mX = rX;
	mY = rY;

	mSpeed = rSp;

	// 当たり判定
	AddFrame(0);
	AddIndexedRect(0, SP->GRID_KOUGEKI, 0, 0, 0, mSizeX, mSizeY);
	AddTarget(GAMECONTROL->GetJiki());

	// 自分をトランプ兵のﾀｰｹﾞｯﾄに登録
	//GAMECONTROL->GetMobManager()->AddAsTargetToAllOf<TrumpSoldier>(this);

	// 初期化
	mHeight = 0;
	
	// SE
	GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_boss3_toge.wav");


}

/************************************************************//**
*	1ﾌﾚｰﾑ処理
****************************************************************/
void Thorn::Move()
{
	mHeight += mSpeed;
	
	// 頂点
	if( mHeight >= mSizeY ){
		mHeight = mSizeY;
		mSpeed *= -1;
	}
	if( mHeight <=0 && mSpeed <0 ){
		GAMECONTROL->GetMobManager()->Remove(this);
	}

	// 当たり判定を直す
	((Rect*)(pCollision->GetCurFrame()->GetIndexedShape(0)))->SetTop(-mHeight);
	((Rect*)(pCollision->GetCurFrame()->GetIndexedShape(0)))->SetBottom(0);

	Draw();
}

/************************************************************//**
*	描画
****************************************************************/
void Thorn::Draw()
{
	DX_DRAW("graphics\\teki\\queen\\boss4_thorn.png", 
		mX, mY-mHeight, 0, 0, mSizeX, mHeight);
}

/************************************************************//**
*	当たり判定の応答
****************************************************************/
void Thorn::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	// ﾋﾛｲﾝ
	if( jiki && rOpGroupId == SP->GRID_BOGYO  || rOpGroupId == SP->GRID_KOUGEKI ){
		jiki->InflictDamage();
	}
}

