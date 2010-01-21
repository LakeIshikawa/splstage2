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
*�@�W���ݽ�׸�
****************************************************************/
TrumpSoldier::TrumpSoldier(int rX, int rY)
{
	TRUMPHEISP = GF("TRUMPHEISP");
	TRUMPHEIHANI = GI("TRUMPHEIHANI");

	// �ʒu
	mSizeX = GI("TRUMPHEISX");
	mSizeY = GI("TRUMPHEISY");

	mX = rX;
	mY = rY - mSizeY;
	mMuki = rand()%2;

	// ������
	mStatus = ST_WALK;

	// �����蔻��
	AddFrame(FR_NONE);
	AddRect(FR_NONE, SP->GRID_BOGYO, 77, 98, 109, 207);
	
	AddFrame(FR_ATTACK);
	AddRect(FR_ATTACK, SP->GRID_KOUGEKI, 0, 134, 181, 159);
	AddRect(FR_ATTACK, SP->GRID_BOGYO, 131, 82, 168, 205);

	AddTarget( GAMECONTROL->GetJiki() );

	GAMECONTROL->GetMobManager()->AddAsTargetAllOf<Thorn>(this);
	GAMECONTROL->GetMobManager()->AddAsTargetAllOf<Heart>(this);

	// ϯ�߂Ƃ̓�����
	mMapCollider = new PointMapCollider(this);
	mMapCollider->AddCollisionPoint( MapCollider::MCSD_DOWN, 52, 205 );
	mMapCollider->AddCollisionPoint( MapCollider::MCSD_FRONT, 120, 150 );

	// ��Ұ���
	mAnimSet = new AnimationSet();

	// �`��
	mSDrawer = new SimpleDrawer();

	// ����`��
	mDrawer = new CollisionDrawer();
}

