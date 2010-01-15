#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\Mob\\ActionControllable\\ActionControllable.h"
#include "..\\..\\..\\Mob\\MobDrawer\\IAlphaCapable.h"


//! �T
/****************************************************************//**
*	���i�U���A�ެ��ߍU���A���͂ȑ��𐁂��ȂǂƂ���������݂��۲݂�
*	�ǂ��l�߂Ă��܂��B �����A�۲݂ǂ́c�@�ʂ����Ă��̉���|�����Ƃ�
*	�o����̃f�V���E�J!!
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

		
		//! IAlphaCapable�̎���
		float GetAlpha();

};
