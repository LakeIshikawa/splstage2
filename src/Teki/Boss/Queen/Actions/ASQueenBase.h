#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once
#include "..\\..\\..\\..\\Mob\\ActionControllable\\ActionState.h"
#include "..\\..\\..\\..\\Units\\MutekiJikan.h"
#include "..\\FriendObjects\\Kagami.h"
#include "..\\FriendObjects\\Chandelier.h"
#include "..\\FriendObjects\\Rod.h"
#include "..\\FriendObjects\\AppleGenerator.h"

class ICollidable;

//! 女王の基本ｽﾃｰﾄ
/****************************************************************//**
*	女王にとって標準の情報やを準備する。
*
*	\nosubgrouping
********************************************************************/
class ASQueenBase: virtual public ActionState
{

public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	ASQueenBase(){}
	//! 標準ﾃﾞｽﾄﾗｸﾀ
	virtual ~ASQueenBase();


	//! @see ActionState
	virtual void BuildAnimation(ActionState* rPrevState);
	//! @see ActionState
	virtual void BuildCollision(ActionState* rPrevState);
	//! @see ActionState
	virtual void BuildMapCollider(ActionState* rPrevState);
	//! @see ActionState
	virtual void BuildMobDrawer(ActionState* rPrevState);
	//! @see ActionState
	virtual void BuildOtherInfo(ActionState* rPrevState);
	//! @see ActionState
	virtual void BuildPosInfo(ActionState* rPrevState);
	//! @see ActionState
	virtual void BuildPosInfo(int rX, int rY);
	
	//! @see ActionState
	virtual void OnExit();


	//! 標準の当たり判定応答
	virtual void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId);


	//! ｱｸｾｽ
	MutekiJikan* GetMutekiJikan();
	//! ｱｸｾｽ
	Kagami* GetKagami();
	//! ｱｸｾｽ
	Chandelier* GetChandelier();
	//! ｱｸｾｽ
	Rod* GetRod1();
	//! ｱｸｾｽ
	Rod* GetRod2();
	//! ｱｸｾｽ
	AppleGenerator* GetAppleGenerator1();
	//! ｱｸｾｽ
	AppleGenerator* GetAppleGenerator2();

	//! ｱｸｾｽ
	int GetPowerStage();

protected:
	// 無敵
	MutekiJikan* mMutekiJikan;

	// 鏡
	Kagami* mKagami;

	// ｼｬﾝﾃﾞﾘｱ
	Chandelier* mChandelier;

	// ﾛｯﾄﾞ
	Rod* mRod1;
	Rod* mRod2;

	// ﾘﾝｺﾞｼﾞｪﾈﾚｰﾀ
	AppleGenerator* mAppleGenerator1; //左
	AppleGenerator* mAppleGenerator2; //右
	
	// HP
	int mHp;

	// 威力
	int mPowerStage;

	// 設定定数
	int QUEEN_STARTX;
	int QUEEN_STARTY;

};

