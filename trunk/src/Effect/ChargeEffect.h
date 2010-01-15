#pragma once

#include "..\\Mob\\Movable.h"
#include "..\\Mob\\MobDrawer\SimpleDrawer.h"
#include "..\\Animation\\Animation.h"

//! ���̗�
/****************************************************************//**
*	�۲݂��K�E�Z�ɓ��钼�O�̉��o
*	\nosubgrouping
********************************************************************/
class LightPart : public Movable
{

/****************************************************************//**
*	\name ײ̏z��
********************************************************************/
/*@{*/
public:
	LightPart(int rXPx, int rYPx, float rSpX, float rSpY, float rSpAlpha, float rAlpha);
	~LightPart(void);

/*@}*/

/****************************************************************//**
*	\name ����
********************************************************************/
/*@{*/
	
	//! �X�V����
	void Move();
	void RunTask(){}
	//! �`��
	void Draw();

	// �ݽ�׸��̒���ɌĂԂׂ�
	virtual void Build() = 0;

protected:
	float mSpAlpha;
	float mAlpha;
	string mGraphic;

};

// �����ȗ�
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


// �傫�ȗ�
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


//! ����޴̪��
/****************************************************************//**
*	�۲݂��K�E�Z�ɓ��钼�O�̉��o
*	\nosubgrouping
********************************************************************/
class ChargeEffect : public Movable
{

/****************************************************************//**
*	\name ײ̏z��
********************************************************************/
/*@{*/
public:
	ChargeEffect(int rXPx, int rYPx);
	~ChargeEffect(void);

/*@}*/

/****************************************************************//**
*	\name ����
********************************************************************/
/*@{*/
	
	//! �X�V����
	void Move();
	void RunTask(){}
	//! �`��
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
