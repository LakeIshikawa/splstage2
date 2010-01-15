#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

class IPositionable;

//! 画面情報を得られるようなｵﾌﾞｼﾞｪｸﾄを象徴します
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class IPositionable
{

public:

	//! 画面の絶対X座標を取得する方法
	virtual float GetX() = 0;

	//! 画面の絶対Y座標を取得する方法
	virtual float GetY() = 0;

	//! ｵﾌﾞｼﾞｪｸﾄの向きを取得する方法 (0=右 1=左)
	virtual bool GetMuki() = 0;

	//! グラフィックの一フレームの横幅を取得する方法
	virtual int GetFrameSizeX() = 0;

	//! グラフィックの一フレームの縦幅を取得する方法
	virtual int GetFrameSizeY() = 0;
};
