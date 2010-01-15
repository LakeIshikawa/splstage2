#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

class IPositionable;

//! ��ʏ��𓾂���悤�ȵ�޼ު�Ă��ے����܂�
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class IPositionable
{

public:

	//! ��ʂ̐��X���W���擾������@
	virtual float GetX() = 0;

	//! ��ʂ̐��Y���W���擾������@
	virtual float GetY() = 0;

	//! ��޼ު�Ă̌������擾������@ (0=�E 1=��)
	virtual bool GetMuki() = 0;

	//! �O���t�B�b�N�̈�t���[���̉������擾������@
	virtual int GetFrameSizeX() = 0;

	//! �O���t�B�b�N�̈�t���[���̏c�����擾������@
	virtual int GetFrameSizeY() = 0;
};
