#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

//! 描画
/****************************************************************//**
*	描画の方法を示すｵﾌﾞｼﾞｪｸﾄ
*	\nosubgrouping
********************************************************************/
class MobDrawer
{

public:

	//! 描画の方法
	virtual void Draw() = 0;

	//! このｵﾌﾞｼﾞｪｸﾄのｺﾋﾟｰを返します
	virtual MobDrawer* Clone() = 0;
};
