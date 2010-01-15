#include ".\haichiobj.h"

HaichiObj::HaichiObj(int rXPx, int rYPx, int rNo)
{
	mXPx = rXPx;
	mYPx = rYPx;
    mNo = rNo;
}

HaichiObj::~HaichiObj(void)
{
}

// ¹Þ¯À°
int HaichiObj::GetXPx()
{
	return mXPx;
}

// ¹Þ¯À°
int HaichiObj::GetYPx()
{
	return mYPx;
}

// ¹Þ¯À°
int HaichiObj::GetNo()
{
	return mNo;
}