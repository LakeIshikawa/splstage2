﻿#pragma once

#include "Cheat.h"

//! ヒロインにダメージを与えるチート
/****************************************************************//**
*	\see Cheats
*	\nosubgrouping
********************************************************************/
class ChtInflictDamage : public Cheat
{
	public:
		ChtInflictDamage(int rKey);
		~ChtInflictDamage(void);

	/************************************************************//**
	*	\name 使うﾒｿｯﾄﾞ
	*	処理に便利な機能を提供するﾒｿｯﾄﾞ。
	****************************************************************/	
	/*@{*/
	
		void DoCheat();

	/*/}*/

};