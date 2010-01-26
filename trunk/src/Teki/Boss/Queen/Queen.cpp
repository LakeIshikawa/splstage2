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
*	�����̎c��̗͂ɂ���čU������݂��قȂ�B
****************************************************************/
void Queen::AddNewStates(ActionState* rPrevState) 
{
	ASQueenBase* prevQueen = dynamic_cast<ASQueenBase*>(rPrevState);

	int powerStage = 0;
	if( prevQueen ) powerStage = prevQueen->GetPowerStage();


	// �З͂ɂ���ē���Ə��Ԃ��Ⴄ
	switch( powerStage ){

		// �З͎�
		case 0:
			{
				// �ðĂ̏�����
				ASQueenBase* chandelier = new ASQueenAttackInit<ASQueenChandelierAttack>();
				ASQueenBase* trumps = new ASQueenAttackInit<ASQueenTrumpsAttack>();
				ASQueenBase* thorn1 = new ASQueenAttackInit<ASQueenThornAttack<true>>();
				ASQueenBase* thorn2 = new ASQueenAttackInit<ASQueenThornAttack<false>>();

				// ����ɒǉ�
				chandelier->BuildState( rPrevState, this );
				QueueAction( chandelier );
				QueueAction( trumps );
				QueueAction( thorn1 );
				QueueAction( thorn2 );
				break;
			}

		// �З͒�
		case 1:
			{
				// �ðĂ̏�����
				ASQueenBase* chandelier = new ASQueenAttackInit<ASQueenChandelierAttackStrong>();
				ASQueenBase* trumps = new ASQueenAttackInit<ASQueenTrumpsAttack>();
				ASQueenBase* thorn1 = new ASQueenAttackInit<ASQueenThornAttackStrong<true>>();
				ASQueenBase* thorn2 = new ASQueenAttackInit<ASQueenThornAttackStrong<false>>();
				ASQueenBase* rod = new ASQueenAttackInit<ASQueenRodAttack>();

				// ����ɒǉ�
				chandelier->BuildState( rPrevState, this );
				QueueAction( chandelier );
				QueueAction( trumps );
				QueueAction( thorn1 );
				QueueAction( thorn2 );
				QueueAction( rod );

				break;
			}

		// �З͋�
		case 2:
			{
				// �ðĂ̏�����
				ASQueenBase* chandelier = new ASQueenAttackInit<ASQueenChandelierAttackStrong>();
				ASQueenBase* trumps = new ASQueenAttackInit<ASQueenTrumpsAttack>();
				ASQueenBase* thorn1 = new ASQueenAttackInit<ASQueenThornAttackStrong<true>>();
				ASQueenBase* thorn2 = new ASQueenAttackInit<ASQueenThornAttackStrong<false>>();
				ASQueenBase* rod = new ASQueenAttackInit<ASQueenRodAttackStrong>();

				// ����ɒǉ�
				QueueAction( chandelier );
				QueueAction( trumps );
				QueueAction( thorn1 );
				QueueAction( rod );
				ShuffleActions();
				InsertAfter( thorn2, thorn1 );

				ASQueenBase* nextAction = dynamic_cast<ASQueenBase*>(GetFirstState());
				nextAction->BuildState(rPrevState, this);
				break;
			}
	}

	
}

/************************************************************//**
*	@see Queen::AddNewStates
*	�܂��A�����オ���Ă���̂�ҋ@
****************************************************************/
void Queen::AddInitStates(int rX, int rY) {
	ActionState* initAction = new ASQueenWaitForMaku(false);

	// �ðĂ̏�����
	initAction->BuildState( GI("QUEEN_STARTX"), GI("QUEEN_STARTY"), this );

	// ����ɒǉ�
	QueueAction( initAction );
}


/************************************************************//**
*	��̧�l�̎擾���@
****************************************************************/
float Queen::GetAlpha(){
	verify(!mStates.empty());

	ASQueenBase* back = dynamic_cast<ASQueenBase*>(mStates.back());

	if( back )
		return (back->GetMutekiJikan()->IsMuteki())?0.5f:1.0f;
	else return 1.0f;
}
