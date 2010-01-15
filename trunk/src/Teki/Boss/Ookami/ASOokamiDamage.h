#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASOokamiBase.h"

//! �T����Ұ�޽ð�
/****************************************************************//**
*	�d�����āA�����̱�Ұ��݂��I������I������
*	\nosubgrouping
********************************************************************/
class ASOokamiDamage: public ASOokamiBase
{

public:

	//! @see ActionState
	void BuildAnimation(ActionState* rPrevState);

	//! @see ActionState
	virtual void OnEnter();
	//! @see ActionState
	virtual bool Update();
	//! @see ActionState
	virtual void OnExit();

	//! �W���̓����蔻�艞��
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId){}
};
