#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASOokamiBase.h"
#include "OokamiHouseStraw.h"
#include "OokamiHouseRog.h"
#include "OokamiHouseBrick.h"


//! òTÇÃã≠ïóçUåÇÅEëßÇìfÇ≠
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class ASOokamiBlowAttackAspire: public ASOokamiBase
{

public:

	//! @see ActionState
	void BuildAnimation(ActionState* rPrevState);

	//! @see ActionState
	void OnEnter();
	//! @see ASOokamiStraightAttack
	bool Update();
	//! @see ActionState
	void OnExit();

};

