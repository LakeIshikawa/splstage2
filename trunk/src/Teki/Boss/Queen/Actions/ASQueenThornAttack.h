#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "ASQueenBase.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"
#include "..\\FriendObjects\\Thorn.h"

#define NUM_THORN 8

//! 茨攻撃
/****************************************************************//**
*	茨が波のように土から生えてくる
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

		// 棘の出現座標
		for( int i=0; i<NUM_THORN; i++){
			char str[8] = "THORNX";
			str[6] = i+'1';
			str[7] = 0;
			spikeX[ D?i:(NUM_THORN-i-1) ] = GI(str);
		}

		throwNum = 0;

		// 一個目を発射する
		curThorn = new Thorn( spikeX[throwNum], FLOORY, stage?THORNSP2:THORNSP );
		GAMECONTROL->GetMobManager()->Request(curThorn, true);
	}


	//! Update @see ActionState
	bool Update(){

		// 終了条件
		if( curThorn->GetHeight() <= 0 &&  throwNum >= NUM_THORN ) 
			return true;

		// THORNTRIGHより高くなったら次の茨を出す
		if( curThorn->GetHeight() >= THORNTRIGH && throwNum < NUM_THORN ){
			throwNum++;
			// 新規茨
			curThorn = new Thorn( spikeX[throwNum], FLOORY, stage?THORNSP2:THORNSP );
			GAMECONTROL->GetMobManager()->Request(curThorn, true);
		}
		return false;
	}

	// OnExit @see ActionState
	void OnExit(){
		// 行きだったらば帰りを呼ぶ
		if( D ) mParent->AddNextAction( new ASQueenThornAttack<false>() );
	}

	// @see ActionState
	void BuildAnimation(ActionState* rPrevAction)
	{
		mAnimation = Animation::ParseFromFile( "data\\animdata\\queen\\ThornAttack.txt" );
	}
	

	//! 威力を設定
	void SetStage(int st){ stage = st; }

	//! 鏡の色
	static Kagami::Color GetColor()
	{ 
		return Kagami::Color(0.0f,1.0f,0.0f); 
	}

protected:
	int spikeX[16];
	int throwNum;

	int stage;

	// 設定定数
	int FLOORY;
	int THORNTRIGH;
	float THORNSP;
	float THORNSP2;

	Thorn* curThorn;

};


/****************************************************************//**
*	ｼｬﾝﾃﾞﾘｱが落ちて来る・威力強
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
