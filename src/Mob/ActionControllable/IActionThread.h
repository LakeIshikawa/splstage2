#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

//! ｱｸｼｮﾝと同時に実行される処理
/****************************************************************//**
*	@see ActionControllable
*	\nosubgrouping
********************************************************************/
class IActionThread
{
	public: 

		//! 平行処理
		virtual void Run() = 0;
};
