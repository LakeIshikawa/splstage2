#pragma once

#include "..\\Mob\\Collidable.h"
#include "..\\Mob\\IRideCapable.h"
#include "..\\MapCollision\\PointMapCollider.h"
#include "..\\Collision\\CollisionSet.h"

class TekkyuStand;

//! 鉄球
/****************************************************************//**
*	出現してから、下に落ち、床に当たると跳ね返りながら左方向に
*	転がります。
*	- ﾋﾛｲﾝにあたったらﾀﾞﾒｰｼﾞを与える
*	- 壁や仲間に当たったらとまる
*	- 足場に乗る
*	\nosubgrouping
********************************************************************/
class Tekkyu : public Collidable, public IRideCapable
{

/****************************************************************//**
*	\name ﾗｲﾌ循環
********************************************************************/
/*@{*/
public:
	Tekkyu(int rXPx, int rYPx, float Z, TekkyuStand* rParent);
	virtual ~Tekkyu(void);
/*@}*/

/****************************************************************//**
*	\name ｵｰﾊﾞｰﾗｲﾄﾞするﾒｿｯﾄﾞ
********************************************************************/
/*@{*/
public:
/*@}*/

/****************************************************************//**
*	\name 操作
********************************************************************/
/*@{*/

	//! 1ﾌﾚｰﾑ処理
	virtual void Move();

	//! 当たり対応
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId);

/*@}*/

/****************************************************************//**
*	\name IRideCapableの実装
********************************************************************/
/*@{*/
	
	//! 足場に乗るための長方形の取得方法
	Rect* GetRideRect() { return (Rect*)pCollision->GetCurFrame()->GetIndexedShape(0); }

	//! 速度の取得方法
	float GetSpX() { return mSpX; }

	//! 速度の取得方法
	float GetSpY() { return mSpY; }

	//! 位置の調整
	void SetX(int rNewX) { mX = rNewX; }

	//! 位置の調整
	void SetY(int rNewY) { mY = rNewY; }

	//! 速度の調整
	void SetSpX(float rNewSpX) { mSpX = rNewSpX; }

	//! 速度の調整
	void SetSpY(float rNewSpY) { mSpY = rNewSpY; }


	//! 速度の加算
	void AddSpX(float rAddSpX) { mAddSpX = rAddSpX; }

	//! 乗ったときのｺｰﾙﾊﾞｯｸ
	void RideResponse(Ashiba* rAshiba) { mAshiba = rAshiba; }

	//! 降りたときのｺｰﾙﾊﾞｯｸ
	void GetOffResponse(Ashiba* rAshiba) { mAshiba = NULL; }
/*@}*/


/****************************************************************//**
*	\name アクセス
********************************************************************/
/*@{*/
/*@}*/

protected:

	//! 描画
	void Draw();

	//! 重力の影響で落ち、何かにぶつかったらそこで静止する
	void Fall();

	//! 地面に当たったら転がる
	void RollIfHitGround();

	//! 地面に当たっているか
	bool IsHittingGround();

	//! 回る回る
	void Kaiten();

	//! ﾊﾞｳﾝﾄﾞ
	void Rebound();

	//! 何かにぶつかったら止まる
	void StopIfHitWall();

	//! とまってから数秒たったら死ぬ
	void DieIfStopAndNSec();

	//! ｱﾙﾌｧでﾌｪｰﾄﾞｱｳﾄし、消滅
	void Disappear();


	// 措置
	TekkyuStand* mParent;

	// ﾏｯﾌﾟあたり判定
	PointMapCollider* mMapCollision;

	// 回転用
	float mAngle;

	// ｱﾙﾌｧ
	float mAlpha;

	// 消えるまでのﾀｲﾏｰ
	float mDieTimer;

	// 足場からもらう速度
	float mAddSpX;

	// 足場に乗っているか
	Ashiba* mAshiba;

	// 音声用:UGLY:
	bool mIsRolling;

	// ｽﾃｰﾀｽ
	enum STATUS{
		GENERATE,
		FALL,
		ROLLING,
		STOP,
		DIE
	} mStatus;

	// 設定定数
	float TEKKYU_SHOMETSUTIME;
};
