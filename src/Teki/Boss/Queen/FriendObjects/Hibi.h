#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\..\\Mob\\Movable.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"

//! 罅
/****************************************************************//**
*	ﾋﾋﾞ
*	\nosubgrouping
********************************************************************/
class Hibi : public Movable
{

public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	Hibi(IPositionable* parent): mParent(parent)
	{
		mHibiStage = 0;
		mZ = -0.1;
	}

	//! @see Movable
	void Move(){
		if( mHibiStage ){
			int x = mParent->GetX();
			int y = mParent->GetY();
			int left = (mHibiStage-1)*mParent->GetFrameSizeX();
			int top = 0;
			int right = mHibiStage*mParent->GetFrameSizeX();
			int bottom = mParent->GetFrameSizeY();
			DX_DRAW( "graphics\\teki\\queen\\boss4_mirror0.png", 
				x, y, left, top, right, bottom );
		}
	}
	//! @see Movable
	void RunTask(){}

	//! ﾋﾋﾞの強さを設定する(0->3)
	void SetHibiStage(int st){ mHibiStage = st; }

private:
	int mHibiStage;
	IPositionable* mParent;
};
