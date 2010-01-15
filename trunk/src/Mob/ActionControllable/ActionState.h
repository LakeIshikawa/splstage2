#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

class ActionControllable;
class MapCollider;
class ActionState;
class Animation;
class ICollidable;
class Collision;
class MobDrawer;

//! ｱｸｼｮﾝ
/****************************************************************//**
*	当たり判定、ｱﾆﾒｰｼｮﾝ、ﾏｯﾌﾟとの当たり判定と描画ができる
*	ActionControllableのｽﾃｰﾄの象徴。
*	これを拡張することで、実際の敵の動きを作る事ができます。
*	\nosubgrouping
********************************************************************/
class ActionState
{

public:

	//! 標準のｺﾝｽﾄﾗｸﾀ
	ActionState();
	//! 標準ﾃﾞｽﾄﾗｸﾀ
	virtual ~ActionState();


	//! ｽﾃｰﾄの初期状態を作る
	/****************************************************************//**
	*	ｽﾃｰﾄのﾃﾞｰﾀの作成
	*	\param rPrevState 終了したばかりのｽﾃｰﾄ
	********************************************************************/
	void BuildState(ActionState* rPrevState, ActionControllable* rParent);

	//! ｽﾃｰﾄの初期状態を作る(初期ﾊﾞｰｼﾞｮﾝ)
	/****************************************************************//**
	*	配置からｽﾃｰﾄのﾋﾞﾙﾄﾞ
	********************************************************************/
	void BuildState(int rStartX, int rStartY, ActionControllable* rParent);

protected:

	//! 当たり判定ｵﾌﾞｼﾞｪｸﾄの作る方法
	virtual void BuildCollision(ActionState* rPrevState) = 0;
	//! ﾏｯﾌﾟ当たり判定ｵﾌﾞｼﾞｪｸﾄの作る方法
	virtual void BuildMapCollider(ActionState* rPrevState) = 0;
	//! ｱﾆﾒｰｼｮﾝｵﾌﾞｼﾞｪｸﾄの作る方法
	virtual void BuildAnimation(ActionState* rPrevState) = 0;
	//! 描画方法ｵﾌﾞｼﾞｪｸﾄを作る方法
	virtual void BuildMobDrawer(ActionState* rPrevState) = 0;
	//! 派生ｸﾗｽの持っている特別情報をｺﾋﾟｰする方法
	virtual void BuildOtherInfo(ActionState* rPrevState) = 0;
	//! 位置情報の作る方法
	virtual void BuildPosInfo( ActionState* state );
	//! 初期ｽﾃｰﾄの位置情報を作る方法
	virtual void BuildPosInfo( int rX, int rY );


public:

	//! このｽﾃｰﾄがﾄﾘｯｶﾞされる時、一回呼ばれるｲﾍﾞﾝﾄﾊﾝﾄﾞﾗ
	virtual void OnEnter() = 0;
	//! 1ﾌﾚｰﾑの処理を示す方法
	virtual bool Update() = 0;
	//! このｽﾃｰﾄの処理が終了するとき、一回呼ばれる
	virtual void OnExit() = 0;

	
	//! 当たり判定の応答方法
	virtual void CollisionResponse(ICollidable* rCollObject, 
				int rThisGroupId, int rOpGroupId) = 0;


	//! 時間を経過させる
	void ElapseTime(float rElapsedTime);


	//! ｱｸｾｽ
	float GetX()		{ return mX; }
	//! ｱｸｾｽ
	float GetY()		{ return mY; }
	//! ｱｸｾｽ
	float GetSpX()		{ return mSpX; }
	//! ｱｸｾｽ
	float GetSpY()		{ return mSpY; }
	//! ｱｸｾｽ
	float GetAccX()		{ return mAccX; }
	//! ｱｸｾｽ
	float GetAccY()		{ return mAccY; }
	//! ｱｸｾｽ
	int GetFrameSizeX()	{ return mFrameSizeX; }
	//! ｱｸｾｽ
	int GetFrameSizeY() { return mFrameSizeY; }
	//! ｱｸｾｽ
	bool GetMuki()		{ return mMuki; }


	//! 親の取得
	ActionControllable* GetParent() { return mParent; }

	//! 当たり判定の取得
	Collision* GetCollision() { return mCollision; }
	//! ﾏｯﾌﾟあたり判定の取得
	MapCollider* GetMapCollider() { return mMapCollider; }
	//! ｱﾆﾒｰｼｮﾝの取得
	Animation* GetAnimation() { return mAnimation; }
	//! 描画方法の取得
	MobDrawer* GetMobDrawer() { return mMobDrawer; }


	//! 中断されたかを取得する
	bool WasInterrupted() { return mWasInterrupted; }
	//! 中断状態を設定する
	void SetInterrupted(bool rOnOff) { mWasInterrupted = rOnOff; }


protected: 
	ActionControllable* mParent;	//!< 親
	float mX;
	float mY;
	float mSpX;
	float mSpY;
	float mAccX;
	float mAccY;
	bool mMuki;
	int mFrameSizeX;
	int mFrameSizeY;
	bool mWasInterrupted;

	Collision* mCollision;
	Animation* mAnimation;
	MapCollider* mMapCollider;
	MobDrawer* mMobDrawer;

};
