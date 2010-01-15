#pragma once

#include "..\\Mob\\Collidable.h"
#include "..\\Mob\\LightResponseAble.h"
#include "..\\MapCollision\\PointMapCollider.h"
#include "..\\Animation\\AnimationSet.h"
#include "..\\Mob\\MobDrawer\\SimpleDrawer.h"
#include "..\\Management\\GameControl.h"

//! �������l
/****************************************************************//**
*	���ۏ��l�ł��B
*	�p������ҁAײĉ����Ƹ��̨���������擾������@���������邪�ǂ��B
*	\nosubgrouping
********************************************************************/
class MikataKobito : public Collidable, public LightResponseAble
{
public:
	MikataKobito(int rXPx, int rYPx);
	virtual ~MikataKobito(void);

	// ���̨�����̐ݒ�(�ݽ�׸��ŌĂׂւ�� T-T)
	void Build();

	void Move();
	void RunTask(){ Collidable::RunTask(); LightResponseAble::RunTask(); }

	int GetAtHtPointX() { return mX + mSizeX/2; }
	int GetAtHtPointY() { return mY + mSizeY/2; }

	//! ���̨������
	virtual string GetWalkGraphic() = 0;
	virtual string GetThrowGraphic() = 0;
	virtual string GetJumpGraphic() = 0;

	// �����蔻��Ȃ�
	void CollisionResponse( ICollidable* rCollObject, int rThisGroup, int rOpGroupId ){}

	enum STATUS
	{
		WALK,
		THROW,
		JUMP
	};

protected:
	
	// ��{
	STATUS	mStatus;

	// ϯ�ߓ����蔻��
	PointMapCollider* mMapCollider;
	// ��Ұ��
	AnimationSet* mAnimSet;
	// �`��
	SimpleDrawer* mMobDrawer;

	// �������
	int mUrotsuki;

	// �Ƃ炳�ꎞ��
	float mLightTimer;
	float mWalkTimer;


	// �ݒ�萔
	float MKOBITO_LTIME;
	float MKOBITO_WTIME;

};

//! �������l�E��
/****************************************************************//**
*	�ԏ��l�ł��B
*	\nosubgrouping
********************************************************************/
class MikataKobitoRed : public MikataKobito
{
public:
	MikataKobitoRed(int rXPx, int rYPx) : MikataKobito( rXPx, rYPx ){}
	string GetWalkGraphic() { return "graphics\\object\\mkobito_walk_b.png"; }
	string GetThrowGraphic() { return "graphics\\object\\mkobito_throw_b.png"; }
	string GetJumpGraphic() { return "graphics\\object\\mkobito_jump_b.png"; }

	// LightResponsable�̉ˋ�ҿ���
	void ResponseAka(){ mLightTimer+=SP->FrameTime; }
	void ResponseAo(){ mLightTimer = 0.0f; }
	void ResponseMidori(){ mLightTimer = 0.0f; }
	void ResponseMushoku(){ mLightTimer = 0.0f; }
	void NoLight(){ mLightTimer = 0.0f; }
};

//! �������l�E��
/****************************************************************//**
*	���l�ł��B
*	\nosubgrouping
********************************************************************/
class MikataKobitoBlue : public MikataKobito
{
public:
	MikataKobitoBlue(int rXPx, int rYPx) : MikataKobito( rXPx, rYPx ){}
	string GetWalkGraphic() { return "graphics\\object\\mkobito_walk_a.png"; }
	string GetThrowGraphic() { return "graphics\\object\\mkobito_throw_a.png"; }
	string GetJumpGraphic() { return "graphics\\object\\mkobito_jump_a.png"; }

	// LightResponsable�̉ˋ�ҿ���
	void ResponseAka(){ mLightTimer = 0.0f; }
	void ResponseAo(){ mLightTimer+=SP->FrameTime; }
	void ResponseMidori(){ mLightTimer = 0.0f; }
	void ResponseMushoku(){ mLightTimer = 0.0f; }
	void NoLight(){ mLightTimer = 0.0f; }
};

//! �������l�E��
/****************************************************************//**
*	���l�ł��B
*	\nosubgrouping
********************************************************************/
class MikataKobitoGreen : public MikataKobito
{
public:
	MikataKobitoGreen(int rXPx, int rYPx) : MikataKobito( rXPx, rYPx ){}
	string GetWalkGraphic() { return "graphics\\object\\mkobito_walk_c.png"; }
	string GetThrowGraphic() { return "graphics\\object\\mkobito_throw_c.png"; }
	string GetJumpGraphic() { return "graphics\\object\\mkobito_jump_c.png"; }

	// LightResponsable�̉ˋ�ҿ���
	void ResponseAka(){ mLightTimer = 0.0f; }
	void ResponseAo(){ mLightTimer = 0.0f; }
	void ResponseMidori(){ mLightTimer+=SP->FrameTime; }
	void ResponseMushoku(){ mLightTimer = 0.0f; }
	void NoLight(){ mLightTimer = 0.0f; }
};
