#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "AppleGenerator.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\..\\Item\\PickUpEffect.h"
#include "..\\..\\..\\..\\Jiki\\Jiki.h"

/************************************************************//**
*　設定定数を読み込む
****************************************************************/
AppleGenerator::AppleGenerator(int rX, int rY)
{
	STD_FADEIN_SP = GF("STD_FADEIN_SP");
	APPLE_BEFOREAPP = GF("APPLE_BEFOREAPP");
	APPLE_BEFOREDISAPP1 = GF("APPLE_BEFOREDISAPP1");
	APPLE_BEFOREDISAPP2 = GF("APPLE_BEFOREDISAPP2");

	// 位置
	mSizeX = GI("ITEMSX");
	mSizeY = GI("ITEMSY");

	mX = rX;
	mY = rY;
	mMuki = 0;
	
	// 当たり判定
	AddFrame(0);
	AddCircle(0, SP->GRID_BOGYO, mSizeX/2, mSizeY/2, mSizeX/2);
	AddTarget(GAMECONTROL->GetJiki());

	// 初期化
	mStatus = ACTIVE;
	mAlpha = 1.0f;
	mTimer = 0.0f;
	mStage = 0;
}

/************************************************************//**
*	1ﾌﾚｰﾑ処理
****************************************************************/
void AppleGenerator::Move()
{
	
	switch( mStatus ){

		// ﾌｪｰﾄﾞｲﾝ
		case APPEAR:
			mAlpha += STD_FADEIN_SP;
			if( mAlpha >= 1.0f ){
				mAlpha = 1.0f;
				mStatus = ACTIVE;
			}
			break;

		// 待機
		case ACTIVE:
			WAIT_TIMER(mTimer, mStage?APPLE_BEFOREDISAPP2:APPLE_BEFOREDISAPP1)
				mStatus = DISAPPEAR;
			mFlashNum = 0;
			mFlashFl = false;
			WAIT_END
			break;

		// ﾌｪｰﾄﾞｱｳﾄ
		case DISAPPEAR:
			if( mFlashNum >= GI("APPLE_TENTIMES") )
				mStatus = INACTIVE;

			if( !mFlashFl ) {
				mAlpha -= STD_FADEIN_SP/2;
				if( mAlpha <= 0.5f ){
					mAlpha = 0.5f;
					mFlashFl = !mFlashFl;
					mFlashNum++;
				}
			}
			else{
				mAlpha += STD_FADEIN_SP/2;
				if( mAlpha >= 1.0f ){
					mAlpha = 1.0f;
					mFlashFl = !mFlashFl;
				}
			}
			break;

		// 待機
		case INACTIVE:
			mAlpha = 0.0f;
			WAIT_TIMER(mTimer, APPLE_BEFOREAPP)
				mStatus = APPEAR;
			WAIT_END			
			break;
		
	}

	// 描画
	Draw();
}

/************************************************************//**
*	描画
****************************************************************/
void AppleGenerator::Draw()
{
	DX_DRAWALPHA("graphics\\item\\Apple_a.png", 
		mX, mY, 0, 0, mSizeX, mSizeY, mAlpha);

}

/************************************************************//**
*	当たり判定の応答
****************************************************************/
void AppleGenerator::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	// ﾋﾛｲﾝ
	if( (jiki && rOpGroupId == SP->GRID_BOGYO  || rOpGroupId == SP->GRID_KOUGEKI)  &&
		mStatus != INACTIVE )
	{
		// ｱｲﾃﾑが消える
		mStatus = INACTIVE;
		mTimer = 0.0f;
		mFlashNum = 0;
		mFlashFl = false;
		// 回復
		jiki->RestoreEmpacy(1);
		// 演出
		GAMECONTROL->GetMobManager()->Request( 
			new PickUpEffect( "graphics\\item\\enpathy_up.png" ), true );
	}
}