/************************************************************//**
*�@�ݒ�萔��ǂݍ���
****************************************************************/
void TrumpSoldier::Build()
{
	// ����
	Animation* walk = new Animation();
	walk->SetGraphicSource( GetWalkGraphic() );
	walk->SetAnimData( 0, 1, 2, 1, 0, 3, 4, 3, -1 );
	walk->SetAnimIntervals( 0.2f, 0.4f, 0.6f, 0.8f, 1.0f, 1.2f, 1.4f, 1.6f, -1.0f );
	walk->SetAnimMode(Animation::ANMD_LOOP);
	mAnimSet->AddAnimation(AN_WALK, walk);

	// �U��
	Animation* attack = new Animation();
	attack->SetGraphicSource( GetAttackGraphic() );
	attack->SetAnimData( 0, 1, 2, -1 );
	attack->SetAnimIntervals( 0.2f, 0.4f, 0.6f, -1.0f );
	attack->SetAnimMode(Animation::ANMD_STOPATEND);
	mAnimSet->AddAnimation(AN_ATTACK, attack);

	// �h��
	Animation* sasu = new Animation();
	sasu->SetGraphicSource( GetSasuGraphic() );
	sasu->SetAnimData( 0, 1, 0, -1 );
	sasu->SetAnimIntervals( 0.2f, 0.4f, 0.6f, -1.0f );
	sasu->SetAnimMode(Animation::ANMD_STOPATEND);
	mAnimSet->AddAnimation(AN_SASU, sasu);

	// ����
	Animation* hiku = new Animation();
	hiku->SetGraphicSource( GetAttackGraphic() );
	hiku->SetAnimData( 2, 1, 0, -1 );
	hiku->SetAnimIntervals( 0.2f, 0.4f, 0.6f, -1.0f );
	hiku->SetAnimMode(Animation::ANMD_STOPATEND);
	mAnimSet->AddAnimation(AN_HIKU, hiku);

	// ����
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
*	1�ڰя���
****************************************************************/
void TrumpSoldier::Move()
{
	// ϯ�ߓ�����
	mMapCollider->CollisionRecognition();

	// ����
	switch( mStatus ){

		// ����
		case ST_WALK:
			{
				// ���i�ŕ���
				mSpX = TRUMPHEISP * (mMuki?1:-1);

				// �ǂɂ�锽�]
				KabeHanten();
				// ����
				Fall();			

				// �۲݂ɋ߂Â�����U������
				int jx = GAMECONTROL->GetJiki()->GetAtHtPointX();
				int jy = GAMECONTROL->GetJiki()->GetAtHtPointY();

				// ----���@�̈ʒu���m�F
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
				//! ����
				Fall();

				mSpX = 0;

				// ��Ұ��݂��I���܂ő҂�
				if( mAnimSet->GetCurAnimationIdx() == AN_ATTACK && mAnimSet->GetCurAnimation()->GetLoopCount() >= 1 ){
					// �h��
					mAnimSet->GetCurAnimation()->Rewind();
					mAnimSet->SetCurAnimation(AN_SASU);
					SetCurFrame( FR_ATTACK );
				}
				else if( mAnimSet->GetCurAnimationIdx() == AN_SASU && mAnimSet->GetCurAnimation()->GetLoopCount() >= 1 ){
					// ����
					mAnimSet->GetCurAnimation()->Rewind();
					mAnimSet->SetCurAnimation( AN_HIKU );
					SetCurFrame( FR_NONE );
				}
				else if( mAnimSet->GetCurAnimationIdx() == AN_HIKU && mAnimSet->GetCurAnimation()->GetLoopCount() >= 1 ){
					// �����ĊJ
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

	// �ړ�
	mSpY += mAccY;
	mX += mSpX;
	mY += mSpY;

	// �`��
	mAnimSet->ElapseTime( SP->FrameTime );
	mSDrawer->SetAnimation( mAnimSet->GetCurAnimation() );
	Draw();

	mDrawer->SetCollision(GetCurFrame());
}

/************************************************************//**
*	�`��
****************************************************************/
void TrumpSoldier::Draw()
{
	mSDrawer->Draw();
	mDrawer->Draw();
}

/************************************************************//**
*	�����蔻��̉���
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
	// �۲�
	if( jiki) {
		if( (rOpGroupId == SP->GRID_BOGYO) && mStatus != ST_DIE){
			jiki->InflictDamage();
		}
	}
}

/************************************************************//**
*	����
****************************************************************/
void TrumpSoldier::Die()
{
	if( mStatus != ST_DIE ){
		mStatus = ST_DIE;
		mAnimSet->SetCurAnimation( AN_DIE );
		SetCurFrame( FR_NONE );

		// �۲݂̈ʒu�ɂ����x���̑��x�����߂�
		mSpX = -GF("SHINIPATT_SPX");
		Jiki* jiki = GAMECONTROL->GetJiki();
		if( jiki->GetAtHtPointX() < mX+mSizeX/2)
			mSpX *= -1;
	
		mSpY = -GF("SHINIPATT_SHOSP");
		mAccY = SP->GRAVITY;	
	}
}


/************************************************************//**
*	�ǂɂԂ������甽�]����
****************************************************************/
void TrumpSoldier::KabeHanten()
{
	// �ǂɂԂ������甽�]
	if( mMapCollider->GetCollision( MapCollider::MCSD_FRONT ) == SP->CHIP_GMNGAILT || 
		mMapCollider->GetCollision( MapCollider::MCSD_FRONT ) == SP->CHIP_GMNGAIRT || 
		mMapCollider->GetCollision( MapCollider::MCSD_FRONT ) == SP->CHIP_HIT )
	{
		mMuki = !mMuki;
	}
}


/************************************************************//**
*	�n�ʂ��Ȃ������痎����
****************************************************************/
void TrumpSoldier::Fall()
{
	// �����Ȃ������痎����
	if( mMapCollider->GetCollision( MapCollider::MCSD_DOWN ) == SP->CHIP_NOHIT  || 
		mMapCollider->GetCollision( MapCollider::MCSD_DOWN ) == SP->CHIP_GMNGAIDN )
		mAccY = SP->GRAVITY;
	else {
		mAccY = 0;
		mSpY = 0;
	}

	// ��ʂ̉��ɍs�����玀��
	if( mMapCollider->GetCollision( MapCollider::MCSD_DOWN ) == SP->CHIP_GMNGAIDN ){
		DieIfGamenGai();
	}
}