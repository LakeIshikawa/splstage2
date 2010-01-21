#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASOokamiBase.h"


//! ˜T‚Ì‹­•—UŒ‚E‹Câ
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


	//! “–‚½‚è”»’è‰“š
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId);

};

