#pragma once

#include "..\\Mob\\Movable.h"
#include "..\\Mob\\MobDrawer\SimpleDrawer.h"
#include "..\\Animation\\Animation.h"

//! 光の粒
/****************************************************************//**
*	ﾋﾛｲﾝが必殺技に入る直前の演出
*	\nosubgrouping
********************************************************************/
class LightPart : public Movable
{

/****************************************************************//**
*	\name ﾗｲﾌ循環
********************************************************************/
/*@{*/
public:
	LightPart(int rXPx, int rYPx, float rSpX, float rSpY, float rSpAlpha, float rAlpha);
	~LightPart(void);

/*@}*/

/****************************************************************//**
*	\name 操作
********************************************************************/
/*@{*/
	
	//! 更新処理
	void Move();
	void RunTask(){}
	//! 描画
	void Draw();

	// ｺﾝｽﾄﾗｸﾀの直後に呼ぶべき
	virtual void Build() = 0;

protected:
	float mSpAlpha;
	float mAlpha;
	string mGraphic;

};

// 小さな粒
class LightPartSmall : public LightPart
{
public:
	LightPartSmall(int rXPx, int rYPx, float rSpX, float rSpY, float rSpAlpha, float rAlpha) :
	  LightPart(rXPx, rYPx, rSpX, rSpY, rSpAlpha, rAlpha){}
	void Build(){
		mGraphic = "graphics\\effect\\skill_effect1.png";
		mSizeX = 32;
		mSizeY = 32;
	}
};


// 大きな粒
class LightPartBig: public LightPart
{
public:
	LightPartBig(int rXPx, int rYPx, float rSpX, float rSpY, float rSpAlpha, float rAlpha) :
	  LightPart(rXPx, rYPx, rSpX, rSpY, rSpAlpha, rAlpha){}

	void Build(){
		mGraphic = "graphics\\effect\\skill_effect2.png";
		mSizeX = 48;
		mSizeY = 48;
	}
};


//! ﾁｬｰｼﾞｴﾌｪｸﾄ
/****************************************************************//**
*	ﾋﾛｲﾝが必殺技に入る直前の演出
*	\nosubgrouping
********************************************************************/
class ChargeEffect : public Movable
{

/****************************************************************//**
*	\name ﾗｲﾌ循環
********************************************************************/
/*@{*/
public:
	ChargeEffect(int rXPx, int rYPx);
	~ChargeEffect(void);

/*@}*/

/****************************************************************//**
*	\name 操作
********************************************************************/
/*@{*/
	
	//! 更新処理
	void Move();
	void RunTask(){}
	//! 描画
	void Draw();

	bool IsChargeCompleted();

/*@}*/

private:

	void CreateLightPartsCharge();
	void CreateLightPartsStill();

	float mAlpha;
	float mAlphaSp;

	enum STATUS{
		CHARGE,
		FADING,
		FADINGIN,
		USE
	} mStatus;

	float mTimer;
	
};
