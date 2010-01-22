#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\CollidableSingleFrame.h"
#include "IActionThread.h"

class ActionState;
class ActionThread;

//! ｱｸｼｮﾝに基づいたMob
/****************************************************************//**
*	当たり判定、ﾏｯﾌﾟとの当たり判定、ｱﾆﾒｰｼｮﾝ・描画と動きができる
*	物体。ｱｸｼｮﾝ事態がこのｸﾗｽのことが
*	\nosubgrouping
********************************************************************/
class ActionControllable: public CollidableSingleFrame
{
	public: 

		//! 標準ｺﾝｽﾄﾗｸﾀ
		ActionControllable();
		//! 標準ﾃﾞｽﾄﾗｸﾀ
		virtual ~ActionControllable();
		

		//! 1ﾌﾚｰﾑ処理
		void Move();
		//! 当たり判定んも取得方法
		Collision* GetCurFrame();


		//! ｱｸｼｮﾝの割り込み
		void BreakInAction(ActionState* rNewState);
		//! ｱｸｼｮﾝをｷｭｰに追加
		void QueueAction(ActionState* rNewState);
		//! ｱｸｼｮﾝを次のｱｸｼｮﾝとして登録
		void AddNextAction(ActionState* rNewState);
		//! 現ｱｸｼｮﾝを強制終了させ、割り込む
		void BreakInActionNoResume(ActionState* rNewState);
		//! すべてのｱｸｼｮﾝを削除
		void RemoveAllActions(ActionState* rExclude);

		//! ﾗﾝﾀﾞﾑでｼｬｯﾌﾙ(
		void ShuffleActions();

		//! 先頭のｱｸｼｮﾝｽﾃｰﾄを返す
		ActionState* GetFirstState();

		//! 当たり判定応答
		void CollisionResponse(ICollidable* rCollObject, int rThisGroupID, int rOpGroupID);


		//! IPositionableｲﾝﾀｰﾌｪｰｽの実装
		int GetFrameSizeX();
		//! IPositionableｲﾝﾀｰﾌｪｰｽの実装
		int GetFrameSizeY();
		//! IPositionableｲﾝﾀｰﾌｪｰｽの実装
		float GetX();
		//! IPositionableｲﾝﾀｰﾌｪｰｽの実装
		float GetY();
		//! IPositionableｲﾝﾀｰﾌｪｰｽの実装
		bool GetMuki();

		//! IDrawableｲﾝﾀｰﾌｪｰｽの実装
		string GetGraphicSource();
		//! IDrawableｲﾝﾀｰﾌｪｰｽの実装
		int GetAnimFrame();
		

		//! 新ｽﾃｰﾄの作成
		/****************************************************************//**
		*	ｷｭｰが空になった時に呼ばれる。
		*	\param rLastState 最後に保たれたｽﾃｰﾄ
		********************************************************************/
		virtual void AddNewStates(ActionState* rLastState) = 0;
		//! 配置直後の初期ｽﾃｰﾄの作成
		virtual void AddInitStates(int rX, int rY) = 0;

		//! 平行処理を行うｽﾚｯﾄﾞの登録
		void AddThread(IActionThread* rThread);
		//! ｽﾚｯﾄﾞを解除する
		void RemoveThread(IActionThread* rThread);

		//! 消滅状態にする
		void SetDead(){ mIsDead = true; }


	protected: 
		list<ActionState*> mStates;		//!< ｽﾃｰﾄのｷｭｰ
		list<IActionThread*> mThreads;	//!< ｽﾚｯﾄﾞ

		bool mIsDead;					//!< 消滅したか
};
