#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Mob\\MobDrawer\\IAlphaCapable.h"


//! 狼
/****************************************************************//**
*	直進攻撃、ｼﾞｬﾝﾌﾟ攻撃、強力な息を吹きなどといったﾊﾟﾀｰﾝでﾋﾛｲﾝを
*	追い詰めてきます。 さぁ、ﾋﾛｲﾝどの…　果たしてこの俺を倒すことが
*	出来るのデショウカ!!
*
*	\nosubgrouping
********************************************************************/
class Ookami: public ActionControllable, public IAlphaCapable
{

	public: 

		//! @see ActionControllable
		void AddNewStates(ActionState* rPrevState);
		//! @see ActionControllable
		void AddInitStates(int rX, int rY);

		
		//! IAlphaCapableの実現
		float GetAlpha();

};
