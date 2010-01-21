#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ASOokamiBlowAttackFaint.h"
#include "ASOokamiBlowAttackHitback.h"
#include "ASOokamiJumpingDeath.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Animation\\Animation.h"
#include "..\\..\\..\\Light\\Light.h"


/************************************************************//**
*	ｱﾆﾒｰｼｮﾝを作り出す
****************************************************************/
void ASOokamiBlowAttackFaint::BuildAnimation(ActionState* rPrevState) 
{
	mAnimation = Animation::ParseFromFile( "data\\animdata\\ookami\\BlowAttackFaint.txt" );
}

/************************************************************//**
*	狼の標準の当たり判定の応答
****************************************************************/
void ASOokamiBlowAttackFaint::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) 
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);

	// ﾋﾛｲﾝ
	if( jiki && !mMutekiJikan->IsMuteki() ){

		// ﾋﾛｲﾝの攻撃、狼の防御
		if( rOpGroupId == SP->GRID_KOUGEKI && rThisGroupId == SP->GRID_BOGYO ){
			// HPを削る
			mHp--;

			// 死亡の場合
			if( mHp <= 0 ) {
				// 死ぬ
				mParent->BreakInActionNoResume( new ASOokamiJumpingDeath() );
			}
			// ﾀﾞﾒｰｼﾞだけの場合
			else{
				// 狼が痛む
				mParent->BreakInActionNoResume( new ASOokamiBlowAttackHitback() ); // TODO: OokamiDamage
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
*	OnEnter
****************************************************************/
void ASOokamiBlowAttackFaint::OnEnter() 
{
	// SE
	GAMECONTROL->GetSoundController()->LoopSE("audio\\se\\se_boss2_bress_out.wav");
}

/************************************************************//**
*	画面に入って終わり
****************************************************************/
bool ASOokamiBlowAttackFaint::Update() {
	// 終了条件
	return mAnimation->GetLoopCount() == 6;
}

/************************************************************//**
*	次のｽﾃｰﾄに移る
****************************************************************/
void ASOokamiBlowAttackFaint::OnExit() 
{
	// ここで家が次の強風動作でちゃんと作り直されるよう、
	// のﾊﾝﾄﾞﾙを開放する
	rog = NULL;
	straw = NULL;
	brick = NULL;

	// SE
	GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_boss2_bress_out.wav");
}
