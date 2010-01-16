#pragma once

#include "Collidable.h"
#include "MobDrawer\\SimpleDrawer.h"
#include "..\\Animation\\AnimationSet.h"

//! ����Ѱ�ް�Ȃǂŏo�Ă���悤�ȱ�Ұ��݉\�ȃG���e�B�e�B
/****************************************************************//**
*	��Ұ��݂Ɠ����蔻��������āA�O���瑀�삳���悤��Mob
*	��{�I�ɐ��~�I�ȱ�Ұ��݁E����Ѱ�ް�Ŏg���ƕ֗��ł�
*	\nosubgrouping
********************************************************************/
class MovieActor : public virtual Collidable
{

/****************************************************************//**
*	\name ײ̏z��
********************************************************************/
/*@{*/
public:
	MovieActor(int rSizeX, int rSizeY);
	virtual ~MovieActor(void);

protected:
	MovieActor() {}
/*@}*/

/****************************************************************//**
*	\name ���ްײ�ނ���ҿ���
********************************************************************/
/*@{*/
public:

	//! �`��
	void Draw();

/*@}*/

/****************************************************************//**
*	\name ����
********************************************************************/
/*@{*/

	//! 1�ڰя���
	void Move();

	//! ������Ή�
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId);


/*@}*/


/****************************************************************//**
*	\name �A�N�Z�X
********************************************************************/
/*@{*/

	//! ����
	AnimationSet* GetAnimationSet();

	//! �۲݂ɓ������Ă��邩
	bool IsJikiColliding();
	
/*@}*/

protected:
	AnimationSet* mAnimSet;
	SimpleDrawer* mSDrawer;

	bool mJikiColliding;
};
