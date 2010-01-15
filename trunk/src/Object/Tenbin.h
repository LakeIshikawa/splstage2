#include <exception>
using namespace std;

#pragma once

#include "AshibaTenbin.h"
#include "..\\Mob\\Movable.h"

class AshibaTenbin;


//! �V��
/****************************************************************//**
*	2�̑���������A���E�Ώ̂ɓ�����
*	\nosubgrouping
********************************************************************/
class Tenbin : public Movable
{

/****************************************************************//**
*	\name ײ̏z��
********************************************************************/
/*@{*/
public:

	Tenbin(int rXPx, int rYPx, float Z);
	virtual ~Tenbin(void);

/*@}*/

	//! �P�t���[���̏����B
	void Move();

	//! \param rHrSpacePx �V���̑��ꂪ����Ă��鉡
	void SetHrSpace(int rHrSpacePx);

	//! \param rVrSpacePx �V���̑��ꂪ����Ă���c
	void SetVrSpace(int rVrSpacePx);

	//! �g��Ȃ�
	void RunTask() {}

	//! �z�u��Ԃɖ߂�
	void Reset();

private:

	AshibaTenbin* mAshibaL;
	AshibaTenbin* mAshibaR;
	int mHrSpace;
	int mVrSpace;

};
