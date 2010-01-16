#include "MovieActor.h"
#include "..\\Management\\GameControl.h"

/**
	標準コンストラクタ
*/
MovieActor::MovieActor(int rSizeX, int rSizeY)
{
	mSizeX = rSizeX;
	mSizeY = rSizeY;

	mJikiColliding = false;

  	mAnimSet = new AnimationSet();
	mSDrawer = new SimpleDrawer();				  
	mSDrawer->SetPositionInfo(this);
}

/**
	標準デストラクタ
*/
MovieActor::~MovieActor()
{
	delete mAnimSet;
	delete mSDrawer;
}

/************************************************************//**
*	1ﾌﾚｰﾑ処理
****************************************************************/
void MovieActor::Move()
{
	// ｱﾆﾒｰｼｮﾝ
	mAnimSet->ElapseTime( SP->FrameTime );

	// 移動
	mSpX += mAccX;
	mSpY += mAccY;
	mX += mSpX;
	mY += mSpY;

	Draw();
}

/************************************************************//**
*	描画
****************************************************************/
void MovieActor::Draw()
{
	// 描画を設定する
	mSDrawer->SetAnimation( mAnimSet->GetCurAnimation() );
	mSDrawer->Draw();
}

/************************************************************//**
*	標準の当たり判定\n
*
*	ヒロインだけを対象する。敵と足場の当たり応答は、敵が担当する。
*	
*	\param rCollObject	当たった先のｵﾌﾞｼﾞｪｸﾄ(例：ﾋﾛｲﾝ)
*	\param rThisGroupId	こっちのGROUPID(所々によって違う)
*	\param rOpGroupId	当たった先のｵﾌﾞｼﾞｪｸﾄのGROUPID(所々によって違う)
*
****************************************************************/
void MovieActor::CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId)
{
	if( rOpGroupId == SP->GRID_KOUGEKI && rThisGroupId == SP->GRID_BOGYO )
		mJikiColliding = true;
}


/************************************************************//**
*	\return ｱﾆﾒｰｼｮﾝｾｯﾄ
****************************************************************/
AnimationSet* MovieActor::GetAnimationSet()
{
	return mAnimSet;
}


/************************************************************//**
*	\return ﾋﾛｲﾝの役者攻撃に当たったか
*	:UGLY:
****************************************************************/
bool MovieActor::IsJikiColliding()
{
	return mJikiColliding;
}