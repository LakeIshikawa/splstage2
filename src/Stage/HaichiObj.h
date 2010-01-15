#pragma once

/*
	”z’u‚Ìî•ñ‚ğ‚Á‚Ä‚¢‚é\‘¢‘Ì
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
