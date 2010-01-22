#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "..\\Queen.h"
#include "ASQueenBase.h"

#include "..\\..\\..\\..\\Collision\\Collision.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\..\\Animation\\Animation.h"
#include "..\\..\\..\\..\\Mob\\MobDrawer\\SimpleDrawer.h"
#include "..\\..\\..\\..\\Light\\Light.h"

#include "..\\..\\..\\TrumpSoldier.h"
#include "..\\FriendObjects\\Thorn.h"

#include "ASQueenDamage.h"


/************************************************************//**
*	���������J������
****************************************************************/
ASQueenBase::~ASQueenBase() 
{
	if( mMutekiJikan ) delete mMutekiJikan;
}

/************************************************************//**
*	��Ұ��݂̍쐬
****************************************************************/
void ASQueenBase::BuildAnimation(ActionState* rPrevState)
{
	mAnimation = Animation::ParseFromFile( "data\\animdata\\queen\\Stand.txt" );
}

/************************************************************//**
*	�W���̓����蔻������o��
****************************************************************/
void ASQueenBase::BuildCollision(ActionState* rPrevState) 
{
	mCollision = new Collision(mParent);	// �����蔻��
	mCollision->AddRect(SP->GRID_BOGYO, 44, 50, 77, 142);
}

/************************************************************//**
*	�W����ϯ�߂����蔻��
****************************************************************/
void ASQueenBase::BuildMapCollider(ActionState* rPrevState) 
{
	mMapCollider = NULL; // ϯ�߂����蔻��Ȃ�
}

/************************************************************//**
*	�W���̕`����@��������޼ު�Ă̍쐬
****************************************************************/
void ASQueenBase::BuildMobDrawer(ActionState* rPrevState) 
{
	mMobDrawer = new SimpleDrawer();
	((SimpleDrawer*)mMobDrawer)->SetAnimation(mAnimation);
	((SimpleDrawer*)mMobDrawer)->SetPositionInfo(mParent);
	((SimpleDrawer*)mMobDrawer)->SetAlphaSrc((Queen*)mParent);
}

/************************************************************//**
*	�����ʒu���Œ�ɂ���
****************************************************************/
void ASQueenBase::BuildPosInfo(ActionState* rPrevState) 
{
	ActionState::BuildPosInfo(rPrevState);
	mFrameSizeX = GI("QUEEN_SX");
	mFrameSizeY = GI("QUEEN_SY");

}

/************************************************************//**
*	�����ʒu���Œ�ɂ���
****************************************************************/
void ASQueenBase::BuildPosInfo(int rX, int rY) 
{
	ActionState::BuildPosInfo(rX, rY);
	mMuki = 0;
	mFrameSizeX = GI("QUEEN_SX");
	mFrameSizeY = GI("QUEEN_SY");
}

/************************************************************//**
*	���������
****************************************************************/
void ASQueenBase::BuildOtherInfo(ActionState* rPrevState) 
{
	ASQueenBase* prev_state = dynamic_cast<ASQueenBase*>(rPrevState);

	// �����ðĂ̏ꍇ
	if( !prev_state ){
		// ���G����
		mMutekiJikan = new MutekiJikan();
		mMutekiJikan->SetMutekiTime(GF("QUEEN_MTKTIME"));
		mParent->AddThread(mMutekiJikan);

		// ��
		mKagami = new Kagami();
		GAMECONTROL->GetMobManager()->Request(mKagami, true);

		// �����ر
		mChandelier = new Chandelier();
		GAMECONTROL->GetMobManager()->Request(mChandelier, true);

		// ۯ��
		mRod1 = NULL;
		mRod2 = NULL;

		// �ݺ޼ު�ڰ�
		mAppleGenerator1 = new AppleGenerator( GI("APPLE_GENLTX"), GI("APPLE_GENY") );
		mAppleGenerator2 = new AppleGenerator( GI("APPLE_GENRTX"), GI("APPLE_GENY") );
		GAMECONTROL->GetMobManager()->Request(mAppleGenerator1, true);
		GAMECONTROL->GetMobManager()->Request(mAppleGenerator2, true);

		// HP
		mHp = GI("QUEEN_HP");

		// �З�
		mPowerStage = 0;
	}

	// ���i�ͺ�߰
	else{
		// ���G����
		mParent->RemoveThread( prev_state->GetMutekiJikan() );
		mMutekiJikan = prev_state->GetMutekiJikan()->Clone();
		mParent->AddThread( mMutekiJikan );

		// ��
		mKagami = prev_state->GetKagami();

		// �����ر
		mChandelier = prev_state->GetChandelier();

		// ۯ��
		mRod1 = prev_state->GetRod1();
		mRod2 = prev_state->GetRod2();

		// �ݺ޼ު�ڰ�
		mAppleGenerator1 = prev_state->GetAppleGenerator1();
		mAppleGenerator2 = prev_state->GetAppleGenerator2();

		// HP
		mHp = prev_state->mHp;

		// �З�
		mPowerStage = prev_state->mPowerStage;
	}
	
	// �ݒ�萔
	QUEEN_STARTX		= GI("QUEEN_STARTX");
	QUEEN_STARTY		= GI("QUEEN_STARTY");
}

