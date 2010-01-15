#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASOokamiStraightAttack.h"

//! ˜T‚Ì‹­•—UŒ‚E‰æ–Ê‚É“ü‚Á‚Ä—ˆ‚é
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class ASOokamiBlowAttackEntering: public ASOokamiStraightAttack
{

public:

	//! @see ASOokamiStraightAttack
	void BuildPosInfo(ActionState* rPrevState);

	//! @see ASOokamiStraightAttack
	bool Update();
	//! @see ActionState
	void OnExit();

};

