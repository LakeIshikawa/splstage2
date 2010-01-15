#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once
#include "..\\BossShareActions\\ASJumpingDeath.h"
#include "ASOokamiBase.h"


//! �T�̊�{�����
/****************************************************************//**
*	�T�ɂƂ��ĕW���̏������������B
*
*	\nosubgrouping
********************************************************************/
class ASOokamiJumpingDeath: virtual public ASJumpingDeath, virtual public ASOokamiBase
{

public:

	//! @se ActionState
	void BuildAnimation(ActionState* rPrevState);

	//! @see ActionState
	void OnEnter();

	//! �W���̓����蔻�艞��
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId){}

};