/************************************************************//**
*	�З͂ƽð�ނ̘A�g
****************************************************************/
void ASQueenBase::OnExit(){
	bool reset = false;

	switch( mPowerStage ){
		case 0:	
			if( mHp < 7 ) 
				mPowerStage = 1, reset = true;
			break;
		case 1:
			if( mHp < 4 ) 
				mPowerStage = 2, reset = true;
			break;
		case 2:	break;
	}

	if( reset ){
		mParent->RemoveAllActions(this);
	}
}

/************************************************************//**
*	�W���̓����蔻��̉���
****************************************************************/
void ASQueenBase::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	// �۲�
	if( jiki && !mMutekiJikan->IsMuteki() ){

		// �۲݂̍U���A�h��
		if( rOpGroupId == SP->GRID_KOUGEKI && rThisGroupId == SP->GRID_BOGYO ){
			if( mHp-1 >0 ) 
				mParent->BreakInAction(new ASQueenDamage(this));
			else
			{
				// ����
				mKagami->SetHibiStage(3);
				GAMECONTROL->GetJiki()->SetSuperPause();
				GAMECONTROL->GetJiki()->DisableCollision();
				GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();

				GAMECONTROL->GetMobManager()->RemoveAll<TrumpSoldier>();
				GAMECONTROL->GetMobManager()->RemoveAll<Thorn>();

				mParent->RemoveAllActions(this);
				mParent->BreakInActionNoResume( new ASQueenJumpingDeath() );		
			}
		}
		// �۲݂̖h��
		else if( rOpGroupId == SP->GRID_BOGYO ){
			// �۲݂��ɂ�
			jiki->InflictDamage();
		}
	}
}

/************************************************************//**
*	���G���Ԃ̎擾
****************************************************************/
MutekiJikan* ASQueenBase::GetMutekiJikan(){
	return mMutekiJikan;
}

/************************************************************//**
*	���̎擾
****************************************************************/
Kagami* ASQueenBase::GetKagami(){
	return mKagami;
}

/************************************************************//**
*	�����ر�̎擾
****************************************************************/
Chandelier* ASQueenBase::GetChandelier(){
	return mChandelier;
}

/************************************************************//**
*	ۯ�ނ̎擾
****************************************************************/
Rod* ASQueenBase::GetRod1(){
	return mRod1;
}

/************************************************************//**
*	ۯ�ނ̎擾
****************************************************************/
Rod* ASQueenBase::GetRod2(){
	return mRod2;
}

/************************************************************//**
*	�ݺ޼ު�ڰ��̎擾
****************************************************************/
AppleGenerator* ASQueenBase::GetAppleGenerator1(){
	return mAppleGenerator1;
}

/************************************************************//**
*	�ݺ޼ު�ڰ��̎擾
****************************************************************/
AppleGenerator* ASQueenBase::GetAppleGenerator2(){
	return mAppleGenerator2;
}

/************************************************************//**
*	�З͂̎擾
****************************************************************/
int ASQueenBase::GetPowerStage(){
	return mPowerStage;
}

