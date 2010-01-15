#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once
#include "..\\..\\..\\Mob\\ActionControllable\\ActionState.h"
#include "..\\..\\..\\Units\\MutekiJikan.h"
#include "OokamiHouse.h"
#include "Storm.h"

class ICollidable;

//! 狼の基本ｱｸｼｮﾝ
/****************************************************************//**
*	狼にとって標準の情報やを準備する。
*
*	\nosubgrouping
********************************************************************/
class ASOokamiBase: virtual public ActionState
{

public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	ASOokamiBase() : brick(NULL), straw(NULL), rog(NULL), storm(NULL) {}
	//! 標準ﾃﾞｽﾄﾗｸﾀ
	~ASOokamiBase();


	//! @see ActionState
	void BuildCollision(ActionState* rPrevState);
	//! @see ActionState
	void BuildMapCollider(ActionState* rPrevState);
	//! @see ActionState
	void BuildMobDrawer(ActionState* rPrevState);
	//! @see ActionState
	void BuildPosInfo(ActionState* rPrevState);
	//! @see ActionState
	void BuildOtherInfo(ActionState* rPrevState);


	//! 標準の当たり判定応答
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId);


	//! ｱｸｾｽ
	MutekiJikan* GetMutekiJikan();

protected:
	// 無敵
	MutekiJikan* mMutekiJikan;
	// HP
	int mHp;

	OokamiHouse* brick;	//!< ﾚﾝｶﾞの家
	OokamiHouse* rog;	//!< 木の家
	OokamiHouse* straw;	//!< わらの家

	Storm* storm;		//! 強風

	// 設定定数
	int OOKAMI_STARTX;
	int OOKAMI_STARTY;
	float OOKAMI_STRATKSPX;
	float OOKAMI_JMPSHOSOKUY;
	int OOKAMI_ENTERRX;
	int OOKAMI_ENTERLX;

};

