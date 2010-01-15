#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\..\\..\\..\\Mob\\ActionControllable\\ActionState.h"
#include "ASQueenBase.h"
#include "..\\..\\BossShareActions\\ASWaitForMaku.h"


//! �����オ�肫��̂�҂�
/****************************************************************//**
*	�����オ�肫��܂őҋ@����
*	\nosubgrouping
********************************************************************/
class ASQueenWaitForMaku : public ASWaitForMaku, public ASQueenBase
{

public:

	//! \param rOpenClose 0-�����J���̂�҂� 1-��������̂�҂�
	ASQueenWaitForMaku(bool rOpenClose) : ASWaitForMaku(rOpenClose){}

	void BuildMapCollider(ActionState* rPrevState) { ASQueenBase::BuildMapCollider(rPrevState);}
	void BuildCollision(ActionState* rPrevState) { ASQueenBase::BuildCollision(rPrevState);}
	void BuildAnimation(ActionState* rPrevState) { ASQueenBase::BuildAnimation(rPrevState);}
	void BuildMobDrawer(ActionState* rPrevState) { ASQueenBase::BuildMobDrawer(rPrevState);}
	void BuildOtherInfo(ActionState* rPrevState) { ASQueenBase::BuildOtherInfo(rPrevState);}
	void BuildPosInfo(ActionState* rPrevState) { ASQueenBase::BuildPosInfo(rPrevState);}
	
	
	//! �����蔻��Ȃ�
	virtual void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId) { }

	//! @see ActionState
	void OnEnter() { ASWaitForMaku::OnEnter(); }
	//! @see ActionState
	bool Update() { return ASWaitForMaku::Update(); }
	//! @see ActionState
	void OnExit() { ASWaitForMaku::OnExit(); }

};
