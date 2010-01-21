#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASOokamiBase.h"


//! �T�̋����U���E�C��
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class ASOokamiBlowAttackFaint: public ASOokamiBase
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


	//! �����蔻�艞��
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId);

};

