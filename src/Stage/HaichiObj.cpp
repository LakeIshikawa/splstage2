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

// �ޯ��
int HaichiObj::GetXPx()
{
	return mXPx;
}

// �ޯ��
int HaichiObj::GetYPx()
{
	return mYPx;
}

// �ޯ��
int HaichiObj::GetNo()
{
	return mNo;
}