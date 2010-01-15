#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\..\\Object\\Ashiba.h"

//! ｼｬﾝﾃﾞﾘｱ
/****************************************************************//**
*	頭に気をつけるべし
*	\nosubgrouping
********************************************************************/
class Chandelier : public Ashiba
{

public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	Chandelier();

	//! @see Movable
	void Move();
	//! @see Ashiba
	void Draw();
	
	//! ｸﾛｰﾝ
	Chandelier* Clone();

	//! 動作が終わったか
	bool IsStopped();


	//! 設定定数を設定する
	void SetStage(bool rStrong);


	//! 落とす
	void Drop();
	//! 引き戻す
	void PickUp();

	//! 当たり対応
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId);

	//! ｵｰﾊﾞｰﾗｲﾄﾞ
	void RespDown(IRideCapable* rider, Rect* jbound){}
	void RespLeft(IRideCapable* rider, Rect* jbound){}
	void RespRight(IRideCapable* rider, Rect* jbound){}

private:

	// ﾒｿｯﾄﾞ
	void Fall();
	void Floor();
	void Raise();

	// ｽﾃｰﾀｽ
	enum {
		STOP,
		FALL,
		FLOOR,
		RAISE
	} mStatus;

	float mTimer;

	// 設定定数
	int CHANDCHAINDX;
	int CHANDCHAINDY;
	int CHANDCHAINSX;
	int CHANDCHAINSY;

	float CHANDRAISESP;
	float CHANDWTTIME;
	
	int FLOORY;
	float GRAVITY;
};
