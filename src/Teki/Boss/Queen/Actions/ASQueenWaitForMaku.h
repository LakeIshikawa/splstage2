#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\..\\..\\..\\Mob\\ActionControllable\\ActionState.h"
#include "ASQueenBase.h"
#include "..\\..\\BossShareActions\\ASWaitForMaku.h"


//! 幕が上がりきるのを待つ
/****************************************************************//**
*	幕が上がりきるまで待機する
*	\nosubgrouping
********************************************************************/
class ASQueenWaitForMaku : public ASWaitForMaku, public ASQueenBase
{

public:

	//! \param rOpenClose 0-幕が開くのを待つ 1-幕が閉じるのを待つ
	ASQueenWaitForMaku(bool rOpenClose) : ASWaitForMaku(rOpenClose){}

	void BuildMapCollider(ActionState* rPrevState) { ASQueenBase::BuildMapCollider(rPrevState);}
	void BuildCollision(ActionState* rPrevState) { ASQueenBase::BuildCollision(rPrevState);}
	void BuildAnimation(ActionState* rPrevState) { ASQueenBase::BuildAnimation(rPrevState);}
	void BuildMobDrawer(ActionState* rPrevState) { ASQueenBase::BuildMobDrawer(rPrevState);}
	void BuildOtherInfo(ActionState* rPrevState) { ASQueenBase::BuildOtherInfo(rPrevState);}
	void BuildPosInfo(ActionState* rPrevState) { ASQueenBase::BuildPosInfo(rPrevState);}
	
	
	//! 当たり判定なし
	virtual void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId) { }

	//! @see ActionState
	void OnEnter() { ASWaitForMaku::OnEnter(); }
	//! @see ActionState
	bool Update() { return ASWaitForMaku::Update(); }
	//! @see ActionState
	void OnExit() { ASWaitForMaku::OnExit(); }

};
