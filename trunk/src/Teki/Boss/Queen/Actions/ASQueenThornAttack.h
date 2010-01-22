#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASQueenBase.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"
#include "..\\FriendObjects\\Thorn.h"

#define NUM_THORN 8

//! ��U��
/****************************************************************//**
*	��g�̂悤�ɓy���琶���Ă���
*
*	\nosubgrouping
********************************************************************/
template<bool D> class ASQueenThornAttack: public ASQueenBase
{

public:

	//! OnEnter @see ActionState
	void OnEnter(){
		FLOORY = GI("FLOORY");
		THORNSP = GF("THORNSP");
		THORNSP2 = GF("THORNSP2");
		THORNTRIGH = GI("THORNTRIGH");

		stage = 0;

		// ���̏o�����W
		for( int i=0; i<NUM_THORN; i++){
			char str[8] = "THORNX";
			str[6] = i+'1';
			str[7] = 0;
			spikeX[ D?i:(NUM_THORN-i-1) ] = GI(str);
		}

		throwNum = 0;

		// ��ڂ𔭎˂���
		curThorn = new Thorn( spikeX[throwNum], FLOORY, stage?THORNSP2:THORNSP );
		GAMECONTROL->GetMobManager()->Request(curThorn, true);
	}


	//! Update @see ActionState
	bool Update(){

		// �I������
		if( curThorn->GetHeight() <= 0 &&  throwNum >= NUM_THORN ) 
			return true;

		// THORNTRIGH��荂���Ȃ����玟�̈���o��
		if( curThorn->GetHeight() >= THORNTRIGH && throwNum < NUM_THORN ){
			throwNum++;
			// �V�K��
			curThorn = new Thorn( spikeX[throwNum], FLOORY, stage?THORNSP2:THORNSP );
			GAMECONTROL->GetMobManager()->Request(curThorn, true);
		}
		return false;
	}

	// OnExit @see ActionState
	void OnExit(){
		// �s����������΋A����Ă�
		if( D ) mParent->AddNextAction( new ASQueenThornAttack<false>() );
	}

	// @see ActionState
	void BuildAnimation(ActionState* rPrevAction)
	{
		mAnimation = Animation::ParseFromFile( "data\\animdata\\queen\\ThornAttack.txt" );
	}
	

	//! �З͂�ݒ�
	void SetStage(int st){ stage = st; }

	//! ���̐F
	static Kagami::Color GetColor()
	{ 
		return Kagami::Color(0.0f,1.0f,0.0f); 
	}

protected:
	int spikeX[16];
	int throwNum;

	int stage;

	// �ݒ�萔
	int FLOORY;
	int THORNTRIGH;
	float THORNSP;
	float THORNSP2;

	Thorn* curThorn;

};


/****************************************************************//**
*	�����ر�������ė���E�З͋�
*
*	\nosubgrouping
********************************************************************/
template <bool D> class ASQueenThornAttackStrong: public ASQueenThornAttack<D>
{
public: 
	void OnEnter(){ 
		THORNSP2 = GF("THORNSP2");
		SetStage(1);
		ASQueenThornAttack<D>::OnEnter();
	}
};