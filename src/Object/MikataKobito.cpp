#include ".\MikataKobito.h"
#include "..\\Management\\GameControl.h"
#include "..\\Item\\Item.h"

/************************************************************//**
*	初期化
****************************************************************/
MikataKobito::MikataKobito(int rXPx, int rYPx)
{
	mSizeX = GI("MKOBITOSX");
	mSizeY = GI("MKOBITOSY");

	MKOBITO_LTIME = GF("MKOBITO_LTIME");
	MKOBITO_WTIME = GF("MKOBITO_WTIME");

	mX = rXPx;
	mY = rYPx - mSizeY + SP->CHSZY;
	mZ = -1.0f;

	mStatus		= WALK;
	mUrotsuki = 0;
	mLightTimer = 0.0f;
	mWalkTimer = 0.0f;

	// ﾏｯﾌﾟあたり
	mMapCollider = new PointMapCollider(this);
	mMapCollider->AddCollisionPoint( MapCollider::MCSD_DOWN, mSizeX, mSizeY );

	// ｱﾆﾒｰﾀｰ
	mAnimSet = new AnimationSet();

	// 徒歩
	Animation* walk = new Animation();
	walk->SetAnimData(  0, 1, 2, 1, 0, 3, 4, 3, -1 );
	walk->SetAnimIntervals( 0.2f, 0.4f, 0.6f, 0.8f, 1.0f, 1.2f, 1.4f, 1.6f, -1.0f );
	walk->SetAnimMode( Animation::ANMD_LOOP );
	mAnimSet->AddAnimation( WALK, walk );

	// 攻撃
	Animation* throws = new Animation();
	throws->SetAnimData( 0, 1, 2, 3, 4, -1 );
	throws->SetAnimIntervals( 0.2f, 0.4f, 0.6f, 0.8f, 1.0f, -1.0f );
	throws->SetAnimMode( Animation::ANMD_STOPATEND );
	mAnimSet->AddAnimation( THROW, throws );
	
	// ｼﾞｬﾝﾌﾟ
	Animation* jump = new Animation();
	jump->SetAnimData( 0, 1, 2,  -1 );
	jump->SetAnimIntervals( 0.2f, 0.4f, 0.6f, -1.0f );
	jump->SetAnimMode( Animation::ANMD_STOPATEND );
	mAnimSet->AddAnimation( JUMP, jump );

	mAnimSet->SetCurAnimation( WALK );

	// 描画
	mMobDrawer = new SimpleDrawer();
	mMobDrawer->SetAnimation( mAnimSet->GetCurAnimation() );
	mMobDrawer->SetPositionInfo( this );


	// 当たり判定
	AddFrame(0);
	AddCircle(0, SP->GRID_BOGYO, 26, 26, 26);
	SetCurFrame(0);
}

MikataKobito::~MikataKobito(void)
{
	// セットに入ってるｱﾆﾒｰｼｮﾝを開放
	delete mAnimSet->GetAnimation(JUMP);
	delete mAnimSet->GetAnimation(WALK);
	delete mAnimSet->GetAnimation(JUMP);

	delete mAnimSet;
	delete mMobDrawer;
}

/************************************************************//**
*	Move
****************************************************************/
void MikataKobito::Move()
{
	// 当たり判定
	mMapCollider->CollisionRecognition();

	// マップ外に出たら消滅
	DieIfGamenGai();

	switch( mStatus ){

		// 徒歩
		case WALK:
			{
				mSpX = GF("MKOBITOSPX")*(mMuki?1:-1);

				// X秒照らされたら、アイテムを投げる
				if( mLightTimer >= MKOBITO_LTIME ){
					mSpX = 0;
					mLightTimer = 0.0f;
					mStatus = THROW;
					break;
				}

				// 壁にぶつかったら、又は落ちそうになったら、又はY秒たったら反転する
				mWalkTimer += SP->FrameTime;
				if( mMapCollider->GetCollision( MapCollider::MCSD_FRONT ) == SP->CHIP_HIT ||
					mMapCollider->GetCollision( MapCollider::MCSD_DOWN ) == SP->CHIP_NOHIT ||
					mWalkTimer > MKOBITO_WTIME )
				{ 
						mMuki = !mMuki;
						mUrotsuki++;
						mWalkTimer = 0.0f;

						// うろつきがMAXになったらジャンプする
						if( mUrotsuki == GI("MKOBITO_URONUM") ){
							mStatus = JUMP;
							mSpX = 0;
							mSpY = GF("MKOBITOJNPSHOSP");
							mMuki = 0;
							break;
						}
				}
				break;
			}

		// ジャンプ
		case JUMP:
			{
				mAccY = SP->GRAVITY;
				break;
			}

		case THROW:
			{
				// 一回投げるアニメーションが終わったら終了
				if(mAnimSet->GetCurAnimation()->GetLoopCount() == 1){

					// ﾘｾｯﾄして
					mAnimSet->GetCurAnimation()->Rewind();
					mStatus = WALK;
					mLightTimer = 0.0f;

					// ｱｲﾃﾑを投げる
					Item* item = NULL;

					int pick = rand()%3;
					switch( pick ){
						case 0: item = new ItRingo( mX, mY ); break;
						case 1: item = new ItAoRingo( mX, mY ); break;
						case 2: item = new ItKinRingo( mX, mY ); break;
					}
					
					GAMECONTROL->GetMobManager()->Request( item, true );
					item->Launch( GF("ITEMSHOSP"), GF("ITEMSPX"), mMuki );
				}
				break;
			}
	}

	// ｱﾆﾒｰｼｮﾝと描画
	mAnimSet->SetCurAnimation( mStatus );
	mAnimSet->ElapseTime( SP->FrameTime );
	mMobDrawer->SetAnimation( mAnimSet->GetCurAnimation() );
	mMobDrawer->Draw();

	mSpX += mAccX;
	mSpY += mAccY;
	mX	 += mSpX;
	mY	 += mSpY;
}

/************************************************************//**
*	Build
****************************************************************/
void MikataKobito::Build()
{
	mAnimSet->GetAnimation( WALK )->SetGraphicSource( GetWalkGraphic() );
	mAnimSet->GetAnimation( THROW )->SetGraphicSource( GetThrowGraphic() );
	mAnimSet->GetAnimation( JUMP )->SetGraphicSource( GetJumpGraphic() );
}

