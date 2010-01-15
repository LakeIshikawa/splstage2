#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASOokamiStraightAttack.h"


//! Όή¬έΜίU
/****************************************************************//**
*	ΌiUπ΅Δ­ι
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
		bool Update();

};
