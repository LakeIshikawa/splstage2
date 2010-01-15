#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

//! 振動
/****************************************************************//**
*	振動を計算してくれる
*	\nosubgrouping
********************************************************************/
class Vibrator
{

public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	Vibrator(int rWidth, float rSpeed, float rTime){
		mVibWidth = rWidth;
		mVibSpeed = rSpeed;
		mVibTime = rTime;
		mActive = false;
		mCurPos = 0;
		mTimer = 0;
	}

	//! 振動
	void Vibrate(){

		if( mActive ){
			// 振動
			mCurPos += mVibSpeed;
			if( mVibSpeed > 0 && mCurPos >= mVibWidth ){
				mCurPos = mVibWidth;
				mVibSpeed *= -1;
			}
			else if( mVibSpeed < 0 && mCurPos <= -mVibWidth ){
				mCurPos = -mVibWidth;
				mVibSpeed *= -1;
			}
			// 時間制限
			WAIT_TIMER(mTimer, mVibTime)
				mActive = false;
				mCurPos = 0;
			WAIT_END
		}
	}

	//! 振動開始
	void StartVibrate(){
		mActive = true;
	}

	//! X座標の差分を取得
	float GetCurWidth(){
		return mCurPos;
	}

private:
	int mVibWidth;
	float mVibSpeed;
	float mVibTime;

	bool mActive;
	float mTimer;

	float mCurPos;
};
