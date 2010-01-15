#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\Mob\\ActionControllable\\IActionThread.h"

//! –³“GŠÔ
/****************************************************************//**
*	–³“GŠÔ‚Ì•Àsˆ—‚ğ’S“–‚·‚é½Ú¯ÄŞ
*	\nosubgrouping
********************************************************************/
class MutekiJikan : public IActionThread
{

public:

	//! •W€ºİ½Ä×¸À
	MutekiJikan();

	//! @see ActionThread
	void Run();


	//! –³“GŠÔ‚ğİ’è‚·‚é
	void SetMutekiTime(float rTime);

	//! ‘€ìE–³“G‚É‚·‚é
	void Start();
	//! ±¸¾½
	bool IsMuteki();

	//! ¸Û°İ
	MutekiJikan* Clone();

private:
	float mTimer;
	float mMutekiTime;
	bool  mMutekiFl;
};
