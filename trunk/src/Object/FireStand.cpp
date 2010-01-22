#include "FireStand.h"
#include "..\\Management\\GameControl.h"
#include "..\\ParticleEmitter\\PeHibashira.h"

/**
	標準コンストラクタ
*/
FireStand::FireStand(int rXPx, int rYPx, float rZ, bool rUpDown) : mUpDown(rUpDown)
{
	HIBASHIRA_HEIGHT = GI("HIBASHIRA_HEIGHT");
	HIBASHIRA_BASESPX = GF("HIBASHIRA_BASESPX");

	mSizeX = GI("FIRESTDSX");
	mSizeY = GI("FIRESTDSY");

	mX = rXPx;
	mY = rYPx - mSizeY + SP->CHSZY;
	mZ = rZ;

	mStatus = WAIT;

	mFireTop = 0;
	mFireBottom = 0;

	FIRESTD_PRODTIME = GF("FIRESTD_PRODTIME");
	mProdTimer = FIRESTD_PRODTIME;

	// ｴﾐｯﾀ
	int chouseiY = (mUpDown?-1:1)*20;
	mEmitter = new PeHibashira( mX+13, mY+chouseiY+(mUpDown*mSizeY), 
		1000, mUpDown?"graphics\\effect\\fire_d.jpg":"graphics\\effect\\fire.jpg", 
		mSizeX-10, GI("HIBASHIRA_HEIGHT"), mUpDown );
	mEmitter->InitParticles( D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );

	// 当たり判定
	AddFrame( 0 );
	AddIndexedRect( 0, SP->GRID_KOUGEKI, 0, 0, mFireTop, mSizeX, mFireBottom);
	AddTarget( GAMECONTROL->GetJiki() );

}

/**
	標準デストラクタ
*/
FireStand::~FireStand()
{}

/************************************************************//**
*	1ﾌﾚｰﾑ処理
****************************************************************/
void FireStand::Move()
{
	// 画面外の場合、ﾀｲﾏｰをﾘｾｯﾄ
	if( GAMECONTROL->GetStageManager()->GetCurrentStage()->GetMap()->IsGamenGai( mX, mY, mSizeX, mSizeY ) )
	{
		mProdTimer = FIRESTD_PRODTIME;
		mStatus = WAIT;
	}

	// ﾀｲﾏｰを待機
	mProdTimer -= SP->FrameTime;
	if( mProdTimer <= 0.0f ){
		mProdTimer = FIRESTD_PRODTIME;
				
		switch( mStatus ) {

			case WAIT: { 
				mStatus = FIRE; 
				mEmitter->Start();
				mFireTop = 0;
				mFireBottom = 0;
				// SE
				GAMECONTROL->GetSoundController()->LoopSE("audio\\se\\se_fire.wav");
				break;
			}

			case FIRE: { 
				mStatus = WAIT; 
				mEmitter->Stop(); 
				// SE
				GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_fire.wav");
				break; 
			}
		}
	}

	// 判定長方形の調整
	AdjustCollision();
	if( mStatus == FIRE ) FadeInCollision();
	else FadeOutCollision();

	// 炎
	mEmitter->Update();
	mEmitter->Render();

	// 装置の描画
	Draw();
}

/************************************************************//**
*	描画
****************************************************************/
void FireStand::Draw()
{
	// 装置
	DX_SCROLL_DRAW("graphics\\object\\obj_fire_stand.png", 
		mX, mY, 0, (mUpDown*mSizeY), mSizeX, (mUpDown+1)*mSizeY);
}

/************************************************************//**
*	標準の当たり判定\n
*	
*	\param rCollObject	当たった先のｵﾌﾞｼﾞｪｸﾄ(例：ﾋﾛｲﾝ)
*	\param rThisGroupId	こっちのGROUPID(所々によって違う)
*	\param rOpGroupId	当たった先のｵﾌﾞｼﾞｪｸﾄのGROUPID(所々によって違う)
*
****************************************************************/
void FireStand::CollisionResponse(ICollidable *rCollObject, 
								  int rThisGroupId, int rOpGroupId)
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);
	if( jiki && rOpGroupId == SP->GRID_BOGYO && mStatus == FIRE){
		jiki->InflictDamage();
	}
}

/************************************************************//**
*	火の動きによって判定長方形も変えてあげる
****************************************************************/
void FireStand::AdjustCollision()
{
	Rect* r = (Rect*)pCollision->GetCurFrame()->GetIndexedShape( 0 );

	if( mUpDown ){
		// 下向き
		r->SetTop( mFireBottom + mSizeY - 10 );
		r->SetBottom( mFireTop + mSizeY );
	}
	else{
		// 上向き
		r->SetTop( -mFireTop );
		r->SetBottom( -mFireBottom + 10 );
	}
}

/************************************************************//**
*	FadeInCollision
****************************************************************/
void FireStand::FadeInCollision()
{
	mFireBottom = 0;
	if( mFireTop < HIBASHIRA_HEIGHT )
		mFireTop += HIBASHIRA_BASESPX;
}

/************************************************************//**
*	FadeOutCollision
****************************************************************/
void FireStand::FadeOutCollision()
{
	if( mFireTop >= HIBASHIRA_HEIGHT && mFireBottom < HIBASHIRA_HEIGHT )
		mFireBottom += HIBASHIRA_BASESPX;
	else{
		mFireBottom = 0;
		mFireTop = 0;
	}
}