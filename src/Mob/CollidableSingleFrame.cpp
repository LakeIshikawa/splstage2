#include <exception>
using namespace std;

#include "CollidableSingleFrame.h"
#include "Movable.h"
#include "ICollidable.h"

/************************************************************//**
*	ﾀｽｸを追加する
****************************************************************/
CollidableSingleFrame::CollidableSingleFrame() {
	AddTask(this);
}

/************************************************************//**
*	ターゲットのリストを回し、あたり判定を行います。
****************************************************************/
void CollidableSingleFrame::RunTask() {
	
	//あたり判定ﾁｪｯｸ
	Collision* cur_frame = GetCurFrame();
	if(cur_frame){
		list<ICollidable*>::iterator it = mlTargets.begin(), en = mlTargets.end();
		for( ; it!=en; it++ ){
			Collision* coll_frame = (*it)->GetCurFrame();
			cur_frame->Hantei(coll_frame, this, *it);
		}
	}
}

/************************************************************//**
*	\param rTarget 当たり判定のターゲットとして追加する
****************************************************************/
void CollidableSingleFrame::AddTarget(ICollidable* rTarget) {
	mlTargets.push_back(rTarget);
}


/************************************************************//**
*	\param rTarget 当たり判定のターゲットとして解除する
****************************************************************/
void CollidableSingleFrame::RemoveTarget(ICollidable* rTarget) {
	mlTargets.remove(rTarget);
}

