#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\..\\Object\\Ashiba.h"

//! �����ر
/****************************************************************//**
*	���ɋC������ׂ�
*	\nosubgrouping
********************************************************************/
class Chandelier : public Ashiba
{

public:

	//! �W���ݽ�׸�
	Chandelier();

	//! @see Movable
	void Move();
	//! @see Ashiba
	void Draw();
	
	//! �۰�
	Chandelier* Clone();

	//! ���삪�I�������
	bool IsStopped();


	//! �ݒ�萔��ݒ肷��
	void SetStage(bool rStrong);


	//! ���Ƃ�
	void Drop();
	//! �����߂�
	void PickUp();

	//! ������Ή�
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId);

	//! ���ްײ��
	void RespDown(IRideCapable* rider, Rect* jbound){}
	void RespLeft(IRideCapable* rider, Rect* jbound){}
	void RespRight(IRideCapable* rider, Rect* jbound){}

private:

	// ҿ���
	void Fall();
	void Floor();
	void Raise();

	// �ð��
	enum {
		STOP,
		FALL,
		FLOOR,
		RAISE
	} mStatus;

	float mTimer;

	// �ݒ�萔
	int CHANDCHAINDX;
	int CHANDCHAINDY;
	int CHANDCHAINSX;
	int CHANDCHAINSY;

	float CHANDRAISESP;
	float CHANDWTTIME;
	
	int FLOORY;
	float GRAVITY;
};
