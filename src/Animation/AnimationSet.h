#include <map>
using namespace std;

#include "Animation.h"

#pragma once

//! ｱﾆﾒｰｼｮﾝｾｯﾄ
/****************************************************************//**
*	複数のｱﾆﾒｰｼｮﾝへのｲﾝﾀｰﾌｪｰｽを提供します
*	\nosubgrouping
********************************************************************/
class AnimationSet
{
	public: 

		//! 標準コンストラクタ
		AnimationSet();
		//! 標準デストラクタ
		~AnimationSet();


		//! 操作・時間を経過させる
		void ElapseTime(float rElapsedTime);
		
		
		//! ｱﾆﾒｰｼｮﾝの追加
		void AddAnimation( int rIdx, Animation* rNewAnimation );
		//! ｱﾆﾒｰｼｮﾝの取得
		Animation* GetAnimation( int rIdx );

		//! 再生見込みｱﾆﾒｰｼｮﾝの設定
		void SetCurAnimation( int rIdx );
		//! 現在再生中のｱﾆﾒｰｼｮﾝの取得
		Animation* GetCurAnimation();
		//! 現在再生中ｱﾆﾒｰｼｮﾝの番号の取得
		int GetCurAnimationIdx();

	private: 
		map< int, Animation* > mAnimations;
		int mCurIdx;
};

