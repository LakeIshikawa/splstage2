#include <string>
#include <vector>
#include <stdarg.h>
using namespace std;

#include "AnimationSet.h"
#include "..\\Management\\GameControl.h"

/************************************************************//**
*	標準コンストラクタ
****************************************************************/
AnimationSet::AnimationSet()
{
	mCurIdx = 0;
}

/************************************************************//**
*	標準デストラクタ
****************************************************************/
AnimationSet::~AnimationSet()
{}

/************************************************************//**
*	\param rElapsedTime 前回からの経過時間
****************************************************************/
void AnimationSet::ElapseTime(float rElapsedTime)
{
	verify( mAnimations[mCurIdx] != NULL );
	
	// 時間を経過させる
	if( !mAnimations.empty() ){
		mAnimations[mCurIdx]->ElapseTime( rElapsedTime );
	}
}

/************************************************************//**
*	\param rIdx ｱﾆﾒｰｼｮﾝを象徴する整数。取得するにはこれを使用します。
*	\param rNewAnimation 追加見込みのｱﾆﾒｰｼｮﾝ
****************************************************************/
void AnimationSet::AddAnimation(int rIdx, Animation* rNewAnimation) 
{
	mAnimations[rIdx] = rNewAnimation;
}

/************************************************************//**
*	\param rIdx 取得したいｱﾆﾒｰｼｮﾝの番号
*	\return そのｱﾆﾒｰｼｮﾝ
****************************************************************/
Animation* AnimationSet::GetAnimation(int rIdx) 
{
	verify( mAnimations[rIdx] != NULL );
	return mAnimations[rIdx];
}

/************************************************************//**
*	\param rIdx 設定したいｱﾆﾒｰｼｮﾝの番号
****************************************************************/
void AnimationSet::SetCurAnimation(int rIdx)
{
	verify( mAnimations[rIdx] != NULL );
	mCurIdx = rIdx;
}

/************************************************************//**
*	\return 現在再生中のｱﾆﾒｰｼｮﾝ
****************************************************************/
Animation* AnimationSet::GetCurAnimation()
{
	verify( mAnimations[mCurIdx] != NULL );
	return mAnimations[mCurIdx];
}


/************************************************************//**
*	\return 現在再生中ｱﾆﾒｰｼｮﾝの番号
****************************************************************/
int AnimationSet::GetCurAnimationIdx()
{
	verify( mAnimations[mCurIdx] != NULL );
	return mCurIdx;
}