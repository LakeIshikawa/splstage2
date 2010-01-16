#pragma once

#include "Collidable.h"
#include "MobDrawer\\SimpleDrawer.h"
#include "..\\Animation\\AnimationSet.h"

//! ｼｮｰﾄﾑｰﾋﾞｰなどで出てくるようなｱﾆﾒｰｼｮﾝ可能なエンティティ
/****************************************************************//**
*	ｱﾆﾒｰｼｮﾝと当たり判定を持って、外から操作されるようなMob
*	基本的に制止的なｱﾆﾒｰｼｮﾝ・ｼｮｰﾄﾑｰﾋﾞｰで使うと便利です
*	\nosubgrouping
********************************************************************/
class MovieActor : public virtual Collidable
{

/****************************************************************//**
*	\name ﾗｲﾌ循環
********************************************************************/
/*@{*/
public:
	MovieActor(int rSizeX, int rSizeY);
	virtual ~MovieActor(void);

protected:
	MovieActor() {}
/*@}*/

/****************************************************************//**
*	\name ｵｰﾊﾞｰﾗｲﾄﾞするﾒｿｯﾄﾞ
********************************************************************/
/*@{*/
public:

	//! 描画
	void Draw();

/*@}*/

/****************************************************************//**
*	\name 操作
********************************************************************/
/*@{*/

	//! 1ﾌﾚｰﾑ処理
	void Move();

	//! 当たり対応
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId);


/*@}*/


/****************************************************************//**
*	\name アクセス
********************************************************************/
/*@{*/

	//! ｱｸｾｽ
	AnimationSet* GetAnimationSet();

	//! ﾋﾛｲﾝに当たっているか
	bool IsJikiColliding();
	
/*@}*/

protected:
	AnimationSet* mAnimSet;
	SimpleDrawer* mSDrawer;

	bool mJikiColliding;
};
