#include <exception>
using namespace std;

#pragma once

#include "Movable.h"
#include "ICollidable.h"
#include "..\\Collision\\Collision.h"
#include "..\\Collision\\CollisionDrawer.h"

class CollidableSingleFrame;

//! �����蔻��\��Mob�̒P�t���[����
/****************************************************************//**
*	�p������N���X��Collision�̒P��t���[�����w�肵�܂��B
*	���̃N���X��ActionControllable��{�N���X�̂��߂ɍ���Ă���܂��B
*	\see ActionControllable
*	\nosubgrouping
********************************************************************/
class CollidableSingleFrame: public Movable, public ICollidable
{
public:

	//! �W���ݽ�׸�
	CollidableSingleFrame();

	//! �����蔻��̎��s
	void RunTask();

	//! �����蔻��̃^�[�Q�b�g��ǉ�����
	void AddTarget(ICollidable* rTarget);

	//! �����蔻��̃^�[�Q�b�g����������
	void RemoveTarget(ICollidable* rTarget);

	//! ����̃t���[�����擾������@
	virtual Collision* GetCurFrame() = 0;

	//! �����蔻��̉���
	virtual void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId) = 0;

	protected: 
		list<ICollidable*> mlTargets;
		CollisionDrawer* mDrawer;
};
