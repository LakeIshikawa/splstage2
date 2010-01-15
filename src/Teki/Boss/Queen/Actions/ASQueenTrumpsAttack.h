#include <string>
#include <list>
#include <algorithm>
#include <exception>
using namespace std;

#pragma once

#include "ASQueenBase.h"
#include "..\\..\\..\\..\\Management\\GameControl.h"
#include "..\\FriendObjects\\Trump.h"

#define TRUMPS_NUM 4

//! �����ر�U��
/****************************************************************//**
*	����ߕ��̓ˌ�
*
*	\nosubgrouping
********************************************************************/
class ASQueenTrumpsAttack: public ASQueenBase
{

public:

	//! @see ActionState
	void OnEnter(){

		string graphics[] = 
		{
			"graphics\\teki\\queen\\boss4_card0.png",
			"graphics\\teki\\queen\\boss4_card1.png",
			"graphics\\teki\\queen\\boss4_card2.png",
			"graphics\\teki\\queen\\boss4_card3.png"
		};

		// ����߂�ظ���
		list<int> picks;
		list<int> picks2;
		for( int i=0; i<TRUMPS_NUM; i++){
			// ����������
			int pick = rand()%TRUMPS_NUM;
			int pick2 = rand()%TRUMPS_NUM;
			while( find(picks.begin(), picks.end(), pick) != picks.end() ){
				pick = rand()%TRUMPS_NUM;
			}
			while( find(picks2.begin(), picks2.end(), pick2) != picks2.end() ){
				pick2 = rand()%TRUMPS_NUM;
			}
			picks.push_back( pick );
			picks2.push_back( pick2 );

			// ظ���
			trumps[i] = new Trump(GI("TRUMPX"), GI("TRUMPY"), graphics[i], pick, pick2, this);
			GAMECONTROL->GetMobManager()->Request(trumps[i], true);
		}
	}

	//! @see ActionState
	bool Update(){

		// �I������
		// ���ׂĂ�����߂��������玟�̋�����
		for( int i=0; i<TRUMPS_NUM; i++ ){
			if( trumps[i] ){
				return false;
			}
		}
		return true;		
	}

	//! @see ActionState
	void BuildAnimation(ActionState* rPrevAction)
	{
		mAnimation = Animation::ParseFromFile( "data\\animdata\\queen\\TrumpsAttack.txt" );
	}
	
	//! ����ޯ�: �g�����v��������
	void TrumpHasFallen(Trump* rTrump)
	{
		for( int i=0; i<4; i++ ){
			if ( trumps[i] == rTrump ){
				trumps[i] = NULL;
			}
		}
	}

	//! ���̐F
	static Kagami::Color GetColor()
	{ 
		return Kagami::Color(0.0f,0.0f,1.0f); 
	}

	

private:
	// �����
	Trump* trumps[TRUMPS_NUM];
};
//
///****************************************************************//**
//*	�����ر�������ė���E�З͋�
//*
//*	\nosubgrouping
//********************************************************************/
//class ASQueenChandelierAttackStrong: public ASQueenChandelierAttack
//{
//public: 
//	void OnEnter(){ 
//		ASQueenChandelierAttack::OnEnter();
//		mChandelier->SetStage(true);
//	}
//};
