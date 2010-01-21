#include <string>
#include <vector>
#include <exception>
#include <stdarg.h>
using namespace std;

#include "PickUpEffect.h"
#include "Item.h"
#include "..\\Management\\GameControl.h"

/************************************************************//**
*	標準コンストラクタ
****************************************************************/
Item::Item( int rX, int rY )
{
	mSizeX = GI("ITEMSX");
	mSizeY = GI("ITEMSY");
	mX = rX;
	mY = rY - mSizeY + SP->CHSZY;
	
	mMuki = false;

	// 当たり判定
	AddFrame(0);
	AddCircle( 0, SP->GRID_BOGYO, mSizeX/2, mSizeY/2, mSizeX/2 );
	AddTarget( GAMECONTROL->GetJiki() );

	// ﾏｯﾌﾟあたり判定
	mMapCollider = new PointMapCollider( this );
	mMapCollider->AddCollisionPoint( MapCollider::MCSD_DOWN, mSizeX/2, mSizeY );
	mMapCollider->AddCollisionPoint( MapCollider::MCSD_FRONT, mSizeX, 0 );
}

/************************************************************//**
*	標準デストラクタ
****************************************************************/
Item::~Item()
{}

/************************************************************//**
*	更新と描画
****************************************************************/
void Item::Move()
{
	mMapCollider->CollisionRecognition();

	// 落ちる
	if( mMapCollider->GetCollision(MapCollider::MCSD_DOWN) == SP->CHIP_AMHIT ){
		mY = mMapCollider->GetAdjustedPosition(MapCollider::MCSD_DOWN);
		mSpY = 0;
		mAccY = 0;
		mSpX = 0;
	}
	else mAccY = SP->GRAVITY;

	// 壁に当たる
	if( mMapCollider->GetCollision(MapCollider::MCSD_FRONT) == SP->CHIP_HIT ){
		mSpX = 0;
	}

	mSpY += mAccY;
	mSpX += mAccX;
	mX += mSpX;
	mY += mSpY;

	// 描画
	DX_SCROLL_DRAW( GetGraphic(), mX, mY, 0, 0, mSizeX, mSizeY );
	CustomEffect();
}

/************************************************************//**
*	投げる
****************************************************************/
void Item::Launch(float rSpX, float rSpY, bool rMuki)
{
	mMuki = rMuki;
	mSpY = rSpX;
	mSpX = rSpY*(rMuki?1:-1);
}


/************************************************************//**
*	標準の当たり判定\n
*
*	ヒロインだけを対象する。
*	
*	\param rCollObject	当たった先のｵﾌﾞｼﾞｪｸﾄ(例：ﾋﾛｲﾝ)
*	\param rThisGroupId	こっちのGROUPID(所々によって違う)
*	\param rOpGroupId	当たった先のｵﾌﾞｼﾞｪｸﾄのGROUPID(所々によって違う)
*
****************************************************************/
void Item::CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId)
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	if(jiki && rOpGroupId == SP->GRID_BOGYO ){

		//SE
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_item_get.wav");
		// 効果
		DoEffect();
		// 消滅
		GAMECONTROL->GetMobManager()->Remove(this);
		// 演出
		GAMECONTROL->GetMobManager()->Request( new PickUpEffect( GetEffectGraphic() ), true );
		
	}
}