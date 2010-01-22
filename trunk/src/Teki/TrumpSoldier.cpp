#include <string>
using namespace std;

#include "TrumpSoldier.h"
#include "..\\Management\\GameControl.h"
#include "..\\Jiki\\Jiki.h"
#include "..\\Animation\\AnimationSet.h"
#include "..\\Mob\\MobDrawer\\SimpleDrawer.h"
#include "..\\MapCollision\\PointMapCollider.h"
#include "Boss\\Queen\\FriendObjects\\Thorn.h"
#include "Boss\\Queen\\FriendObjects\\Heart.h"

/************************************************************//**
*　標準ｺﾝｽﾄﾗｸﾀ
****************************************************************/
TrumpSoldier::TrumpSoldier(int rX, int rY)
{
	TRUMPHEISP = GF("TRUMPHEISP");
	TRUMPHEIHANI = GI("TRUMPHEIHANI");

	// 位置
	mSizeX = GI("TRUMPHEISX");
	mSizeY = GI("TRUMPHEISY");

	mX = rX;
	mY = rY - mSizeY;
	mMuki = rand()%2;

	// 初期化
	mStatus = ST_WALK;

	// 当たり判定
	AddFrame(FR_NONE);
	AddRect(FR_NONE, SP->GRID_BOGYO, 77, 98, 109, 207);
	
	AddFrame(FR_ATTACK);
	AddRect(FR_ATTACK, SP->GRID_KOUGEKI, 0, 134, 181, 159);
	AddRect(FR_ATTACK, SP->GRID_BOGYO, 131, 82, 168, 205);

	AddTarget( GAMECONTROL->GetJiki() );

	//GAMECONTROL->GetMobManager()->AddAsTargetAllOf<Thorn>(this);
	//GAMECONTROL->GetMobManager()->AddAsTargetAllOf<Heart>(this);

	// ﾏｯﾌﾟとの当たり
	mMapCollider = new PointMapCollider(this);
	mMapCollider->AddCollisionPoint( MapCollider::MCSD_DOWN, 52, 205 );
	mMapCollider->AddCollisionPoint( MapCollider::MCSD_FRONT, 120, 150 );

	// ｱﾆﾒｰｼｮﾝ
	mAnimSet = new AnimationSet();

	// 描画
	mSDrawer = new SimpleDrawer();

	// 判定描画
	mDrawer = new CollisionDrawer();
}

/************************************************************//**
*　設定定数を読み込む
****************************************************************/
void TrumpSoldier::Build()
{
	// 歩く
	Animation* walk = new Animation();
	walk->SetGraphicSource( GetWalkGraphic() );
	walk->SetAnimData( 0, 1, 2, 1, 0, 3, 4, 3, -1 );
	walk->SetAnimIntervals( 0.2f, 0.4f, 0.6f, 0.8f, 1.0f, 1.2f, 1.4f, 1.6f, -1.0f );
	walk->SetAnimMode(Animation::ANMD_LOOP);
	mAnimSet->AddAnimation(AN_WALK, walk);

	// 攻撃
	Animation* attack = new Animation();
	attack->SetGraphicSource( GetAttackGraphic() );
	attack->SetAnimData( 0, 1, 2, -1 );
	attack->SetAnimIntervals( 0.2f, 0.4f, 0.6f, -1.0f );
	attack->SetAnimMode(Animation::ANMD_STOPATEND);
	mAnimSet->AddAnimation(AN_ATTACK, attack);

	// 刺す
	Animation* sasu = new Animation();
	sasu->SetGraphicSource( GetSasuGraphic() );
	sasu->SetAnimData( 0, 1, 0, -1 );
	sasu->SetAnimIntervals( 0.2f, 0.4f, 0.6f, -1.0f );
	sasu->SetAnimMode(Animation::ANMD_STOPATEND);
	mAnimSet->AddAnimation(AN_SASU, sasu);

	// 引く
	Animation* hiku = new Animation();
	hiku->SetGraphicSource( GetAttackGraphic() );
	hiku->SetAnimData( 2, 1, 0, -1 );
	hiku->SetAnimIntervals( 0.2f, 0.4f, 0.6f, -1.0f );
	hiku->SetAnimMode(Animation::ANMD_STOPATEND);
	mAnimSet->AddAnimation(AN_HIKU, hiku);

	// 死ぬ
	Animation* die = new Animation();
	die->SetGraphicSource( GetDieGraphic() );
	die->SetAnimData( 0, 1, -1 );
	die->SetAnimIntervals( 0.2f, 0.4f, -1.0f );
	die->SetAnimMode(Animation::ANMD_STOPATEND);
	mAnimSet->AddAnimation(AN_DIE, die);

	mAnimSet->SetCurAnimation(AN_WALK);

	mSDrawer->SetAnimation(mAnimSet->GetCurAnimation());
	mSDrawer->SetAlphaSrc( NULL );
	mSDrawer->SetPositionInfo( this );
}

