#include "Tekkyu.h"
#include "..\\Management\\GameControl.h"
#include "..\\MapCollision\\PointMapCollider.h"
#include "TekkyuStand.h"

class AshibaInvisible;
class AshibaMovable;
class AshibaTenbin;

/**
	�W���R���X�g���N�^
*/
Tekkyu::Tekkyu(int rXPx, int rYPx, float rZ, TekkyuStand* rParent)
{
	mParent = rParent;

	// �ݒ�萔
	TEKKYU_SHOMETSUTIME = GF("TEKKYU_SHOMETSUTIME");

	// �ʒu���
	mSizeX = GI("TEKKYUSX");
	mSizeY = GI("TEKKYUSY");

	mX = rXPx;
	mY = rYPx;
	mZ = rZ;

	mAddSpX = 0;
	mAshiba = NULL;

	// ϯ�߂����蔻��
	mMapCollision = new PointMapCollider( this );
	mMapCollision->AddCollisionPoint( MapCollider::MCSD_DOWN, 34, 102 );
	mMapCollision->AddCollisionPoint( MapCollider::MCSD_DOWN, 71, 102 );
	mMapCollision->AddCollisionPoint( MapCollider::MCSD_FRONT, 94, 34 );
	mMapCollision->AddCollisionPoint( MapCollider::MCSD_FRONT, 94, 71 );
	
	// �����蔻��
	AddFrame(0);
	AddCircle(0, SP->GRID_BOGYO, 52, 52, 52);
	AddIndexedRect(0, SP->GRID_BOUND, 0, 20, 10, 84, 94);
	
	AddFrame(1); //����Ȃ�

	// ���ޯ�
	AddTarget(GAMECONTROL->GetJiki());
	GAMECONTROL->GetMobManager()->AddAsTargetAllOf<Tekkyu>(this);
	GAMECONTROL->GetStageManager()->GetCurrentStage()->GetHaichi()->SetAshibaTargets(this);
	SetCurFrame(1);

	// ��]�p
	mAngle = 0.0f;

	// ��̧�l
	mAlpha = 1.0f;

	// �ð��
	mStatus = GENERATE;

	// ������ϰ
	mDieTimer = 0.0f;

	// �����p�̃t���O :UGLY:
	mIsRolling = false;
}

/**
	�W���f�X�g���N�^
*/
Tekkyu::~Tekkyu()
{
}

/************************************************************//**
*	1�ڰя���
****************************************************************/
void Tekkyu::Move()
{
	// ���Œ�
	if( mStatus == DIE ){
		Disappear();
		Draw();
		return;
	}

	// �o����
	if( mStatus == GENERATE ){
		if( mY >= mParent->GetY() ){
			mStatus = FALL;
			SetCurFrame(0); // �����蔻���L����
			// SE
			GAMECONTROL->GetSoundController()->PlaySE("audio\\se\\se_ttekkyuu_hassya.wav");
		}
	}

	// ϯ�߂Ƃ̓����蔻��
	mMapCollision->CollisionRecognition();

	// �n�ʂɓ���������]����
	RollIfHitGround();
	// �]�����Ă���Ȃ��
	if( mStatus == ROLLING ) Kaiten();
	// �e��
	Rebound();
	// ������
	Fall();
	// �����ɂԂ�������Ƃ܂�
	StopIfHitWall();
	// ����
	DieIfStopAndNSec();

	// ϯ�߂��甲�����玀��
	DieIfGamenGai();

	// �͊w
	mSpX += mAccX;
	mSpY += mAccY;
	mX += mSpX + mAddSpX;
	mY += mSpY;

	// ���u�̕`��
	Draw();

	mAddSpX = 0;
}

/************************************************************//**
*	�`��
****************************************************************/
void Tekkyu::Draw()
{
	// �o�����̎�
	int cuty = 0;
	if( mStatus == GENERATE ){
		cuty = mParent->GetY() - mY;
	}

	// �S��
	DX_SCROLL_ROT_DRAWALPHA("graphics\\object\\obj_ag.png", 
		mX, mY+cuty+1, 0, cuty, mSizeX, mSizeY, mAngle, mAlpha);
	// �e
	DX_SCROLL_ROT_DRAWALPHA("graphics\\object\\obj_ag_a.png", 
		mX, mY+cuty+1, 0, cuty, mSizeX, mSizeY, 0.0f, mAlpha);

}

/************************************************************//**
*	�W���̓����蔻��\n
*	
*	\param rCollObject	����������̵�޼ު��(��F�۲�)
*	\param rThisGroupId	��������GROUPID(���X�ɂ���ĈႤ)
*	\param rOpGroupId	����������̵�޼ު�Ă�GROUPID(���X�ɂ���ĈႤ)
*
****************************************************************/
void Tekkyu::CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId)
{

	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);
	Tekkyu* tekkyu = dynamic_cast<Tekkyu*>(rCollObject);
	
	// �۲�
	if( jiki && rOpGroupId == SP->GRID_BOGYO && mStatus!=DIE ){
		jiki->InflictDamage();
	}

	// �S�����m
	if( tekkyu ){
		mSpX = 0;
		mStatus = STOP;
	}
}

/************************************************************//**
*	�n�ʂƂ��������u�Ԃɓ]����n�߂�
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
*	��]����
****************************************************************/
void Tekkyu::Kaiten()
{
	mAngle += mSpX/(mSizeX/2);
	if( mAngle >= D3DX_PI*2 ) mAngle = 0;
}

/************************************************************//**
*	�d�͂̉e���ŁA������B�@ϯ�߂ɂ��������炻���ŐÎ~����B
****************************************************************/
void Tekkyu::Fall()
{
	// ����
	if( IsHittingGround() )
	{
		// �ʒu�C��
		if( !mAshiba) mY = mMapCollision->GetAdjustedPosition( MapCollider::MCSD_DOWN )+1;
	}
	else{
		mAccY = SP->GRAVITY;
	}
}

/************************************************************//**
*	\return �n�ʂɓ������Ă��邩
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
*	�e��
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
*	�u�O�v������������
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
*	����
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
*	���X�ɏ����Ă���
****************************************************************/
void Tekkyu::Disappear()
{
	mAlpha -= 0.02f;
	if( mAlpha < 0.0f ){
		GAMECONTROL->GetMobManager()->Remove(this);
		if( mAshiba ) mAshiba->GetOff(this);

		// ���ׂĂ̓S�����玩���Ƃ������ޯĂ�r������
		GAMECONTROL->GetStageManager()->GetCurrentStage()->
			GetHaichi()->RemoveAshibaTargets( this );
	}

}
