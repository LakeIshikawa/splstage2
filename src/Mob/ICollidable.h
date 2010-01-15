#include <exception>
using namespace std;

#pragma once

#include "IPositionable.h"

class Collision;

//! �����蔻��ɉ����ł���C���^�[�t�F�[�X
/****************************************************************//**
*	�����蔻��̎d���Ɋ֌W�Ȃ��A�������o����N���X�ւ̃C���^�[�t�F�[�X
*	\nosubgrouping
********************************************************************/
class ICollidable : public virtual IPositionable
{

	public: 
		//! �����蔻�艞��
		/************************************************************//**
		*	�^�[�Q�b�g�I�u�W�F�N�g�ɂԂ������Ƃ��ɌĂ΂��R�[���o�b�N
		*	\param rCollObject �Ԃ���������
		*	\param rThisGroupID ���̵�޼ު�Ă̂Ԃ����������̸�ٰ��ID
		*	\param rThisGroupID �����޼ު�Ă̂Ԃ����������̸�ٰ��ID
		****************************************************************/
		virtual void CollisionResponse(ICollidable* rCollObject, 
			int rThisGroupId, int rOpGroupId) = 0;

		//! ���t���[���̎擾���@
		virtual Collision* GetCurFrame() = 0;

		// ���ޯĂ̎w��
		virtual void AddTarget(ICollidable* rTarget) = 0;
		virtual void RemoveTarget(ICollidable* rTarget) = 0;
};
