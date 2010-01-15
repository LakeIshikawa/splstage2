#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "MobDrawer.h"
#include "IAlphaCapable.h"

class Animation;
class IPositionable;

//! �P���ȕ`��
/****************************************************************//**
*	�ʒu�Ʊ�Ұ��݂̏������킹��DX�ŕ`����s���܂�
*	\nosubgrouping
********************************************************************/
class SimpleDrawer : public MobDrawer
{

public:

	//! �W���ݽ�׸�
	SimpleDrawer();

	//! �`��̕��@
	void Draw();

	//! ���̵�޼ު�Ă̺�߰��Ԃ��܂�
	MobDrawer* Clone();


	//! ��Ұ��ݵ�޼ު�Ă̐ݒ�
	void SetAnimation( Animation* rAnimation );
	//! �ʒu�擾���@�̐ݒ�
	void SetPositionInfo( IPositionable* rPositionInfo );
	//! ��̧�l�̐ݒ�
	void SetAlphaSrc( IAlphaCapable* rAlphaCapable );


private:
	Animation* mAnimation;			//!< ��Ұ���
	IPositionable* mPositionInfo;	//!< �ʒu���
	IAlphaCapable* mAlphaCapable;	//!< ��̧��޼ު��
};
