#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "Queen.h"
#include "Actions\\ASQueenBase.h"
#include "Actions\\ASQueenWaitForMaku.h"

#include "Actions\\ASQueenChandelierAttack.h"
#include "Actions\\ASQueenTrumpsAttack.h"
#include "Actions\\ASQueenThornAttack.h"
#include "Actions\\ASQueenRodAttack.h"

#include "Actions\\ASQueenAttackInit.h"

#include "..\\..\\..\\Management\\GameControl.h"
#include "..\\..\\..\\Units\\MutekiJikan.h"

class ASQueenChandelierAttack;
class ASQueenTrumpsAttack;

/************************************************************//**
*	女王の残り体力によって攻撃ﾊﾟﾀｰﾝが異なる。
****************************************************************/
void Queen::AddNewStates(ActionState* rPrevState) 
{
	ASQueenBase* prevQueen = dynamic_cast<ASQueenBase*>(rPrevState);

	int powerStage = 0;
	if( prevQueen ) powerStage = prevQueen->GetPowerStage();


	// 威力によって動作と順番が違う
	switch( powerStage ){

		// 威力弱
		case 0:
			{
				// ｽﾃｰﾄの初期化
				ASQueenBase* chandelier = new ASQueenAttackInit<ASQueenChandelierAttack>();
				ASQueenBase* trumps = new ASQueenAttackInit<ASQueenTrumpsAttack>();
				ASQueenBase* thorn = new ASQueenAttackInit<ASQueenThornAttack<true>>();

				// ｷｭｰに追加
				chandelier->BuildState( rPrevState, this );
				QueueAction( chandelier );
				QueueAction( trumps );
				QueueAction( thorn );
				break;
			}

		// 威力中
		case 1:
			{
				// ｽﾃｰﾄの初期化
				ASQueenBase* chandelier = new ASQueenAttackInit<ASQueenChandelierAttackStrong>();
				ASQueenBase* trumps = new ASQueenAttackInit<ASQueenTrumpsAttack>();
				ASQueenBase* thorn = new ASQueenAttackInit<ASQueenThornAttackStrong<true>>();
				ASQueenBase* rod = new ASQueenAttackInit<ASQueenRodAttack>();

				// ｷｭｰに追加
				chandelier->BuildState( rPrevState, this );
				QueueAction( chandelier );
				QueueAction( trumps );
				QueueAction( thorn );
				QueueAction( rod );

				break;
			}

		// 威力強
		case 2:
			{
				// ｽﾃｰﾄの初期化
				ASQueenBase* chandelier = new ASQueenAttackInit<ASQueenChandelierAttackStrong>();
				ASQueenBase* trumps = new ASQueenAttackInit<ASQueenTrumpsAttack>();
				ASQueenBase* thorn = new ASQueenAttackInit<ASQueenThornAttackStrong<true>>();
				ASQueenBase* rod = new ASQueenAttackInit<ASQueenRodAttackStrong>();

				// ｷｭｰに追加
				QueueAction( chandelier );
				QueueAction( trumps );
				QueueAction( thorn );
				QueueAction( rod );
				ShuffleActions();

				ASQueenBase* nextAction = dynamic_cast<ASQueenBase*>(GetFirstState());
				nextAction->BuildState(rPrevState, this);
				break;
			}
	}

	
}

/************************************************************//**
*	@see Queen::AddNewStates
*	まず、幕が上がってくるのを待機
****************************************************************/
void Queen::AddInitStates(int rX, int rY) {
	ActionState* initAction = new ASQueenWaitForMaku(false);

	// ｽﾃｰﾄの初期化
	initAction->BuildState( GI("QUEEN_STARTX"), GI("QUEEN_STARTY"), this );

	// ｷｭｰに追加
	QueueAction( initAction );
}


/************************************************************//**
*	ｱﾙﾌｧ値の取得方法
****************************************************************/
float Queen::GetAlpha(){
	verify(!mStates.empty());

	ASQueenBase* back = dynamic_cast<ASQueenBase*>(mStates.back());

	if( back )
		return (back->GetMutekiJikan()->IsMuteki())?0.5f:1.0f;
	else return 1.0f;
}
