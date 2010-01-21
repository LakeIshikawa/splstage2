#pragma once

#include "..\\Mob\\Collidable.h"
#include "..\\Mob\\IRideCapable.h"
#include "..\\MapCollision\\PointMapCollider.h"
#include "..\\Collision\\CollisionSet.h"

class TekkyuStand;

//! �S��
/****************************************************************//**
*	�o�����Ă���A���ɗ����A���ɓ�����ƒ��˕Ԃ�Ȃ��獶������
*	�]����܂��B
*	- �۲݂ɂ�����������Ұ�ނ�^����
*	- �ǂ⒇�Ԃɓ���������Ƃ܂�
*	- ����ɏ��
*	\nosubgrouping
********************************************************************/
class Tekkyu : public Collidable, public IRideCapable
{

/****************************************************************//**
*	\name ײ̏z��
********************************************************************/
/*@{*/
public:
	Tekkyu(int rXPx, int rYPx, float Z, TekkyuStand* rParent);
	virtual ~Tekkyu(void);
/*@}*/

/****************************************************************//**
*	\name ���ްײ�ނ���ҿ���
********************************************************************/
/*@{*/
public:
/*@}*/

/****************************************************************//**
*	\name ����
********************************************************************/
/*@{*/

	//! 1�ڰя���
	virtual void Move();

	//! ������Ή�
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId);

/*@}*/

/****************************************************************//**
*	\name IRideCapable�̎���
********************************************************************/
/*@{*/
	
	//! ����ɏ�邽�߂̒����`�̎擾���@
	Rect* GetRideRect() { return (Rect*)pCollision->GetCurFrame()->GetIndexedShape(0); }

	//! ���x�̎擾���@
	float GetSpX() { return mSpX; }

	//! ���x�̎擾���@
	float GetSpY() { return mSpY; }

	//! �ʒu�̒���
	void SetX(int rNewX) { mX = rNewX; }

	//! �ʒu�̒���
	void SetY(int rNewY) { mY = rNewY; }

	//! ���x�̒���
	void SetSpX(float rNewSpX) { mSpX = rNewSpX; }

	//! ���x�̒���
	void SetSpY(float rNewSpY) { mSpY = rNewSpY; }


	//! ���x�̉��Z
	void AddSpX(float rAddSpX) { mAddSpX = rAddSpX; }

	//! ������Ƃ��̺���ޯ�
	void RideResponse(Ashiba* rAshiba) { mAshiba = rAshiba; }

	//! �~�肽�Ƃ��̺���ޯ�
	void GetOffResponse(Ashiba* rAshiba) { mAshiba = NULL; }
/*@}*/


/****************************************************************//**
*	\name �A�N�Z�X
********************************************************************/
/*@{*/
/*@}*/

protected:

	//! �`��
	void Draw();

	//! �d�͂̉e���ŗ����A�����ɂԂ������炻���ŐÎ~����
	void Fall();

	//! �n�ʂɓ���������]����
	void RollIfHitGround();

	//! �n�ʂɓ������Ă��邩
	bool IsHittingGround();

	//! �����
	void Kaiten();

	//! �޳���
	void Rebound();

	//! �����ɂԂ�������~�܂�
	void StopIfHitWall();

	//! �Ƃ܂��Ă��琔�b�������玀��
	void DieIfStopAndNSec();

	//! ��̧��̪��ޱ�Ă��A����
	void Disappear();


	// �[�u
	TekkyuStand* mParent;

	// ϯ�߂����蔻��
	PointMapCollider* mMapCollision;

	// ��]�p
	float mAngle;

	// ��̧
	float mAlpha;

	// ������܂ł���ϰ
	float mDieTimer;

	// ���ꂩ����炤���x
	float mAddSpX;

	// ����ɏ���Ă��邩
	Ashiba* mAshiba;

	// �����p:UGLY:
	bool mIsRolling;

	// �ð��
	enum STATUS{
		GENERATE,
		FALL,
		ROLLING,
		STOP,
		DIE
	} mStatus;

	// �ݒ�萔
	float TEKKYU_SHOMETSUTIME;
};
