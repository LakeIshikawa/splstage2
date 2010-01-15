#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

//! ±¸¼®İ‚Æ“¯‚ÉÀs‚³‚ê‚éˆ—
/****************************************************************//**
*	@see ActionControllable
*	\nosubgrouping
********************************************************************/
class IActionThread
{
	public: 

		//! •½sˆ—
		virtual void Run() = 0;
};
