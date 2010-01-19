#pragma once

#include "..\\Mob\\Collidable.h"

class Rect;
class IRideCapable;

//! �۲݂�����悤�ȑ���
/****************************************************************//**
*	����
*	\nosubgrouping
********************************************************************/
class Ashiba : public virtual Collidable
{

/****************************************************************//**
*	\name ײ̏z��
********************************************************************/
/*@{*/
public:
	Ashiba(int rXPx, int rYPx, float Z, string rGraphic, int rSizeX, int rSizeY);
	virtual ~Ashiba(void);

protected:
	Ashiba() {}
/*@}*/

/****************************************************************//**
*	\name ���ްײ�ނ���ҿ���
********************************************************************/
/*@{*/
public:

	//! �`��
	virtual void Draw();

	//! �����艞��
	virtual void RespLeft(IRideCapable* rider, Rect* jbound);
	//! �����艞��
	virtual void RespRight(IRideCapable* rider, Rect* jbound);
	//! �����艞��
	virtual void RespUp(IRideCapable* rider, Rect* jbound);
	//! �����艞��
	virtual void RespDown(IRideCapable* rider, Rect* jbound);

/*@}*/

/****************************************************************//**
*	\name ����
********************************************************************/
/*@{*/

	//! 1�ڰя���
	virtual void Move();

	//! ����Ă���҂̏���
	virtual void UpdateRiders();

	//! ������Ή�
	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId);

	//! ���
	virtual void GetOn(IRideCapable* rRider);

	//! �~���
	virtual void GetOff(IRideCapable* rRider);

	// ���[�X�g�f�o�C�X
	virtual void OnLostDevice(){}
	virtual void OnRestoredDevice(){}

/*@}*/


/****************************************************************//**
*	\name �A�N�Z�X
********************************************************************/
/*@{*/

	//! ���̎擾
	int GetFrameSizeX();

	//! �c���̎擾
	int GetFrameSizeY();

	//! X���x���擾
	float GetSpX();

	//! Y���x���擾
	float GetSpY();

	//! �����蔻�蒷���`���擾
	Rect* GetCollRect();
	
/*@}*/

protected:
	// ����Ă����
	list<IRideCapable*> mRiders;
	list<IRideCapable*> mDelRiders;

	// ���̨��
	string mGraphic;

	// �ݒ�萔
	int ASHIBASX;
	int ASHIBASY;
};
