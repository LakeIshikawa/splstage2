#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once


//! ��̧�`��̉\�ȵ�޼ު��
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class IAlphaCapable
{

public:

	//! ��̧�l�̎擾���@������
	virtual float GetAlpha() = 0;

};
