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
*	�T������тȏ��ԂŎO�̱���݂��J��Ԃ��܂��B
*	0 - ���i�U��
*	1 - �ެ��ߍU��
*	2 - �Ƃ̐�����΂�
****************************************************************/
void Ookami::AddNewStates(ActionState* rPrevState) {


	// �E��ؽĂ����
	list<pair<ASOokamiBase*, int>> initPick;
	initPick.push_back(pair<ASOokamiStraightAttack*,int>(new ASOokamiStraightAttack(), rand()%10));
	initPick.push_back(pair<ASOokamiJumpAttack*,int>(new ASOokamiJumpAttack(), rand()%10));
	initPick.push_back(pair<ASOokamiBlowAttackEntering*, int>(new ASOokamiBlowAttackEntering(),rand()%10));

	initPick.sort(random);

	for each( pair<ASOokamiBase*, int> ap in initPick ){
		// �ðĂ̏�����
		ap.first->BuildState( rPrevState, this );
		// ����ɒǉ�
		QueueAction( ap.first );
	}
}

/************************************************************//**
*	@see Ookami::AddNewStates
*	�܂��A�����オ���Ă���̂�ҋ@
****************************************************************/
void Ookami::AddInitStates(int rX, int rY) {
	ActionState* initAction = new ASWaitForMaku(false);

	// �ðĂ̏�����
	initAction->BuildState( GI("OOKAMI_STARTX"), GI("OOKAMI_STARTY"), this );

	// ����ɒǉ�
	QueueAction( initAction );
}


/************************************************************//**
*	��̧�l�̎擾���@
****************************************************************/
float Ookami::GetAlpha(){
	verify(!mStates.empty());

	ASOokamiBase* back = dynamic_cast<ASOokamiBase*>(mStates.back());

	if( back )
		return (back->GetMutekiJikan()->IsMuteki())?0.5f:1.0f;
	else return 1.0f;
}

/************************************************************//**
*	����тſ��
****************************************************************/
bool random(pair<ASOokamiBase*, int> a, pair<ASOokamiBase*, int> b)
{
	return a.second > b.second;
}