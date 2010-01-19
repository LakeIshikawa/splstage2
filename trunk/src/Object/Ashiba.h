#pragma once

#include "..\\Mob\\Collidable.h"

class Rect;
class IRideCapable;

//! ﾋﾛｲﾝが乗れるような足場
/****************************************************************//**
*	足場
*	\nosubgrouping
********************************************************************/
class Ashiba : public virtual Collidable
{

/****************************************************************//**
*	\name ﾗｲﾌ循環
********************************************************************/
/*@{*/
public:
	Ashiba(int rXPx, int rYPx, float Z, string rGraphic, int rSizeX, int rSizeY);
	virtual ~Ashiba(void);

protected:
	Ashiba() {}
/*@}*/

/****************************************************************//**
*	\name ｵｰﾊﾞｰﾗｲﾄﾞするﾒｿｯﾄﾞ
********************************************************************/
/*@{*/
public:

	//! 描画
	virtual void Draw();

	//! 当たり応答
	virtual void RespLeft(IRideCapable* rider, Rect* jbound);
	//! 当たり応答
	virtual void RespRight(IRideCapable* rider, Rect* jbound);
	//! 当たり応答
	virtual void RespUp(IRideCapable* rider, Rect* jbound);
	//! 当たり応答
	virtual void RespDown(IRideCapable* rider, Rect* jbound);

/*@}*/

/****************************************************************//**
*	\name 操作
********************************************************************/
/*@{*/

	//! 1ﾌﾚｰﾑ処理
	virtual void Move();

	//! 乗っている者の処理
	virtual void UpdateRiders();

	//! 当たり対応
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId);

	//! 乗る
	virtual void GetOn(IRideCapable* rRider);

	//! 降りる
	virtual void GetOff(IRideCapable* rRider);

	// ローストデバイス
	virtual void OnLostDevice(){}
	virtual void OnRestoredDevice(){}

/*@}*/


/****************************************************************//**
*	\name アクセス
********************************************************************/
/*@{*/

	//! 幅の取得
	int GetFrameSizeX();

	//! 縦幅の取得
	int GetFrameSizeY();

	//! X速度を取得
	float GetSpX();

	//! Y速度を取得
	float GetSpY();

	//! 当たり判定長方形を取得
	Rect* GetCollRect();
	
/*@}*/

protected:
	// 乗っている者
	list<IRideCapable*> mRiders;
	list<IRideCapable*> mDelRiders;

	// ｸﾞﾗﾌｨｯｸ
	string mGraphic;

	// 設定定数
	int ASHIBASX;
	int ASHIBASY;
};
