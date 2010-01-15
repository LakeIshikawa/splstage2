#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Mob\\MobDrawer\\IAlphaCapable.h"


//! ����
/****************************************************************//**
*	�����ر���Ƃ��A����ߕ����g���A��������A������ڰ�ް�ް�!
*	׽��޽��|�����炱�̹ްт͏I���܂��B
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

		
		//! IAlphaCapable�̎���
		float GetAlpha();

};
