#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASOokamiBase.h"

//! �T�̋����U���E�����z��
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class ASOokamiBlowAttackInspire: public ASOokamiBase
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

