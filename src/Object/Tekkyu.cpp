#include "Tekkyu.h"
#include "..\\Management\\GameControl.h"
#include "..\\MapCollision\\PointMapCollider.h"
#include "TekkyuStand.h"

class AshibaInvisible;
class AshibaMovable;
class AshibaTenbin;

/**
	標準コンストラクタ
*/
Tekkyu::Tekkyu(int rXPx, int rYPx, float rZ, TekkyuStand* rParent)
{
	mParent = rParent;

	// 設定定数
	TEKKYU_SHOMETSUTIME = GF("TEKKYU_SHOMETSUTIME");

	// 位置情報
	mSizeX = GI("TEKKYUSX");
	mSizeY = GI("TEKKYUSY");

	mX = rXPx;
	mY = rYPx;
	mZ = rZ;

	mAddSpX = 0;
	mAshiba = NULL;

	// ﾏｯﾌﾟあたり判定
	mMapCollision = new PointMapCollider( this );
	mMapCollision->AddCollisionPoint( MapCollider::MCSD_DOWN, 34, 102 );
	mMapCollision->AddCollisionPoint( MapCollider::MCSD_DOWN, 71, 102 );
	mMapCollision->AddCollisionPoint( MapCollider::MCSD_FRONT, 94, 34 );
	mMapCollision->AddCollisionPoint( MapCollider::MCSD_FRONT, 94, 71 );
	
	// 当たり判定
	AddFrame(0);
	AddCircle(0, SP->GRID_BOGYO, 52, 52, 52);
	AddIndexedRect(0, SP->GRID_BOUND, 0, 20, 10, 84, 94);
	
	AddFrame(1); //判定なし

	// ﾀｰｹﾞｯﾄ
	AddTarget(GAMECONTROL->GetJiki());
	GAMECONTROL->GetMobManager()->AddAsTargetAllOf<Tekkyu>(this);
	GAMECONTROL->GetStageManager()->GetCurrentStage()->GetHaichi()->SetAshibaTargets(this);
	SetCurFrame(1);

	// 回転用
	mAngle = 0.0f;

	// ｱﾙﾌｧ値
	mAlpha = 1.0f;

	// ｽﾃｰﾀｽ
	mStatus = GENERATE;

	// 消滅ﾀｲﾏｰ
	mDieTimer = 0.0f;

	// 音声用のフラグ :UGLY:
	mIsRolling = false;
}

/**
	標準デストラクタ
*/
Tekkyu::~Tekkyu()
{
}

/************************************************************//**
*	1ﾌﾚｰﾑ処理
****************************************************************/
void Tekkyu::Move()
{
	// 消滅中
	if( mStatus == DIE ){
		Disappear();
		Draw();
		return;
	}

	// 出現中
	if( mStatus == GENERATE ){
		if( mY >= mParent->GetY() ){
			mStatus = FALL;
			SetCurFrame(0); // あたり判定を有効に
			// SE
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_ttekkyuu_hassya.wav");
		}
	}

	// ﾏｯﾌﾟとの当たり判定
	mMapCollision->CollisionRecognition();

	// 地面に当たったら転がる
	RollIfHitGround();
	// 転がっているなら回す
	if( mStatus == ROLLING ) Kaiten();
	// 弾む
	Rebound();
	// 落ちる
	Fall();
	// 何かにぶつかったらとまる
	StopIfHitWall();
	// 消滅
	DieIfStopAndNSec();

	// ﾏｯﾌﾟから抜けたら死ぬ
	DieIfGamenGai();

	// 力学
	mSpX += mAccX;
	mSpY += mAccY;
	mX += mSpX + mAddSpX;
	mY += mSpY;

	// 装置の描画
	Draw();

	mAddSpX = 0;
}

/************************************************************//**
*	描画
****************************************************************/
void Tekkyu::Draw()
{
	// 出現中の時
	int cuty = 0;
	if( mStatus == GENERATE ){
		cuty = mParent->GetY() - mY;
	}

	// 鉄球
	DX_SCROLL_ROT_DRAWALPHA("graphics\\object\\obj_ag.png", 
		mX, mY+cuty+1, 0, cuty, mSizeX, mSizeY, mAngle, mAlpha);
	// 影
	DX_SCROLL_ROT_DRAWALPHA("graphics\\object\\obj_ag_a.png", 
		mX, mY+cuty+1, 0, cuty, mSizeX, mSizeY, 0.0f, mAlpha);

}

