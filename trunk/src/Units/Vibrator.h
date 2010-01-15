#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

//! U“®
/****************************************************************//**
*	U“®‚ðŒvŽZ‚µ‚Ä‚­‚ê‚é
*	\nosubgrouping
********************************************************************/
class Vibrator
{

public:

	//! •W€ºÝ½Ä×¸À
	Vibrator(int rWidth, float rSpeed, float rTime){
		mVibWidth = rWidth;
		mVibSpeed = rSpeed;
		mVibTime = rTime;
		mActive = false;
		mCurPos = 0;
		mTimer = 0;
	}

	//! U“®
	void Vibrate(){

		if( mActive ){
			// U“®
			mCurPos += mVibSpeed;
			if( mVibSpeed > 0 && mCurPos >= mVibWidth ){
				mCurPos = mVibWidth;
				mVibSpeed *= -1;
			}
			else if( mVibSpeed < 0 && mCurPos <= -mVibWidth ){
				mCurPos = -mVibWidth;
				mVibSpeed *= -1;
			}
			// ŽžŠÔ§ŒÀ
			WAIT_TIMER(mTimer, mVibTime)
				mActive = false;
				mCurPos = 0;
			WAIT_END
		}
	}

	//! U“®ŠJŽn
	void StartVibrate(){
		mActive = true;
	}

	//! XÀ•W‚Ì·•ª‚ðŽæ“¾
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
