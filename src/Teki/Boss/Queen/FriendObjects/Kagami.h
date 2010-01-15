#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\..\\Mob\\Movable.h"
#include "Hibi.h"
#include "..\\..\\..\\..\\Units\\Vibrator.h"

//! 鏡
/****************************************************************//**
*	虹みたいになるよー
*	\nosubgrouping
********************************************************************/
class Kagami : public Movable
{

public:

	//! 色
	class Color{
	public :Color(float rr, float gg, float bb) : r(rr), g(gg), b(bb){}
		float r,g,b;
	};

	//! 標準ｺﾝｽﾄﾗｸﾀ
	Kagami();
	//! 標準ﾃﾞｽﾄﾗｸﾀ
	~Kagami();

	//! @see Movable
	void Move();
	//! @see Movable
	void RunTask(){}


	//! 虹のように美しく
	void StartShuffle();
	//! 虹のよう…
	void StopShuffle();
	//! 揺れる
	void StartVibrate();

	//! 指定のRGBに設定する
	void SetToColor( Color col );

	//! 罅の段階
	void SetHibiStage(int st);

	//! @see IPositionable
	float GetX() { return mX + mVibrator->GetCurWidth(); }


	//! ｼｬｯﾌﾙ現回数
	int GetShuffleLoops() { return mShuffleLoops; }

	
	//! ｸﾛｰﾝ
	Kagami* Clone();

private:

	// 虹のように
	void Shuffle();

	// ｽﾃｰﾀｽ
	enum {
		STOP,
		SHUFFLE
	} mStatus;

	// 罅(ﾋﾋﾞ)
	Hibi* mHibi;

	int mShuffleStage;
	int mShuffleLoops;

	Vibrator* mVibrator;

	// 色
	float mR;
	float mG;
	float mB;

	float KAGAMI_NIJISP;
};
