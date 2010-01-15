#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

//! •`‰æ
/****************************************************************//**
*	•`‰æ‚Ì•û–@‚ðŽ¦‚·µÌÞ¼Þª¸Ä
*	\nosubgrouping
********************************************************************/
class MobDrawer
{

public:

	//! •`‰æ‚Ì•û–@
	virtual void Draw() = 0;

	//! ‚±‚ÌµÌÞ¼Þª¸Ä‚ÌºËß°‚ð•Ô‚µ‚Ü‚·
	virtual MobDrawer* Clone() = 0;
};
