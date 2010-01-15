#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "OokamiHouse.h"

//! 家の基本ｸﾗｽ
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class OokamiHouseBrick: public OokamiHouse
{

public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	OokamiHouseBrick();

	//! ｸﾞﾗﾌｨｯｸの取得方法
	string GetGraphicSrc() 
	{ 
		return "graphics\\teki\\ookami\\brickhouse.png"; 
	}

	//! 壊れ方
	void Disappear();


	//! 破片ｼﾞｪﾈﾚｰﾀの作成(なし)
	void BuildParticleGenerator() {}

	//! 当たり判定応答なし
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId);

};

