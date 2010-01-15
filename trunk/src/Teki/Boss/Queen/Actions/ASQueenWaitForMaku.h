#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\..\\..\\..\\Mob\\ActionControllable\\ActionState.h"
#include "ASQueenBase.h"
#include "..\\..\\BossShareActions\\ASWaitForMaku.h"


//! –‹‚ªã‚ª‚è‚«‚é‚Ì‚ğ‘Ò‚Â
/****************************************************************//**
*	–‹‚ªã‚ª‚è‚«‚é‚Ü‚Å‘Ò‹@‚·‚é
*	\nosubgrouping
********************************************************************/
class ASQueenWaitForMaku : public ASWaitForMaku, public ASQueenBase
{

public:

	//! \param rOpenClose 0-–‹‚ªŠJ‚­‚Ì‚ğ‘Ò‚Â 1-–‹‚ª•Â‚¶‚é‚Ì‚ğ‘Ò‚Â
	ASQueenWaitForMaku(bool rOpenClose) : ASWaitForMaku(rOpenClose){}

	void BuildMapCollider(ActionState* rPrevState) { ASQueenBase::BuildMapCollider(rPrevState);}
	void BuildCollision(ActionState* rPrevState) { ASQueenBase::BuildCollision(rPrevState);}
	void BuildAnimation(ActionState* rPrevState) { ASQueenBase::BuildAnimation(rPrevState);}
	void BuildMobDrawer(ActionState* rPrevState) { ASQueenBase::BuildMobDrawer(rPrevState);}
	void BuildOtherInfo(ActionState* rPrevState) { ASQueenBase::BuildOtherInfo(rPrevState);}
	void BuildPosInfo(ActionState* rPrevState) { ASQueenBase::BuildPosInfo(rPrevState);}
	
	
	//! “–‚½‚è”»’è‚È‚µ
	virtual void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId) { }

	//! @see ActionState
	void OnEnter() { ASWaitForMaku::OnEnter(); }
	//! @see ActionState
	bool Update() { return ASWaitForMaku::Update(); }
	//! @see ActionState
	void OnExit() { ASWaitForMaku::OnExit(); }

};
