#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASOokamiStraightAttack.h"

//! 狼の強風攻撃・画面に入って来る
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

