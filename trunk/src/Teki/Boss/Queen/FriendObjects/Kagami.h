#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\..\\Mob\\Movable.h"
#include "Hibi.h"
#include "..\\..\\..\\..\\Units\\Vibrator.h"

//! ��
/****************************************************************//**
*	���݂����ɂȂ��[
*	\nosubgrouping
********************************************************************/
class Kagami : public Movable
{

public:

	//! �F
	class Color{
	public :Color(float rr, float gg, float bb) : r(rr), g(gg), b(bb){}
		float r,g,b;
	};

	//! �W���ݽ�׸�
	Kagami();
	//! �W���޽�׸�
	~Kagami();

	//! @see Movable
	void Move();
	//! @see Movable
	void RunTask(){}


	//! ���̂悤�ɔ�����
	void StartShuffle();
	//! ���̂悤�c
	void StopShuffle();
	//! �h���
	void StartVibrate();

	//! �w���RGB�ɐݒ肷��
	void SetToColor( Color col );

	//! 㟂̒i�K
	void SetHibiStage(int st);

	//! @see IPositionable
	float GetX() { return mX + mVibrator->GetCurWidth(); }


	//! ����ٌ���
	int GetShuffleLoops() { return mShuffleLoops; }

	
	//! �۰�
	Kagami* Clone();

private:

	// ���̂悤��
	void Shuffle();

	// �ð��
	enum {
		STOP,
		SHUFFLE
	} mStatus;

	// �(���)
	Hibi* mHibi;

	int mShuffleStage;
	int mShuffleLoops;

	Vibrator* mVibrator;

	// �F
	float mR;
	float mG;
	float mB;

	float KAGAMI_NIJISP;
};
