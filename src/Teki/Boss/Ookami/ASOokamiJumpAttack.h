#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASOokamiStraightAttack.h"


//! �ެ��ߍU��
/****************************************************************//**
*	���i�U�������Ă���
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
