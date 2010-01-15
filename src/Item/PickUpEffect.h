#include <exception>
using namespace std;

#include "..\\Mob\\Movable.h"
#include "..\\Management\\GameControl.h"

#pragma once

//! ｱｲﾃﾑ効果(演出)
/****************************************************************//**
*	ｱｲﾃﾑを拾ったときの演出。
*	ﾋﾛｲﾝの頭から出て、浮かんで行く。Nﾋﾟｸｾﾙ距離を動いた後、ﾌｪｰﾄﾞで
*	消えます。
*	\nosubgrouping
********************************************************************/
class PickUpEffect : public Movable
{
public: 

	//! 標準コンストラクタ
	PickUpEffect( string rGraphic );
	//! 標準デストラクタ
	virtual ~PickUpEffect();

	//! 更新
	void Move();
	void RunTask() {}

protected:
	string mGraphic;
	float mAlpha;

	// 設定定数
	float ITEMFXFADESP;

};
