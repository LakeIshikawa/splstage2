#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASOokamiBase.h"

//! ���i�U��
/****************************************************************//**
*	���i�U�������Ă���
*
*	\nosubgrouping
********************************************************************/
class ASOokamiStraightAttack: public ASOokamiBase
{

public:

	//! @see ActionState
	void BuildAnimation(ActionState* rPrevState);
	//! @see ActionState
	virtual void BuildPosInfo(ActionState* rPrevState);

	//! @see ActionState
	void OnEnter();
	//! @see ActionState
	bool Update();
	//! @see ActionState
	void OnExit();
};
