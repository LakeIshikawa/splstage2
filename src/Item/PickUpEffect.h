#include <exception>
using namespace std;

#include "..\\Mob\\Movable.h"
#include "..\\Management\\GameControl.h"

#pragma once

//! ���ь���(���o)
/****************************************************************//**
*	���т��E�����Ƃ��̉��o�B
*	�۲݂̓�����o�āA������ōs���BN�߸�ً����𓮂�����A̪��ނ�
*	�����܂��B
*	\nosubgrouping
********************************************************************/
class PickUpEffect : public Movable
{
public: 

	//! �W���R���X�g���N�^
	PickUpEffect( string rGraphic );
	//! �W���f�X�g���N�^
	virtual ~PickUpEffect();

	//! �X�V
	void Move();
	void RunTask() {}

protected:
	string mGraphic;
	float mAlpha;

	// �ݒ�萔
	float ITEMFXFADESP;

};
