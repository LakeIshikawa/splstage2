#pragma once

#include "..\\Mob\\Movable.h"
#include "..\\Mob\\MobDrawer\SimpleDrawer.h"
#include "..\\Animation\\Animation.h"

//! �Ō��̪��
/****************************************************************//**
*	�۲݂̍U����������Ƃ��̴̪��
*	\nosubgrouping
********************************************************************/
class HitEffect : public Movable
{

/****************************************************************//**
*	\name ײ̏z��
********************************************************************/
/*@{*/
public:
	HitEffect(int rXPx, int rYPx);
	~HitEffect(void);

/*@}*/

/****************************************************************//**
*	\name ����
********************************************************************/
/*@{*/
	
	//! �X�V����
	void Move();
	void RunTask(){}
	//! �`��
	void Draw();

/*@}*/


protected:
	// ��Ұ���
	Animation* mAnim;
	// �`��
	SimpleDrawer* mSDrawer;
	
};
