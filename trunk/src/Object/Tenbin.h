#include <exception>
using namespace std;

#pragma once

#include "AshibaTenbin.h"
#include "..\\Mob\\Movable.h"

class AshibaTenbin;


//! 天秤
/****************************************************************//**
*	2つの足場を持ち、左右対称に動かす
*	\nosubgrouping
********************************************************************/
class Tenbin : public Movable
{

/****************************************************************//**
*	\name ﾗｲﾌ循環
********************************************************************/
/*@{*/
public:

	Tenbin(int rXPx, int rYPx, float Z);
	virtual ~Tenbin(void);

/*@}*/

	//! １フレームの処理。
	void Move();

	//! \param rHrSpacePx 天秤の足場が離れている横
	void SetHrSpace(int rHrSpacePx);

	//! \param rVrSpacePx 天秤の足場が離れている縦
	void SetVrSpace(int rVrSpacePx);

	//! 使わない
	void RunTask() {}

	//! 配置状態に戻す
	void Reset();

private:

	AshibaTenbin* mAshibaL;
	AshibaTenbin* mAshibaR;
	int mHrSpace;
	int mVrSpace;

};
