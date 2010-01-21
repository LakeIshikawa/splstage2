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
*@•W€ºÝ½Ä×¸À
****************************************************************/
TrumpSoldier::TrumpSoldier(int rX, int rY)
{
	TRUMPHEISP = GF("TRUMPHEISP");
	TRUMPHEIHANI = GI("TRUMPHEIHANI");

	// ˆÊ’u
	mSizeX = GI("TRUMPHEISX");
	mSizeY = GI("TRUMPHEISY");

	mX = rX;
	mY = rY - mSizeY;
	mMuki = rand()%2;

	// ‰Šú‰»
	mStatus = ST_WALK;

	// “–‚½‚è”»’è
	AddFrame(FR_NONE);
	AddRect(FR_NONE, SP->GRID_BOGYO, 77, 98, 109, 207);
	
	AddFrame(FR_ATTACK);
	AddRect(FR_ATTACK, SP->GRID_KOUGEKI, 0, 134, 181, 159);
	AddRect(FR_ATTACK, SP->GRID_BOGYO, 131, 82, 168, 205);

	AddTarget( GAMECONTROL->GetJiki() );

	GAMECONTROL->GetMobManager()->AddAsTargetAllOf<Thorn>(this);
	GAMECONTROL->GetMobManager()->AddAsTargetAllOf<Heart>(this);

	// Ï¯Ìß‚Æ‚Ì“–‚½‚è
	mMapCollider = new PointMapCollider(this);
	mMapCollider->AddCollisionPoint( MapCollider::MCSD_DOWN, 52, 205 );
	mMapCollider->AddCollisionPoint( MapCollider::MCSD_FRONT, 120, 150 );

	// ±ÆÒ°¼®Ý
	mAnimSet = new AnimationSet();

	// •`‰æ
	mSDrawer = new SimpleDrawer();

	// ”»’è•`‰æ
	mDrawer = new CollisionDrawer();
}

