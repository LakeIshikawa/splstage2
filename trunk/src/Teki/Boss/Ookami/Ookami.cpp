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
*	˜T‚ª×İÀŞÑ‚È‡”Ô‚ÅO‚Â‚Ì±¸¼®İ‚ğŒJ‚è•Ô‚µ‚Ü‚·B
*	0 - ’¼iUŒ‚
*	1 - ¼Ş¬İÌßUŒ‚
*	2 - ‰Æ‚Ì‚«”ò‚Î‚µ
****************************************************************/
void Ookami::AddNewStates(ActionState* rPrevState) {


	// E‚¢Ø½Ä‚ğì‚é
	list<pair<ASOokamiBase*, int>> initPick;
	initPick.push_back(pair<ASOokamiStraightAttack*,int>(new ASOokamiStraightAttack(), rand()%10));
	initPick.push_back(pair<ASOokamiJumpAttack*,int>(new ASOokamiJumpAttack(), rand()%10));
	initPick.push_back(pair<ASOokamiBlowAttackEntering*, int>(new ASOokamiBlowAttackEntering(),rand()%10));

	initPick.sort(random);

	for each( pair<ASOokamiBase*, int> ap in initPick ){
		// ½Ã°Ä‚Ì‰Šú‰»
		ap.first->BuildState( rPrevState, this );
		// ·­°‚É’Ç‰Á
		QueueAction( ap.first );
	}
}

/************************************************************//**
*	@see Ookami::AddNewStates
*	‚Ü‚¸A–‹‚ªã‚ª‚Á‚Ä‚­‚é‚Ì‚ğ‘Ò‹@
****************************************************************/
void Ookami::AddInitStates(int rX, int rY) {
	ActionState* initAction = new ASWaitForMaku(false);

	// ½Ã°Ä‚Ì‰Šú‰»
	initAction->BuildState( GI("OOKAMI_STARTX"), GI("OOKAMI_STARTY"), this );

	// ·­°‚É’Ç‰Á
	QueueAction( initAction );
}


/************************************************************//**
*	±ÙÌ§’l‚Ìæ“¾•û–@
****************************************************************/
float Ookami::GetAlpha(){
	verify(!mStates.empty());

	ASOokamiBase* back = dynamic_cast<ASOokamiBase*>(mStates.back());

	if( back )
		return (back->GetMutekiJikan()->IsMuteki())?0.5f:1.0f;
	else return 1.0f;
}

/************************************************************//**
*	×İÀŞÑ‚Å¿°Ä
****************************************************************/
bool random(pair<ASOokamiBase*, int> a, pair<ASOokamiBase*, int> b)
{
	return a.second > b.second;
}