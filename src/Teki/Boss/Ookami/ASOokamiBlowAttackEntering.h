#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASOokamiStraightAttack.h"

//! �T�̋����U���E��ʂɓ����ė���
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class ASOokamiBlowAttackEntering: public ASOokamiStraightAttack
{

public:

	//! @see ASOokamiStraightAttack
	void BuildPosInfo(ActionState* rPrevState);

	//! @see AsOokamiStraightAttack
	void OnEnter();
	//! @see AsOokamiStraightAttack
	bool Update();
	//! @see AsOokamiStraightAttack
	void OnExit();


};

