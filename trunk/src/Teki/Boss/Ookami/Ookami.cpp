#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Ookami.h"
#include "ASOokamiBase.h"
#include "ASOokamiStraightAttack.h"
#include "ASOokamiJumpAttack.h"
#include "ASOokamiBlowAttackEntering.h"
#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\BossShareActions\\ASWaitForMaku.h"
#include "..\\..\\..\\Units\\MutekiJikan.h"

bool random(pair<ASOokamiBase*,int>, pair<ASOokamiBase*,int>);

/************************************************************//**
*	狼がﾗﾝﾀﾞﾑな順番で三つのｱｸｼｮﾝを繰り返します。
*	0 - 直進攻撃
*	1 - ｼﾞｬﾝﾌﾟ攻撃
*	2 - 家の吹き飛ばし
****************************************************************/
void Ookami::AddNewStates(ActionState* rPrevState) {


	// 拾いﾘｽﾄを作る
	list<pair<ASOokamiBase*, int>> initPick;
	initPick.push_back(pair<ASOokamiStraightAttack*,int>(new ASOokamiStraightAttack(), rand()%10));
	initPick.push_back(pair<ASOokamiJumpAttack*,int>(new ASOokamiJumpAttack(), rand()%10));
	initPick.push_back(pair<ASOokamiBlowAttackEntering*, int>(new ASOokamiBlowAttackEntering(),rand()%10));

	initPick.sort(random);

	for each( pair<ASOokamiBase*, int> ap in initPick ){
		// ｽﾃｰﾄの初期化
		ap.first->BuildState( rPrevState, this );
		// ｷｭｰに追加
		QueueAction( ap.first );
	}
}

/************************************************************//**
*	@see Ookami::AddNewStates
*	まず、幕が上がってくるのを待機
****************************************************************/
void Ookami::AddInitStates(int rX, int rY) {
	ActionState* initAction = new ASWaitForMaku(false);

	// ｽﾃｰﾄの初期化
	initAction->BuildState( GI("OOKAMI_STARTX"), GI("OOKAMI_STARTY"), this );

	// ｷｭｰに追加
	QueueAction( initAction );

	//SE STOP
	GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_boss2_bress_atack.wav");
	GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_boss2_bress_out.wav");
	GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_boss2_bress_tame.wav");
	GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_boss2_move.wav");
	GAMECONTROL->GetSoundController()->StopSE("audio\\se\\se_boss2_house_break.wav");
}


/************************************************************//**
*	ｱﾙﾌｧ値の取得方法
****************************************************************/
float Ookami::GetAlpha(){
	verify(!mStates.empty());

	ASOokamiBase* back = dynamic_cast<ASOokamiBase*>(mStates.back());

	if( back )
		return (back->GetMutekiJikan()->IsMuteki())?0.5f:1.0f;
	else return 1.0f;
}

/************************************************************//**
*	ﾗﾝﾀﾞﾑでｿｰﾄ
****************************************************************/
bool random(pair<ASOokamiBase*, int> a, pair<ASOokamiBase*, int> b)
{
	return a.second > b.second;
}