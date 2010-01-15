#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\Mob\\ActionControllable\\ActionState.h"

//! 幕が上がりきるのを待つ
/****************************************************************//**
*	幕が上がりきるまで待機する
*	\nosubgrouping
********************************************************************/
class ASWaitForMaku : virtual public ActionState
{

public:

	//! \param rOpenClose 0-幕が開くのを待つ 1-幕が閉じるのを待つ
	ASWaitForMaku(bool rOpenClose) : mOpenClose(rOpenClose){}

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

private:
	bool mOpenClose;

};
