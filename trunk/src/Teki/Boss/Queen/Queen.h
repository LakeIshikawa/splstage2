#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Mob\\MobDrawer\\IAlphaCapable.h"


//! 女王
/****************************************************************//**
*	ｼｬﾝﾃﾞﾘｱ落とし、ﾄﾗﾝﾌﾟ兵を使い、茨を召喚、そしてﾚｰｻﾞｰﾋﾞｰﾑ!
*	ﾗｽﾄﾎﾞｽを倒せたらこのｹﾞｰﾑは終わります。
*	\nosubgrouping
********************************************************************/
class Queen: public ActionControllable, public IAlphaCapable
{

	public: 

		Queen(){mZ = -0.2f;}

		//! @see ActionControllable
		void AddNewStates(ActionState* rPrevState);
		//! @see ActionControllable
		void AddInitStates(int rX, int rY);

		
		//! IAlphaCapableの実現
		float GetAlpha();

};
