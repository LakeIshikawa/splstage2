#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "OokamiBaseAction.h"

/************************************************************//**
*	\return 狼の標準の当たり判定
****************************************************************/
Collision* OokamiBaseAction::BuildCollision(ActionState* rPrevState) {
	
	// 標準のあたり判定
}

/************************************************************//**
*	\return 狼の標準のﾏｯﾌﾟ当たり判定
****************************************************************/
MapCollision* OokamiBaseAction::BuildMapCollider(ActionState* rPrevState) {
	
	// 標準のあたり判定
}

/************************************************************//**
*	\return 狼の標準のﾏｯﾌﾟ当たり判定
****************************************************************/
Animation* OokamiBaseAction::BuildAnimation(ActionState* rPrevState) {
	
	// 標準のあたり判定
}


void OokamiBaseAction::CollisionResponse(ICollidable* rCollObject, 
										 int rThisGroupId, int rOpGroupId) {
	throw "Not yet implemented";
}

void OokamiBaseAction::Draw() {
	throw "Not yet implemented";
}

void OokamiBaseAction::OnEnter() {
	throw "Not yet implemented";
}

bool OokamiBaseAction::Update() {
	throw "Not yet implemented";
}

void OokamiBaseAction::OnExit() {
	throw "Not yet implemented";
}

