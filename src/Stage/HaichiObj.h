#pragma once

/*
	配置の情報を持っている構造体
*/
class HaichiObj
{
public:
	HaichiObj(int rXPx, int rYPx, int rNo);
	virtual ~HaichiObj(void);

	int GetXPx();
	int GetYPx();
	int GetNo();

private:
	int mXPx;
	int mYPx;
	int mNo;

};
