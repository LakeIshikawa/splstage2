#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once


//! ｱﾙﾌｧ描画の可能なｵﾌﾞｼﾞｪｸﾄ
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class IAlphaCapable
{

public:

	//! ｱﾙﾌｧ値の取得方法を示す
	virtual float GetAlpha() = 0;

};
