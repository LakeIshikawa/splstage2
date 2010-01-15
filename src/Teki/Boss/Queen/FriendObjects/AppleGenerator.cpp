#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "AppleGenerator.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\..\\Item\\PickUpEffect.h"
#include "..\\..\\..\\..\\Jiki\\Jiki.h"

/************************************************************//**
*�@�ݒ�萔��ǂݍ���
****************************************************************/
AppleGenerator::AppleGenerator(int rX, int rY)
{
	STD_FADEIN_SP = GF("STD_FADEIN_SP");
	APPLE_BEFOREAPP = GF("APPLE_BEFOREAPP");
	APPLE_BEFOREDISAPP1 = GF("APPLE_BEFOREDISAPP1");
	APPLE_BEFOREDISAPP2 = GF("APPLE_BEFOREDISAPP2");

	// �ʒu
	mSizeX = GI("ITEMSX");
	mSizeY = GI("ITEMSY");

	mX = rX;
	mY = rY;
	mMuki = 0;
	
	// �����蔻��
	AddFrame(0);
	AddCircle(0, SP->GRID_BOGYO, mSizeX/2, mSizeY/2, mSizeX/2);
	AddTarget(GAMECONTROL->GetJiki());

	// ������
	mStatus = ACTIVE;
	mAlpha = 1.0f;
	mTimer = 0.0f;
	mStage = 0;
}

/************************************************************//**
*	1�ڰя���
****************************************************************/
void AppleGenerator::Move()
{
	
	switch( mStatus ){

		// ̪��޲�
		case APPEAR:
			mAlpha += STD_FADEIN_SP;
			if( mAlpha >= 1.0f ){
				mAlpha = 1.0f;
				mStatus = ACTIVE;
			}
			break;

		// �ҋ@
		case ACTIVE:
			WAIT_TIMER(mTimer, mStage?APPLE_BEFOREDISAPP2:APPLE_BEFOREDISAPP1)
				mStatus = DISAPPEAR;
			mFlashNum = 0;
			mFlashFl = false;
			WAIT_END
			break;

		// ̪��ޱ��
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

		// �ҋ@
		case INACTIVE:
			mAlpha = 0.0f;
			WAIT_TIMER(mTimer, APPLE_BEFOREAPP)
				mStatus = APPEAR;
			WAIT_END			
			break;
		
	}

	// �`��
	Draw();
}

/************************************************************//**
*	�`��
****************************************************************/
void AppleGenerator::Draw()
{
	DX_DRAWALPHA("graphics\\item\\Apple_a.png", 
		mX, mY, 0, 0, mSizeX, mSizeY, mAlpha);

}

/************************************************************//**
*	�����蔻��̉���
****************************************************************/
void AppleGenerator::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	// �۲�
	if( (jiki && rOpGroupId == SP->GRID_BOGYO  || rOpGroupId == SP->GRID_KOUGEKI)  &&
		mStatus != INACTIVE )
	{
		// ���т�������
		mStatus = INACTIVE;
		mTimer = 0.0f;
		mFlashNum = 0;
		mFlashFl = false;
		// ��
		jiki->RestoreEmpacy(1);
		// ���o
		GAMECONTROL->GetMobManager()->Request( 
			new PickUpEffect( "graphics\\item\\enpathy_up.png" ), true );
	}
}
