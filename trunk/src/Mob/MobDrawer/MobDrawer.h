#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

//! �`��
/****************************************************************//**
*	�`��̕��@��������޼ު��
*	\nosubgrouping
********************************************************************/
class MobDrawer
{

public:

	//! �`��̕��@
	virtual void Draw() = 0;

	//! ���̵�޼ު�Ă̺�߰��Ԃ��܂�
	virtual MobDrawer* Clone() = 0;
};
