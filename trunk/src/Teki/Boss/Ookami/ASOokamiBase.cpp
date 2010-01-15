#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Ookami.h"
#include "ASOokamiBase.h"
#include "ASOokamiDamage.h"
#include "ASOokamiJumpingDeath.h"
#include "..\\..\\..\\Collision\\Collision.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Animation\\Animation.h"
#include "..\\..\\..\\Mob\\MobDrawer\\SimpleDrawer.h"



/************************************************************//**
*	狼の所属物を開放する
****************************************************************/
ASOokamiBase::~ASOokamiBase() 
{
	if( mMutekiJikan ) delete mMutekiJikan;
}

/************************************************************//**
*	狼の標準の当たり判定を作り出す
****************************************************************/
void ASOokamiBase::BuildCollision(ActionState* rPrevState) 
{
	mCollision = new Collision(mParent);	// 当たり判定
	mCollision->AddRect(SP->GRID_BOGYO, 38, 32, 75, 131);
}

/************************************************************//**
*	狼の標準のﾏｯﾌﾟあたり判定
****************************************************************/
void ASOokamiBase::BuildMapCollider(ActionState* rPrevState) 
{
	mMapCollider = NULL; // ﾏｯﾌﾟあたり判定なし
}

/************************************************************//**
*	狼の標準の描画方法を示すｵﾌﾞｼﾞｪｸﾄの作成
****************************************************************/
void ASOokamiBase::BuildMobDrawer(ActionState* rPrevState) 
{
	mMobDrawer = new SimpleDrawer();
	((SimpleDrawer*)mMobDrawer)->SetAnimation(mAnimation);
	((SimpleDrawer*)mMobDrawer)->SetPositionInfo(mParent);
	((SimpleDrawer*)mMobDrawer)->SetAlphaSrc((Ookami*)mParent);
}


/************************************************************//**
*	狼の初期位置を固定にする
****************************************************************/
void ASOokamiBase::BuildPosInfo(ActionState* rPrevState) 
{
	ActionState::BuildPosInfo(rPrevState);
	mFrameSizeX = GI("OOKAMI_SX");
	mFrameSizeY = GI("OOKAMI_SY");

}

/************************************************************//**
*	狼の情報のﾋﾞﾙﾄﾞ
****************************************************************/
void ASOokamiBase::BuildOtherInfo(ActionState* rPrevState) 
{
	ASOokamiBase* prev_state = dynamic_cast<ASOokamiBase*>(rPrevState);

	// 初期ｽﾃｰﾄの場合
	if( !prev_state ){
		mMutekiJikan = new MutekiJikan();
		mMutekiJikan->SetMutekiTime(GF("OOKAMI_MTKTIME"));
		mParent->AddThread(mMutekiJikan);

		// HP
		mHp = GI("OOKAMI_HP");
	}

	// 普段はｺﾋﾟｰ
	else{
		mParent->RemoveThread( prev_state->GetMutekiJikan() );
		mMutekiJikan = prev_state->GetMutekiJikan()->Clone();
		mParent->AddThread( mMutekiJikan );

		// HP
		mHp = prev_state->mHp;

		// 家
		straw = prev_state->straw;
		rog = prev_state->rog;
		brick = prev_state->brick;
	}

	
	// 設定定数
	OOKAMI_STARTX		= GI("OOKAMI_STARTX");
	OOKAMI_STARTY		= GI("OOKAMI_STARTY");
	OOKAMI_STRATKSPX	= GF("OOKAMI_STRATKSPX");
	OOKAMI_JMPSHOSOKUY	= GF("OOKAMI_JMPSHOSOKUY");
	OOKAMI_ENTERRX		= GI("OOKAMI_ENTERRX");
	OOKAMI_ENTERLX		= GI("OOKAMI_ENTERLX");
}

/************************************************************//**
*	狼の標準の当たり判定の応答
****************************************************************/
void ASOokamiBase::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	// ﾋﾛｲﾝ
	if( jiki && !mMutekiJikan->IsMuteki() ){

		// ﾋﾛｲﾝの攻撃、狼の防御
		if( rOpGroupId == SP->GRID_KOUGEKI && rThisGroupId == SP->GRID_BOGYO ){
			// HPを削る
			mHp--;

			// ヒロインにいいことをプレゼントする
			jiki->IncreaseTensEmpa();
			jiki->IncrementChain();

			// 死亡の場合
			if( mHp <= 0 ) {
				// 死ぬ
				mParent->BreakInActionNoResume( new ASOokamiJumpingDeath() );
			}

			// ﾀﾞﾒｰｼﾞを食らうだけの場合
			else{
				// 狼が痛む
				mParent->BreakInAction( new ASOokamiDamage() ); // TODO: OokamiDamage
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
MutekiJikan* ASOokamiBase::GetMutekiJikan(){
	return mMutekiJikan;
}