/************************************************************//**
*@Ý’è’è”‚ð“Ç‚Ýž‚Þ
****************************************************************/
void TrumpSoldier::Build()
{
	// •à‚­
	Animation* walk = new Animation();
	walk->SetGraphicSource( GetWalkGraphic() );
	walk->SetAnimData( 0, 1, 2, 1, 0, 3, 4, 3, -1 );
	walk->SetAnimIntervals( 0.2f, 0.4f, 0.6f, 0.8f, 1.0f, 1.2f, 1.4f, 1.6f, -1.0f );
	walk->SetAnimMode(Animation::ANMD_LOOP);
	mAnimSet->AddAnimation(AN_WALK, walk);

	// UŒ‚
	Animation* attack = new Animation();
	attack->SetGraphicSource( GetAttackGraphic() );
	attack->SetAnimData( 0, 1, 2, -1 );
	attack->SetAnimIntervals( 0.2f, 0.4f, 0.6f, -1.0f );
	attack->SetAnimMode(Animation::ANMD_STOPATEND);
	mAnimSet->AddAnimation(AN_ATTACK, attack);

	// Žh‚·
	Animation* sasu = new Animation();
	sasu->SetGraphicSource( GetSasuGraphic() );
	sasu->SetAnimData( 0, 1, 0, -1 );
	sasu->SetAnimIntervals( 0.2f, 0.4f, 0.6f, -1.0f );
	sasu->SetAnimMode(Animation::ANMD_STOPATEND);
	mAnimSet->AddAnimation(AN_SASU, sasu);

	// ˆø‚­
	Animation* hiku = new Animation();
	hiku->SetGraphicSource( GetAttackGraphic() );
	hiku->SetAnimData( 2, 1, 0, -1 );
	hiku->SetAnimIntervals( 0.2f, 0.4f, 0.6f, -1.0f );
	hiku->SetAnimMode(Animation::ANMD_STOPATEND);
	mAnimSet->AddAnimation(AN_HIKU, hiku);

	// Ž€‚Ê
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
*	1ÌÚ°Ñˆ—
****************************************************************/
void TrumpSoldier::Move()
{
	// Ï¯Ìß“–‚½‚è
	mMapCollider->CollisionRecognition();

	// ‹““®
	switch( mStatus ){

		// •à‚­
		case ST_WALK:
			{
				// ’¼i‚Å•à‚­
				mSpX = TRUMPHEISP * (mMuki?1:-1);

				// •Ç‚É‚æ‚é”½“]
				KabeHanten();
				// —Ž‰º
				Fall();			

				// ËÛ²Ý‚É‹ß‚Ã‚¢‚½‚çUŒ‚‚·‚é
				int jx = GAMECONTROL->GetJiki()->GetAtHtPointX();
				int jy = GAMECONTROL->GetJiki()->GetAtHtPointY();

				// ----Ž©‹@‚ÌˆÊ’u‚ðŠm”F
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
				//! —Ž‰º
				Fall();

				mSpX = 0;

				// ±ÆÒ°¼®Ý‚ªI‚í‚é‚Ü‚Å‘Ò‚Â
				if( mAnimSet->GetCurAnimationIdx() == AN_ATTACK && mAnimSet->GetCurAnimation()->GetLoopCount() >= 1 ){
					// Žh‚·
					mAnimSet->GetCurAnimation()->Rewind();
					mAnimSet->SetCurAnimation(AN_SASU);
					SetCurFrame( FR_ATTACK );
				}
				else if( mAnimSet->GetCurAnimationIdx() == AN_SASU && mAnimSet->GetCurAnimation()->GetLoopCount() >= 1 ){
					// ˆø‚­
					mAnimSet->GetCurAnimation()->Rewind();
					mAnimSet->SetCurAnimation( AN_HIKU );
					SetCurFrame( FR_NONE );
				}
				else if( mAnimSet->GetCurAnimationIdx() == AN_HIKU && mAnimSet->GetCurAnimation()->GetLoopCount() >= 1 ){
					// •à‚«ÄŠJ
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

	// ˆÚ“®
	mSpY += mAccY;
	mX += mSpX;
	mY += mSpY;

	// •`‰æ
	mAnimSet->ElapseTime( SP->FrameTime );
	mSDrawer->SetAnimation( mAnimSet->GetCurAnimation() );
	Draw();

	mDrawer->SetCollision(GetCurFrame());
}

/************************************************************//**
*	•`‰æ
****************************************************************/
void TrumpSoldier::Draw()
{
	mSDrawer->Draw();
	mDrawer->Draw();
}

/************************************************************//**
*	“–‚½‚è”»’è‚Ì‰ž“š
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
	// ËÛ²Ý
	if( jiki) {
		if( (rOpGroupId == SP->GRID_BOGYO) && mStatus != ST_DIE){
			jiki->InflictDamage();
		}
	}
}

/************************************************************//**
*	Ž€‚Ê
****************************************************************/
void TrumpSoldier::Die()
{
	if( mStatus != ST_DIE ){
		mStatus = ST_DIE;
		mAnimSet->SetCurAnimation( AN_DIE );
		SetCurFrame( FR_NONE );

		// ËÛ²Ý‚ÌˆÊ’u‚É‚æ‚Á‚ÄxŽ²‚Ì‘¬“x‚ðŒˆ‚ß‚é
		mSpX = -GF("SHINIPATT_SPX");
		Jiki* jiki = GAMECONTROL->GetJiki();
		if( jiki->GetAtHtPointX() < mX+mSizeX/2)
			mSpX *= -1;
	
		mSpY = -GF("SHINIPATT_SHOSP");
		mAccY = SP->GRAVITY;	
	}
}


/************************************************************//**
*	•Ç‚É‚Ô‚Â‚©‚Á‚½‚ç”½“]‚·‚é
****************************************************************/
void TrumpSoldier::KabeHanten()
{
	// •Ç‚É‚Ô‚Â‚©‚Á‚½‚ç”½“]
	if( mMapCollider->GetCollision( MapCollider::MCSD_FRONT ) == SP->CHIP_GMNGAILT || 
		mMapCollider->GetCollision( MapCollider::MCSD_FRONT ) == SP->CHIP_GMNGAIRT || 
		mMapCollider->GetCollision( MapCollider::MCSD_FRONT ) == SP->CHIP_HIT )
	{
		mMuki = !mMuki;
	}
}


/************************************************************//**
*	’n–Ê‚ª‚È‚©‚Á‚½‚ç—Ž‚¿‚é
****************************************************************/
void TrumpSoldier::Fall()
{
	// °‚ª‚È‚©‚Á‚½‚ç—Ž‚¿‚é
	if( mMapCollider->GetCollision( MapCollider::MCSD_DOWN ) == SP->CHIP_NOHIT  || 
		mMapCollider->GetCollision( MapCollider::MCSD_DOWN ) == SP->CHIP_GMNGAIDN )
		mAccY = SP->GRAVITY;
	else {
		mAccY = 0;
		mSpY = 0;
	}

	// ‰æ–Ê‚Ì‰º‚És‚Á‚½‚çŽ€‚Ê
	if( mMapCollider->GetCollision( MapCollider::MCSD_DOWN ) == SP->CHIP_GMNGAIDN ){
		DieIfGamenGai();
	}
}