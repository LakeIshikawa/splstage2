#include <string>
#include <vector>
#include <exception>
#include <assert.h>
using namespace std;

#include "MutekiJikan.h"
#include "..\\Management\\GameControl.h"

/************************************************************//**
*	•W€ºÝ½Ä×¸À
****************************************************************/
MutekiJikan::MutekiJikan() {
	mTimer = -0.0f;
	mMutekiFl = false;
	mMutekiTime = -1.0f;
}

/************************************************************//**
*	ŽžŠÔ‚ðŒo‰ß‚³‚¹‚é
****************************************************************/
void MutekiJikan::Run() 
{
	verify(mMutekiTime >= 0);

	if( mMutekiFl ){
		// Œo‰ß
		mTimer += SP->FrameTime;

		// –³“GŽžŠÔI—¹ðŒ
		if( mTimer >= mMutekiTime ){
			mTimer = 0.0f;
			mMutekiFl = false;
		}
	}
}

/************************************************************//**
*	–³“GŽžŠÔ‚ÌÝ’è
****************************************************************/
void MutekiJikan::SetMutekiTime(float rTime) {
	mMutekiTime = rTime;
}

/************************************************************//**
*	–³“GŽžŠÔ‚ð½À°Ä
****************************************************************/
void MutekiJikan::Start() {
	mMutekiFl = true;
}

/************************************************************//**
*	\return –³“Gó‘Ô‚©
****************************************************************/
bool MutekiJikan::IsMuteki() {
	return mMutekiFl;
}


/************************************************************//**
*	\return ‚±‚ÌµÌÞ¼Þª¸Ä‚ÌºËß°
****************************************************************/
MutekiJikan* MutekiJikan::Clone() {

	MutekiJikan* mtjk = new MutekiJikan();

	// Ì¨°ÙÄÞ‚ÌºËß°
	mtjk->mMutekiFl = mMutekiFl;
	mtjk->mMutekiTime = mMutekiTime;
	mtjk->mTimer = mTimer;

	return mtjk;
}