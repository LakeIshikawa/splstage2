#pragma once

#include "..\\Mob\\Movable.h"
#include "..\\Mob\\MobDrawer\SimpleDrawer.h"
#include "..\\Animation\\Animation.h"

//! ‘ÅŒ‚´Ìª¸Ä
/****************************************************************//**
*	ËÛ²İ‚ÌUŒ‚‚ª‚ ‚½‚é‚Æ‚«‚Ì´Ìª¸Ä
*	\nosubgrouping
********************************************************************/
class HitEffect : public Movable
{

/****************************************************************//**
*	\name ×²ÌzŠÂ
********************************************************************/
/*@{*/
public:
	HitEffect(int rXPx, int rYPx);
	~HitEffect(void);

/*@}*/

/****************************************************************//**
*	\name ‘€ì
********************************************************************/
/*@{*/
	
	//! XVˆ—
	void Move();
	void RunTask(){}
	//! •`‰æ
	void Draw();

/*@}*/


protected:
	// ±ÆÒ°¼®İ
	Animation* mAnim;
	// •`‰æ
	SimpleDrawer* mSDrawer;
	
};
