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
*	所属物を開放する
****************************************************************/
ASQueenBase::~ASQueenBase() 
{
	if( mMutekiJikan ) delete mMutekiJikan;
}

/************************************************************//**
*	ｱﾆﾒｰｼｮﾝの作成
****************************************************************/
void ASQueenBase::BuildAnimation(ActionState* rPrevState)
{
	mAnimation = Animation::ParseFromFile( "data\\animdata\\queen\\Stand.txt" );
}

/************************************************************//**
*	標準の当たり判定を作り出す
****************************************************************/
void ASQueenBase::BuildCollision(ActionState* rPrevState) 
{
	mCollision = new Collision(mParent);	// 当たり判定
	mCollision->AddRect(SP->GRID_BOGYO, 44, 50, 77, 142);
}

/************************************************************//**
*	標準のﾏｯﾌﾟあたり判定
****************************************************************/
void ASQueenBase::BuildMapCollider(ActionState* rPrevState) 
{
	mMapCollider = NULL; // ﾏｯﾌﾟあたり判定なし
}

/************************************************************//**
*	標準の描画方法を示すｵﾌﾞｼﾞｪｸﾄの作成
****************************************************************/
void ASQueenBase::BuildMobDrawer(ActionState* rPrevState) 
{
	mMobDrawer = new SimpleDrawer();
	((SimpleDrawer*)mMobDrawer)->SetAnimation(mAnimation);
	((SimpleDrawer*)mMobDrawer)->SetPositionInfo(mParent);
	((SimpleDrawer*)mMobDrawer)->SetAlphaSrc((Queen*)mParent);
}

/************************************************************//**
*	初期位置を固定にする
****************************************************************/
void ASQueenBase::BuildPosInfo(ActionState* rPrevState) 
{
	ActionState::BuildPosInfo(rPrevState);
	mFrameSizeX = GI("QUEEN_SX");
	mFrameSizeY = GI("QUEEN_SY");

}

/************************************************************//**
*	初期位置を固定にする
****************************************************************/
void ASQueenBase::BuildPosInfo(int rX, int rY) 
{
	ActionState::BuildPosInfo(rX, rY);
	mMuki = 0;
	mFrameSizeX = GI("QUEEN_SX");
	mFrameSizeY = GI("QUEEN_SY");
}

/************************************************************//**
*	情報のﾋﾞﾙﾄﾞ
****************************************************************/
void ASQueenBase::BuildOtherInfo(ActionState* rPrevState) 
{
	ASQueenBase* prev_state = dynamic_cast<ASQueenBase*>(rPrevState);

	// 初期ｽﾃｰﾄの場合
	if( !prev_state ){
		// 無敵時間
		mMutekiJikan = new MutekiJikan();
		mMutekiJikan->SetMutekiTime(GF("QUEEN_MTKTIME"));
		mParent->AddThread(mMutekiJikan);

		// 鏡
		mKagami = new Kagami();
		GAMECONTROL->GetMobManager()->Request(mKagami, true);

		// ｼｬﾝﾃﾞﾘｱ
		mChandelier = new Chandelier();
		GAMECONTROL->GetMobManager()->Request(mChandelier, true);

		// ﾛｯﾄﾞ
		mRod1 = NULL;
		mRod2 = NULL;

		// ﾘﾝｺﾞｼﾞｪﾈﾚｰﾀ
		mAppleGenerator1 = new AppleGenerator( GI("APPLE_GENLTX"), GI("APPLE_GENY") );
		mAppleGenerator2 = new AppleGenerator( GI("APPLE_GENRTX"), GI("APPLE_GENY") );
		GAMECONTROL->GetMobManager()->Request(mAppleGenerator1, true);
		GAMECONTROL->GetMobManager()->Request(mAppleGenerator2, true);

		// HP
		mHp = GI("QUEEN_HP");

		// 威力
		mPowerStage = 0;
	}

	// 普段はｺﾋﾟｰ
	else{
		// 無敵時間
		mParent->RemoveThread( prev_state->GetMutekiJikan() );
		mMutekiJikan = prev_state->GetMutekiJikan()->Clone();
		mParent->AddThread( mMutekiJikan );

		// 鏡
		mKagami = prev_state->GetKagami();

		// ｼｬﾝﾃﾞﾘｱ
		mChandelier = prev_state->GetChandelier();

		// ﾛｯﾄﾞ
		mRod1 = prev_state->GetRod1();
		mRod2 = prev_state->GetRod2();

		// ﾘﾝｺﾞｼﾞｪﾈﾚｰﾀ
		mAppleGenerator1 = prev_state->GetAppleGenerator1();
		mAppleGenerator2 = prev_state->GetAppleGenerator2();

		// HP
		mHp = prev_state->mHp;

		// 威力
		mPowerStage = prev_state->mPowerStage;
	}
	
	// 設定定数
	QUEEN_STARTX		= GI("QUEEN_STARTX");
	QUEEN_STARTY		= GI("QUEEN_STARTY");
}

/************************************************************//**
*	威力とｽﾃｰｼﾞの連携
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
*	標準の当たり判定の応答
****************************************************************/
void ASQueenBase::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	// ﾋﾛｲﾝ
	if( jiki && !mMutekiJikan->IsMuteki() ){

		// ﾋﾛｲﾝの攻撃、防御
		if( rOpGroupId == SP->GRID_KOUGEKI && rThisGroupId == SP->GRID_BOGYO ){
			if( mHp-1 >0 ) 
				mParent->BreakInAction(new ASQueenDamage(this));
			else
			{
				// 死ぬ
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
		// ﾋﾛｲﾝの防御
		else if( rOpGroupId == SP->GRID_BOGYO ){
			// ﾋﾛｲﾝが痛む
			jiki->InflictDamage();
		}
	}
}

/************************************************************//**
*	無敵時間の取得
****************************************************************/
MutekiJikan* ASQueenBase::GetMutekiJikan(){
	return mMutekiJikan;
}

/************************************************************//**
*	鏡の取得
****************************************************************/
Kagami* ASQueenBase::GetKagami(){
	return mKagami;
}

/************************************************************//**
*	ｼｬﾝﾃﾞﾘｱの取得
****************************************************************/
Chandelier* ASQueenBase::GetChandelier(){
	return mChandelier;
}

/************************************************************//**
*	ﾛｯﾄﾞの取得
****************************************************************/
Rod* ASQueenBase::GetRod1(){
	return mRod1;
}

/************************************************************//**
*	ﾛｯﾄﾞの取得
****************************************************************/
Rod* ASQueenBase::GetRod2(){
	return mRod2;
}

/************************************************************//**
*	ﾘﾝｺﾞｼﾞｪﾈﾚｰﾀの取得
****************************************************************/
AppleGenerator* ASQueenBase::GetAppleGenerator1(){
	return mAppleGenerator1;
}

/************************************************************//**
*	ﾘﾝｺﾞｼﾞｪﾈﾚｰﾀの取得
****************************************************************/
AppleGenerator* ASQueenBase::GetAppleGenerator2(){
	return mAppleGenerator2;
}

/************************************************************//**
*	威力の取得
****************************************************************/
int ASQueenBase::GetPowerStage(){
	return mPowerStage;
}

