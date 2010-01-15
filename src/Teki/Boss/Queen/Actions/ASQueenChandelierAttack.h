#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASQueenBase.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"

//! �����ر�U��
/****************************************************************//**
*	�����ر�������ė���
*
*	\nosubgrouping
********************************************************************/
class ASQueenChandelierAttack: public ASQueenBase
{

public:

	//! @see ActionState
	void OnEnter() {mChandelier->Drop();}
	//! @see ActionState
	bool Update() {return mChandelier->IsStopped();}

	//! @see ActionState
	void BuildAnimation(ActionState* rPrevState)
	{
		mAnimation = Animation::ParseFromFile( "data\\animdata\\queen\\ChandelierAttack.txt" );
	}
	

	//! ���̐F
	static Kagami::Color GetColor()
	{ 
		return Kagami::Color(1.0f,1.0f,0.0f); 
	}
};

/****************************************************************//**
*	�����ر�������ė���E�З͋�
*
*	\nosubgrouping
********************************************************************/
class ASQueenChandelierAttackStrong: public ASQueenChandelierAttack
{
public: 
	void OnEnter(){ 
		ASQueenChandelierAttack::OnEnter();
		mChandelier->SetStage(true);
	}
};
