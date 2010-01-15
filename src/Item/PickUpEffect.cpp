#include <string>
#include <vector>
#include <exception>
#include <stdarg.h>
using namespace std;

#include "PickUpEffect.h"
#include "..\\Management\\GameControl.h"

/************************************************************//**
*	標準コンストラクタ
****************************************************************/
PickUpEffect::PickUpEffect( string rGraphic ) : mGraphic( rGraphic )
{
	ITEMFXFADESP = GF("ITEMFXFADESP");

	mSizeX = GI("ITEMFXSX");
	mSizeY = GI("ITEMFXSY");

	mSpY =  GF("ITEMFXSHOSP");
	mAccY = GF("ITEMFXACCY");

	mY = GAMECONTROL->GetJiki()->GetY();
	mX = GAMECONTROL->GetJiki()->GetX() + abs(mSizeX - GAMECONTROL->GetJiki()->GetFrameSizeX())/2;

	mAlpha = 1.0f;
}

/************************************************************//**
*	標準デストラクタ
****************************************************************/
PickUpEffect::~PickUpEffect()
{}

/************************************************************//**
*	更新と描画
****************************************************************/
void PickUpEffect::Move()
{
	// Yはﾌﾞﾚｰｷして減速
	mSpY += mAccY;
	mY += mSpY;

	// ｱﾙﾌｧでﾌｪｰﾄﾞｱｳﾄ
	mAlpha -= ITEMFXFADESP;

	// 消滅
	if( mAlpha <= 0.0f )
		GAMECONTROL->GetMobManager()->Remove(this);

	// 描画
	DX_SCROLL_ROT_DRAWALPHA( mGraphic, mX, mY, 0, 0, mSizeX, mSizeY, 0.0f, mAlpha );
}
