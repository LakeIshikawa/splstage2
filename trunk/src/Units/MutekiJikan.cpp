#include <string>
#include <vector>
#include <exception>
#include <assert.h>
using namespace std;

#include "MutekiJikan.h"
#include "..\\Management\\GameControl.h"

/************************************************************//**
*	標準ｺﾝｽﾄﾗｸﾀ
****************************************************************/
MutekiJikan::MutekiJikan() {
	mTimer = -0.0f;
	mMutekiFl = false;
	mMutekiTime = -1.0f;
}

/************************************************************//**
*	時間を経過させる
****************************************************************/
void MutekiJikan::Run() 
{
	verify(mMutekiTime >= 0);

	if( mMutekiFl ){
		// 経過
		mTimer += SP->FrameTime;

		// 無敵時間終了条件
		if( mTimer >= mMutekiTime ){
			mTimer = 0.0f;
			mMutekiFl = false;
		}
	}
}

/************************************************************//**
*	無敵時間の設定
****************************************************************/
void MutekiJikan::SetMutekiTime(float rTime) {
	mMutekiTime = rTime;
}

/************************************************************//**
*	無敵時間をｽﾀｰﾄ
****************************************************************/
void MutekiJikan::Start() {
	mMutekiFl = true;
}

/************************************************************//**
*	\return 無敵状態か
****************************************************************/
bool MutekiJikan::IsMuteki() {
	return mMutekiFl;
}


/************************************************************//**
*	\return このｵﾌﾞｼﾞｪｸﾄのｺﾋﾟｰ
****************************************************************/
MutekiJikan* MutekiJikan::Clone() {

	MutekiJikan* mtjk = new MutekiJikan();

	// ﾌｨｰﾙﾄﾞのｺﾋﾟｰ
	mtjk->mMutekiFl = mMutekiFl;
	mtjk->mMutekiTime = mMutekiTime;
	mtjk->mTimer = mTimer;

	return mtjk;
}