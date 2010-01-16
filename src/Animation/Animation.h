#include <exception>
using namespace std;

#pragma once

//! ｱﾆﾒｰｼｮﾝ
/****************************************************************//**
*	ひとつのｱﾆﾒｰｼｮﾝに必要な処理やデータをラップします
*	\nosubgrouping
********************************************************************/
class Animation
{
	public: 

		//! ｱﾆﾒｰｼｮﾝﾓｰﾄﾞ
		/****************************************************************//**
		*	ｱﾆﾒｰｼｮﾝの基本的な再生の仕方を示す
		*	\nosubgrouping
		********************************************************************/
		enum ANIM_MODE
		{
			ANMD_LOOP,			//!< ループ再生
			ANMD_STOPATEND		//!< 一回再生、最後にﾌﾘｰｽﾞ
		};

		//! 標準コンストラクタ
		Animation();
		//! 標準デストラクタ
		~Animation();

		//! ｸﾛｰﾝ方法
		Animation* Clone();


		//! 操作・時間を経過させる
		void ElapseTime(float rElapsedTime);
		//! ｱﾆﾒｰｼｮﾝデータの指定
		void SetAnimData(int rFirst, ...);
		//! ﾌﾚｰﾑとﾌﾚｰﾑの間の時間の指定
		void SetAnimIntervals(float rFirst, ...);
		//! ｱﾆﾒｰｼｮﾝﾓｰﾄﾞの設定
		void SetAnimMode(ANIM_MODE rMode);
		//! ｸﾞﾗﾌｨｯｸ名の指定
		void SetGraphicSource(string rGraphicSource);
		//! ループの開始番号を設定する
		void SetLoopStartIdx(int rLoopStartIdx);
		//! 回転角度を設定する
		void SetRotAngle(float rAngle);

		//! 操作・巻き戻し
		void Rewind();

		//! 現在ﾌﾚｰﾑの取得
		int GetCurFrameIdx();
		//! ﾙｰﾌﾟ回数の取得
		int GetLoopCount();
		//! ｸﾞﾗﾌｨｯｸ源の取得
		string GetGraphicSource();
		//! 回転角度
		float GetRotAngle();

		//! ｱﾆﾒｰｼｮﾝﾌｧｲﾙから設定のﾊﾟｰｽ
		static Animation* ParseFromFile(string rPath);

	private: 
		float	mElapsedTime;
		int		mFrameIdx;
		int		mLoopStartIdx;

		vector<int> mAnimData;
		vector<float> mAnimIntervals;

		float mRotAngle;

		ANIM_MODE mMode;
		string mGraphicSource;

		int mLoopCount;
};

