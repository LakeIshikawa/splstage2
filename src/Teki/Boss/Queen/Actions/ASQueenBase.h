#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once
#include "..\\..\\..\\..\\Mob\\ActionControllable\\ActionState.h"
#include "..\\..\\..\\..\\Units\\MutekiJikan.h"
#include "..\\FriendObjects\\Kagami.h"
#include "..\\FriendObjects\\Chandelier.h"
#include "..\\FriendObjects\\Rod.h"
#include "..\\FriendObjects\\AppleGenerator.h"

class ICollidable;

//! �����̊�{�ð�
/****************************************************************//**
*	�����ɂƂ��ĕW���̏������������B
*
*	\nosubgrouping
********************************************************************/
class ASQueenBase: virtual public ActionState
{

public:

	//! �W���ݽ�׸�
	ASQueenBase(){}
	//! �W���޽�׸�
	virtual ~ASQueenBase();


	//! @see ActionState
	virtual void BuildAnimation(ActionState* rPrevState);
	//! @see ActionState
	virtual void BuildCollision(ActionState* rPrevState);
	//! @see ActionState
	virtual void BuildMapCollider(ActionState* rPrevState);
	//! @see ActionState
	virtual void BuildMobDrawer(ActionState* rPrevState);
	//! @see ActionState
	virtual void BuildOtherInfo(ActionState* rPrevState);
	//! @see ActionState
	virtual void BuildPosInfo(ActionState* rPrevState);
	//! @see ActionState
	virtual void BuildPosInfo(int rX, int rY);
	
	//! @see ActionState
	virtual void OnExit();


	//! �W���̓����蔻�艞��
	virtual void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId);


	//! ����
	MutekiJikan* GetMutekiJikan();
	//! ����
	Kagami* GetKagami();
	//! ����
	Chandelier* GetChandelier();
	//! ����
	Rod* GetRod1();
	//! ����
	Rod* GetRod2();
	//! ����
	AppleGenerator* GetAppleGenerator1();
	//! ����
	AppleGenerator* GetAppleGenerator2();

	//! ����
	int GetPowerStage();

protected:
	// ���G
	MutekiJikan* mMutekiJikan;

	// ��
	Kagami* mKagami;

	// �����ر
	Chandelier* mChandelier;

	// ۯ��
	Rod* mRod1;
	Rod* mRod2;

	// �ݺ޼ު�ڰ�
	AppleGenerator* mAppleGenerator1; //��
	AppleGenerator* mAppleGenerator2; //�E
	
	// HP
	int mHp;

	// �З�
	int mPowerStage;

	// �ݒ�萔
	int QUEEN_STARTX;
	int QUEEN_STARTY;

};

