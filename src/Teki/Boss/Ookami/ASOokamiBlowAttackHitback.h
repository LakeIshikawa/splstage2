#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASOokamiDamage.h"


//! òTÇÃã≠ïóçUåÇÅEÀØƒ ﬁØ∏
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class ASOokamiBlowAttackHitback: public ASOokamiDamage
{

public:

	//! @see ActionState
	void OnEnter();
	//! @see ASOokamiStraightAttack
	bool Update();
	//! @see ActionState
	void OnExit();
};

