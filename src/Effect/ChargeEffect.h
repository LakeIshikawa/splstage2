#pragma once

#include "..\\Mob\\Movable.h"
#include "..\\Mob\\MobDrawer\SimpleDrawer.h"
#include "..\\Animation\\Animation.h"

//! υΜ±
/****************************************************************//**
*	ΛΫ²έͺKEZΙόιΌOΜo
*	\nosubgrouping
********************************************************************/
class LightPart : public Movable
{

/****************************************************************//**
*	\name Χ²ΜzΒ
********************************************************************/
/*@{*/
public:
	LightPart(int rXPx, int rYPx, float rSpX, float rSpY, float rSpAlpha, float rAlpha);
	~LightPart(void);

/*@}*/

/****************************************************************//**
*	\name μ
********************************************************************/
/*@{*/
	
	//! XV
	void Move();
	void RunTask(){}
	//! `ζ
	void Draw();

	// Ίέ½ΔΧΈΐΜΌγΙΔΤΧ«
	virtual void Build() = 0;

protected:
	float mSpAlpha;
	float mAlpha;
	string mGraphic;

};

// ¬³Θ±
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


// ε«Θ±
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


//! Α¬°Όή΄ΜͺΈΔ
/****************************************************************//**
*	ΛΫ²έͺKEZΙόιΌOΜo
*	\nosubgrouping
********************************************************************/
class ChargeEffect : public Movable
{

/****************************************************************//**
*	\name Χ²ΜzΒ
********************************************************************/
/*@{*/
public:
	ChargeEffect(int rXPx, int rYPx);
	~ChargeEffect(void);

/*@}*/

/****************************************************************//**
*	\name μ
********************************************************************/
/*@{*/
	
	//! XV
	void Move();
	void RunTask(){}
	//! `ζ
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
