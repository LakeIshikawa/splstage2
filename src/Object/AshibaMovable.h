#pragma once

#include "Ashiba.h"
#include <d3dx9.h>

//! ���C�g�𓖂Ă�Ƃ����������Ȃ�����
/****************************************************************//**
*	����E�Ƃ炳��Ă��Ȃ��ƌ����Ȃ��o�[�W����
*	\nosubgrouping
********************************************************************/
class AshibaMovable : public virtual Ashiba
{
	
private:
	//! ���ꂪ�ړ����郋�[�g�̃m�[�h
	class RoutePoint
	{
	public:
		RoutePoint(int rX, int rY){X = rX; Y= rY;}
		int X;
		int Y;
	};

/****************************************************************//**
*	\name ײ̏z��
********************************************************************/
/*@{*/
public:
	AshibaMovable(int rXPx, int rYPx, float Z, string graphic, int sizex, int sizey);
	virtual ~AshibaMovable(void);
/*@}*/

	//! �v���Z�X
	void Move();

	//! ���[�g�m�[�h
	void AddRoutePoint(int card, int rX, int rY);

	//! ���[�v�̐ݒ�
	void SetLooping(bool rOnOff);

	//! �z�u�̎��̏�Ԃɖ߂�
	void Reset();

protected:

	//! �ړ�
	void _Move();

	//! ��������
	bool HasArrived();

	//! ���̃m�[�h�ɐ؂�ւ���
	void GoToNext();

	//! ٰ�ߗp��ɰ�ނ��擾
	int GetLoopNodeIdx();

	// �ݒ�萔
	float ASHIBAMOV_SP;

	RoutePoint* route[17];
	int	mCurRPoint;
	bool mLooping;
	bool mBacking;

	// �z�u���W
	int mHaichiX;
	int mHaichiY;

};
