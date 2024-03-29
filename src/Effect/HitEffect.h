#pragma once

#include "..\\Mob\\Movable.h"
#include "..\\Mob\\MobDrawer\SimpleDrawer.h"
#include "..\\Animation\\Animation.h"

//! 打撃ｴﾌｪｸﾄ
/****************************************************************//**
*	ﾋﾛｲﾝの攻撃があたるときのｴﾌｪｸﾄ
*	\nosubgrouping
********************************************************************/
class HitEffect : public Movable
{

/****************************************************************//**
*	\name ﾗｲﾌ循環
********************************************************************/
/*@{*/
public:
	HitEffect(int rXPx, int rYPx);
	~HitEffect(void);

/*@}*/

/****************************************************************//**
*	\name 操作
********************************************************************/
/*@{*/
	
	//! 更新処理
	void Move();
	void RunTask(){}
	//! 描画
	void Draw();

/*@}*/


protected:
	// ｱﾆﾒｰｼｮﾝ
	Animation* mAnim;
	// 描画
	SimpleDrawer* mSDrawer;
	
};
