#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once
#include "..\\..\\..\\Mob\\ActionControllable\\ActionState.h"


//! �T�̊�{�����
/****************************************************************//**
*	�ެ���(˯��ޯ����ۂ����)���ĉ�ʂ̉����甲����
*
*	\nosubgrouping
********************************************************************/
class ASJumpingDeath: virtual public ActionState
{

public:
	
	virtual ~ASJumpingDeath() {}

	//! @see ActionState
	void OnEnter();
	//! @see ActionState
	bool Update();
	//! @see ActionState
	void OnExit();

	//! �W���̓����蔻�艞��
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId){}


};

