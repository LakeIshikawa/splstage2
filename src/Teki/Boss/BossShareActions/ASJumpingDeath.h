#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once
#include "..\\..\\..\\Mob\\ActionControllable\\ActionState.h"


//! ˜T‚ÌŠî–{±¸¼®İ
/****************************************************************//**
*	¼Ş¬İÌß(Ë¯ÄÊŞ¯¸‚Á‚Û‚¢‚â‚Â)‚µ‚Ä‰æ–Ê‚Ì‰º‚©‚ç”²‚¯‚é
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

	//! •W€‚Ì“–‚½‚è”»’è‰“š
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId){}


};

