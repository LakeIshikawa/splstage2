#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\Mob\\ActionControllable\\IActionThread.h"

//! ���G����
/****************************************************************//**
*	���G���Ԃ̕��s������S������گ��
*	\nosubgrouping
********************************************************************/
class MutekiJikan : public IActionThread
{

public:

	//! �W���ݽ�׸�
	MutekiJikan();

	//! @see ActionThread
	void Run();


	//! ���G���Ԃ�ݒ肷��
	void SetMutekiTime(float rTime);

	//! ����E���G�ɂ���
	void Start();
	//! ����
	bool IsMuteki();

	//! �۰�
	MutekiJikan* Clone();

private:
	float mTimer;
	float mMutekiTime;
	bool  mMutekiFl;
};
