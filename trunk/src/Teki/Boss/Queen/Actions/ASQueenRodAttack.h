#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASQueenBase.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"


//! ۯ�ލU���E�I������
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class ASQueenRodAttackEnd: public ASQueenBase
{
public:
	
	//! @see ActionState
	bool Update()
	{
		return mAnimation->GetLoopCount() >= 1;
	}

	//! @see ActionState
	void BuildAnimation(ActionState* rPrevState)
	{
		mAnimation = Animation::ParseFromFile( "data\\animdata\\queen\\RodAttackEnd.txt" );
	}

	void OnEnter(){};
};


//! ۯ�ލU��
/****************************************************************//**
*	ۯ�ނ��񂵂čU�����Ă���
*
*	\nosubgrouping
********************************************************************/
class ASQueenRodAttack: public ASQueenBase
{

public:

	//! @see ActionState
	void OnEnter() {
		mRod1 = new Rod(0.0f, GAMECONTROL->GetJiki()->GetX() <= SP->SCRSZX/2);
		GAMECONTROL->GetMobManager()->Request( mRod1, true );
	}
	
	//! @see ActionState
	bool Update() {return mRod1->HasFinished();}
	
	//! @see ActionState
	void OnExit(){ 
		ASQueenBase::OnExit(); 
		GAMECONTROL->GetMobManager()->Remove( mRod1 ); 

		// �I������ɓ���
		mParent->AddNextAction(new ASQueenRodAttackEnd());
	}

	// @see ActionState
	void BuildAnimation(ActionState* rPrevAction)
	{
		mAnimation = Animation::ParseFromFile( "data\\animdata\\queen\\RodAttack.txt" );
		mAnimation->SetLoopStartIdx(2);
	}

	//! ���̐F
	static Kagami::Color GetColor()
	{ 
		return Kagami::Color(1.0f,0.0f,0.0f); 
	}
};

/****************************************************************//**
*	�����ر�������ė���E�З͋�
*
*	\nosubgrouping
********************************************************************/
class ASQueenRodAttackStrong: public ASQueenRodAttack
{
public: 
	//! @see ActionState
	void OnEnter() {
		mRod1 = new Rod(0.0f, GAMECONTROL->GetJiki()->GetX() <= SP->SCRSZX/2);
		mRod2 = new Rod(D3DX_PI, GAMECONTROL->GetJiki()->GetX() <= SP->SCRSZX/2);
		GAMECONTROL->GetMobManager()->Request( mRod1, true );
		GAMECONTROL->GetMobManager()->Request( mRod2, true );
	}
	
	//! @see ActionState
	bool Update() {return mRod1->HasFinished();}
	
	//! @see ActionState
	void OnExit(){ 
		ASQueenBase::OnExit(); 
		GAMECONTROL->GetMobManager()->Remove( mRod1 ); 
		GAMECONTROL->GetMobManager()->Remove( mRod2 ); 

		// �I������ɓ���
		mParent->AddNextAction(new ASQueenRodAttackEnd());
	}
	
};

