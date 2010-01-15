#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\Mob\\ActionControllable\\ActionState.h"

//! ﾌｪｰﾄﾞｱｳﾄさせて、ｽﾃｰｷｸﾘｱを呼ぶ
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class ASFadeOutAndStageClear : public ActionState
{

public:

	//! 当たり判定ｵﾌﾞｼﾞｪｸﾄの作る方法
	void BuildCollision(ActionState* rPrevState);
	//! ﾏｯﾌﾟ当たり判定ｵﾌﾞｼﾞｪｸﾄの作る方法
	void BuildMapCollider(ActionState* rPrevState);
	//! ｱﾆﾒｰｼｮﾝｵﾌﾞｼﾞｪｸﾄの作る方法
	void BuildAnimation(ActionState* rPrevState);
	//! 描画方法を示すｵﾌﾞｼﾞｪｸﾄの作る方法
	void BuildMobDrawer(ActionState* rPrevState);
	//! 派生ｸﾗｽの持っている特別情報をｺﾋﾟｰする方法
	void BuildOtherInfo(ActionState* rPrevState);
	
	
	//! 当たり判定の応答方法
	virtual void CollisionResponse(ICollidable* rCollObject, 
				int rThisGroupId, int rOpGroupId);

	//! @see ActionState
	void OnEnter();
	//! @see ActionState
	bool Update();
	//! @see ActionState
	void OnExit();

};
