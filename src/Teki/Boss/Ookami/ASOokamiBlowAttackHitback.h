#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASOokamiDamage.h"


//! �T�̋����U���E˯��ޯ�
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

