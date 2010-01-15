#pragma once

#include "..\\Mob\\Collidable.h"
#include "..\\ParticleEmitter\\ParticleEmitter.h"

//! ���o���΂̑��u
/****************************************************************//**
*	�΂��o���܂��B
*	- ��ʓ��ɓ����Ă���N�b��ɍŏ��ɔ���
*	\nosubgrouping
********************************************************************/
class FireStand : public Collidable
{

/****************************************************************//**
*	\name ײ̏z��
********************************************************************/
/*@{*/
public:
	FireStand(int rXPx, int rYPx, float Z, bool rUpDown);
	virtual ~FireStand(void);
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

	//! �΂𕬏o��
	void ProduceFire();

	//! ������Ή�
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId);

/*@}*/

protected:

	//! �`��
	void Draw();

	//! ���蒷���`�𒲐�
	void AdjustCollision();
	void FadeInCollision();
	void FadeOutCollision();


	// �߰è�ٴЯ�
	ParticleEmitter* mEmitter;

	// ��ϰ
	float mProdTimer;

	// ����(�㉺)
	bool mUpDown;
	
	// �ð��
	enum STATUS{
		WAIT,
		FIRE
	} mStatus;

	// �����蔻��p
	float mFireTop;
	float mFireBottom;
	int flag;

	// �ݒ�萔
	float FIRESTD_PRODTIME;
	float HIBASHIRA_HEIGHT;
	float HIBASHIRA_BASESPX;

};