/************************************************************//**
*	1ﾌﾚｰﾑ処理
****************************************************************/
void TrumpSoldier::Move()
{
	// ﾏｯﾌﾟ当たり
	mMapCollider->CollisionRecognition();

	// 挙動
	switch( mStatus ){

		// 歩く
		case ST_WALK:
			{
				// 直進で歩く
				mSpX = TRUMPHEISP * (mMuki?1:-1);

				// 壁による反転
				KabeHanten();
				// 落下
				Fall();			

				// ﾋﾛｲﾝに近づいたら攻撃する
				int jx = GAMECONTROL->GetJiki()->GetAtHtPointX();
				int jy = GAMECONTROL->GetJiki()->GetAtHtPointY();

				// ----自機の位置を確認
				float sax = jx - (mX+mSizeX/2);
				float say = jy - (mY+mSizeY/2);
				float sa = sqrt(sax*sax + say*say);

				if( sa < TRUMPHEIHANI ){
					mStatus = ST_ATTACK;
					mAnimSet->SetCurAnimation(AN_ATTACK);
				}
			}
			break;

		case ST_ATTACK:
			{
				//! 落下
				Fall();

				mSpX = 0;

				// ｱﾆﾒｰｼｮﾝが終わるまで待つ
				if( mAnimSet->GetCurAnimationIdx() == AN_ATTACK && mAnimSet->GetCurAnimation()->GetLoopCount() >= 1 ){
					// 刺す
					mAnimSet->GetCurAnimation()->Rewind();
					mAnimSet->SetCurAnimation(AN_SASU);
					SetCurFrame( FR_ATTACK );
					//SE
					GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_ken_atack.wav");
				}
				else if( mAnimSet->GetCurAnimationIdx() == AN_SASU && mAnimSet->GetCurAnimation()->GetLoopCount() >= 1 ){
					// 引く
					mAnimSet->GetCurAnimation()->Rewind();
					mAnimSet->SetCurAnimation( AN_HIKU );
					SetCurFrame( FR_NONE );
				}
				else if( mAnimSet->GetCurAnimationIdx() == AN_HIKU && mAnimSet->GetCurAnimation()->GetLoopCount() >= 1 ){
					// 歩き再開
					mAnimSet->GetCurAnimation()->Rewind();
					mAnimSet->SetCurAnimation( AN_WALK );
					mStatus = ST_WALK;
				}
			}
			break;

		case ST_DIE:
			DieIfGamenGai();
			break;

	}

	// 移動
	mSpY += mAccY;
	mX += mSpX;
	mY += mSpY;

	// 描画
	mAnimSet->ElapseTime( SP->FrameTime );
	mSDrawer->SetAnimation( mAnimSet->GetCurAnimation() );
	Draw();
}

/************************************************************//**
*	描画
****************************************************************/
void TrumpSoldier::Draw()
{
	mSDrawer->Draw();
}

/************************************************************//**
*	当たり判定の応答
****************************************************************/
void TrumpSoldier::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	if( rOpGroupId == SP->GRID_KOUGEKI && rThisGroupId == SP->GRID_BOGYO ){
			if( jiki && mStatus != ST_DIE){
				jiki->IncrementChain();
				jiki->IncreaseTensEmpa();
			}
			Die();
		}
	// ﾋﾛｲﾝ
	if( jiki) {
		if( (rOpGroupId == SP->GRID_BOGYO) && mStatus != ST_DIE){
			jiki->InflictDamage();
		}
	}
}

/************************************************************//**
*	死ぬ
****************************************************************/
void TrumpSoldier::Die()
{
	if( mStatus != ST_DIE ){
		mStatus = ST_DIE;
		mAnimSet->SetCurAnimation( AN_DIE );
		SetCurFrame( FR_NONE );

		// ﾋﾛｲﾝの位置によってx軸の速度を決める
		mSpX = -GF("SHINIPATT_SPX");
		Jiki* jiki = GAMECONTROL->GetJiki();
		if( jiki->GetAtHtPointX() < mX+mSizeX/2)
			mSpX *= -1;
	
		mSpY = -GF("SHINIPATT_SHOSP");
		mAccY = SP->GRAVITY;	

		//SE
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_kougekimeityuu.wav");
		GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_teki_down.wav");
	}
}


/************************************************************//**
*	壁にぶつかったら反転する
****************************************************************/
void TrumpSoldier::KabeHanten()
{
	// 壁にぶつかったら反転
	if( mMapCollider->GetCollision( MapCollider::MCSD_FRONT ) == SP->CHIP_GMNGAILT || 
		mMapCollider->GetCollision( MapCollider::MCSD_FRONT ) == SP->CHIP_GMNGAIRT || 
		mMapCollider->GetCollision( MapCollider::MCSD_FRONT ) == SP->CHIP_HIT )
	{
		mMuki = !mMuki;
	}
}


/************************************************************//**
*	地面がなかったら落ちる
****************************************************************/
void TrumpSoldier::Fall()
{
	// 床がなかったら落ちる
	if( mMapCollider->GetCollision( MapCollider::MCSD_DOWN ) == SP->CHIP_NOHIT  || 
		mMapCollider->GetCollision( MapCollider::MCSD_DOWN ) == SP->CHIP_GMNGAIDN )
		mAccY = SP->GRAVITY;
	else {
		mAccY = 0;
		mSpY = 0;
	}

	// 画面の下に行ったら死ぬ
	if( mMapCollider->GetCollision( MapCollider::MCSD_DOWN ) == SP->CHIP_GMNGAIDN ){
		DieIfGamenGai();
	}
}