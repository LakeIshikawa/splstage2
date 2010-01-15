#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

//! �U��
/****************************************************************//**
*	�U�����v�Z���Ă����
*	\nosubgrouping
********************************************************************/
class Vibrator
{

public:

	//! �W���ݽ�׸�
	Vibrator(int rWidth, float rSpeed, float rTime){
		mVibWidth = rWidth;
		mVibSpeed = rSpeed;
		mVibTime = rTime;
		mActive = false;
		mCurPos = 0;
		mTimer = 0;
	}

	//! �U��
	void Vibrate(){

		if( mActive ){
			// �U��
			mCurPos += mVibSpeed;
			if( mVibSpeed > 0 && mCurPos >= mVibWidth ){
				mCurPos = mVibWidth;
				mVibSpeed *= -1;
			}
			else if( mVibSpeed < 0 && mCurPos <= -mVibWidth ){
				mCurPos = -mVibWidth;
				mVibSpeed *= -1;
			}
			// ���Ԑ���
			WAIT_TIMER(mTimer, mVibTime)
				mActive = false;
				mCurPos = 0;
			WAIT_END
		}
	}

	//! �U���J�n
	void StartVibrate(){
		mActive = true;
	}

	//! X���W�̍������擾
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
