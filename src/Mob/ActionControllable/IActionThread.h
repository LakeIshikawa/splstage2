#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

//! ����݂Ɠ����Ɏ��s����鏈��
/****************************************************************//**
*	@see ActionControllable
*	\nosubgrouping
********************************************************************/
class IActionThread
{
	public: 

		//! ���s����
		virtual void Run() = 0;
};
