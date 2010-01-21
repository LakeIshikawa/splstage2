#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASOokamiStraightAttack.h"


//! ºﬁ¨›ÃﬂçUåÇ
/****************************************************************//**
*	íºêiçUåÇÇÇµÇƒÇ≠ÇÈ
*
*	\nosubgrouping
********************************************************************/
class ASOokamiJumpAttack: public ASOokamiStraightAttack
{
	public: 

		//! @see ActionState
		void BuildAnimation(ActionState* rPrevState);
		//! @see ActionState
		void BuildPosInfo(ActionState* rPrevState);

		//! @see AsOokamiStraightAttack
		void OnEnter();
		//! @see AsOokamiStraightAttack
		bool Update();
		//! @see AsOokamiStraightAttack
		void OnExit();

};