/************************************************************//**
*	標準の当たり判定\n
*	
*	\param rCollObject	当たった先のｵﾌﾞｼﾞｪｸﾄ(例：ﾋﾛｲﾝ)
*	\param rThisGroupId	こっちのGROUPID(所々によって違う)
*	\param rOpGroupId	当たった先のｵﾌﾞｼﾞｪｸﾄのGROUPID(所々によって違う)
*
****************************************************************/
void Tekkyu::CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId)
{

	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);
	Tekkyu* tekkyu = dynamic_cast<Tekkyu*>(rCollObject);
	
	// ﾋﾛｲﾝ
	if( jiki && rOpGroupId == SP->GRID_BOGYO && mStatus!=DIE ){
		jiki->InflictDamage();
	}

	// 鉄球同士
	if( tekkyu ){
		mSpX = 0;
		mStatus = STOP;
	}
}

/************************************************************//**
*	地面とあたった瞬間に転がり始める
****************************************************************/
void Tekkyu::RollIfHitGround()
{
	if( mStatus == FALL && IsHittingGround() ){
		mStatus = ROLLING;

		mAngle = 0;
	
		mSpX = GF("TEKKYU_RLSP");

	}
}

/************************************************************//**
*	回転する
****************************************************************/
void Tekkyu::Kaiten()
{
	mAngle += mSpX/(mSizeX/2);
	if( mAngle >= D3DX_PI*2 ) mAngle = 0;
}

/************************************************************//**
*	重力の影響で、落ちる。　ﾏｯﾌﾟにあたったらそこで静止する。
****************************************************************/
void Tekkyu::Fall()
{
	// 動き
	if( IsHittingGround() )
	{
		// 位置修正
		if( !mAshiba) mY = mMapCollision->GetAdjustedPosition( MapCollider::MCSD_DOWN )+1;
	}
	else{
		mAccY = SP->GRAVITY;
	}
}

/************************************************************//**
*	\return 地面に当たっているか
****************************************************************/
bool Tekkyu::IsHittingGround()
{
	return 
		(mMapCollision->GetCollision( MapCollider::MCSD_DOWN ) == SP->CHIP_AMHIT ||
		mMapCollision->GetCollision( MapCollider::MCSD_DOWN ) == SP->CHIP_KGHIT ||
		mAshiba
		);
}

/************************************************************//**
*	弾む
****************************************************************/
void Tekkyu::Rebound()
{
	if( IsHittingGround() ){
		// SE
		if( fabs(mSpY) >= 20 )
		{
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_ttekkyuu_setti.wav");
		}
		else{
			if( !mIsRolling ){
				// SE
				GAMECONTROL->GetSoundController()->LoopSE("audio\\se\\se_ttekkyuu_move.wav");
				mIsRolling = true;
			}
		}
		mSpY = -mSpY/2;
		if( mSpY < 0 && mAshiba ) {
			mAshiba->GetOff(this);
			mAshiba = NULL;
		}
	}
}

/************************************************************//**
*	「前」だけが見られる
****************************************************************/
void Tekkyu::StopIfHitWall()
{
	if( mMapCollision->GetCollision( MapCollider::MCSD_FRONT ) == SP->CHIP_HIT && 
		mStatus == ROLLING){
		mSpX = 0;
		mStatus = STOP;
	}
}

/************************************************************//**
*	消滅
****************************************************************/
void Tekkyu::DieIfStopAndNSec()
{
	if( mStatus == STOP ){
		// SE
		GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_ttekkyuu_move.wav");

		WAIT_TIMER( mDieTimer, TEKKYU_SHOMETSUTIME )
			mStatus = DIE;
		WAIT_END
	}
}

/************************************************************//**
*	徐々に消えていく
****************************************************************/
void Tekkyu::Disappear()
{
	mAlpha -= 0.02f;
	if( mAlpha < 0.0f ){
		GAMECONTROL->GetMobManager()->Remove(this);
		if( mAshiba ) mAshiba->GetOff(this);

		// すべての鉄球から自分というﾀｰｹﾞｯﾄを排除する
		GAMECONTROL->GetStageManager()->GetCurrentStage()->
			GetHaichi()->RemoveAshibaTargets( this );
	}

}
