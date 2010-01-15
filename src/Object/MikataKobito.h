#pragma once

#include "..\\Mob\\Collidable.h"
#include "..\\Mob\\LightResponseAble.h"
#include "..\\MapCollision\\PointMapCollider.h"
#include "..\\Animation\\AnimationSet.h"
#include "..\\Mob\\MobDrawer\\SimpleDrawer.h"
#include "..\\Management\\GameControl.h"

//! 見方小人
/****************************************************************//**
*	抽象小人です。
*	継承たる者、ﾗｲﾄ応答とｸﾞﾗﾌｨｯｸ資源を取得する方法を実装するが良い。
*	\nosubgrouping
********************************************************************/
class MikataKobito : public Collidable, public LightResponseAble
{
public:
	MikataKobito(int rXPx, int rYPx);
	virtual ~MikataKobito(void);

	// ｸﾞﾗﾌｨｯｸ源の設定(ｺﾝｽﾄﾗｸﾀで呼べへんで T-T)
	void Build();

	void Move();
	void RunTask(){ Collidable::RunTask(); LightResponseAble::RunTask(); }

	int GetAtHtPointX() { return mX + mSizeX/2; }
	int GetAtHtPointY() { return mY + mSizeY/2; }

	//! ｸﾞﾗﾌｨｯｸ資源
	virtual string GetWalkGraphic() = 0;
	virtual string GetThrowGraphic() = 0;
	virtual string GetJumpGraphic() = 0;

	// 当たり判定なし
	void CollisionResponse( ICollidable* rCollObject, int rThisGroup, int rOpGroupId ){}

	enum STATUS
	{
		WALK,
		THROW,
		JUMP
	};

protected:
	
	// 基本
	STATUS	mStatus;

	// ﾏｯﾌﾟ当たり判定
	PointMapCollider* mMapCollider;
	// ｱﾆﾒｰﾀｰ
	AnimationSet* mAnimSet;
	// 描画
	SimpleDrawer* mMobDrawer;

	// うろつき回数
	int mUrotsuki;

	// 照らされ時間
	float mLightTimer;
	float mWalkTimer;


	// 設定定数
	float MKOBITO_LTIME;
	float MKOBITO_WTIME;

};

//! 見方小人・赤
/****************************************************************//**
*	赤小人です。
*	\nosubgrouping
********************************************************************/
class MikataKobitoRed : public MikataKobito
{
public:
	MikataKobitoRed(int rXPx, int rYPx) : MikataKobito( rXPx, rYPx ){}
	string GetWalkGraphic() { return "graphics\\object\\mkobito_walk_b.png"; }
	string GetThrowGraphic() { return "graphics\\object\\mkobito_throw_b.png"; }
	string GetJumpGraphic() { return "graphics\\object\\mkobito_jump_b.png"; }

	// LightResponsableの架空ﾒｿｯﾄﾞ
	void ResponseAka(){ mLightTimer+=SP->FrameTime; }
	void ResponseAo(){ mLightTimer = 0.0f; }
	void ResponseMidori(){ mLightTimer = 0.0f; }
	void ResponseMushoku(){ mLightTimer = 0.0f; }
	void NoLight(){ mLightTimer = 0.0f; }
};

//! 見方小人・青
/****************************************************************//**
*	青小人です。
*	\nosubgrouping
********************************************************************/
class MikataKobitoBlue : public MikataKobito
{
public:
	MikataKobitoBlue(int rXPx, int rYPx) : MikataKobito( rXPx, rYPx ){}
	string GetWalkGraphic() { return "graphics\\object\\mkobito_walk_a.png"; }
	string GetThrowGraphic() { return "graphics\\object\\mkobito_throw_a.png"; }
	string GetJumpGraphic() { return "graphics\\object\\mkobito_jump_a.png"; }

	// LightResponsableの架空ﾒｿｯﾄﾞ
	void ResponseAka(){ mLightTimer = 0.0f; }
	void ResponseAo(){ mLightTimer+=SP->FrameTime; }
	void ResponseMidori(){ mLightTimer = 0.0f; }
	void ResponseMushoku(){ mLightTimer = 0.0f; }
	void NoLight(){ mLightTimer = 0.0f; }
};

//! 見方小人・青
/****************************************************************//**
*	青小人です。
*	\nosubgrouping
********************************************************************/
class MikataKobitoGreen : public MikataKobito
{
public:
	MikataKobitoGreen(int rXPx, int rYPx) : MikataKobito( rXPx, rYPx ){}
	string GetWalkGraphic() { return "graphics\\object\\mkobito_walk_c.png"; }
	string GetThrowGraphic() { return "graphics\\object\\mkobito_throw_c.png"; }
	string GetJumpGraphic() { return "graphics\\object\\mkobito_jump_c.png"; }

	// LightResponsableの架空ﾒｿｯﾄﾞ
	void ResponseAka(){ mLightTimer = 0.0f; }
	void ResponseAo(){ mLightTimer = 0.0f; }
	void ResponseMidori(){ mLightTimer+=SP->FrameTime; }
	void ResponseMushoku(){ mLightTimer = 0.0f; }
	void NoLight(){ mLightTimer = 0.0f; }
};
