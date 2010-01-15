#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "OokamiHouse.h"

//! �Ƃ̊�{�׽
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class OokamiHouseBrick: public OokamiHouse
{

public:

	//! �W���ݽ�׸�
	OokamiHouseBrick();

	//! ���̨���̎擾���@
	string GetGraphicSrc() 
	{ 
		return "graphics\\teki\\ookami\\brickhouse.png"; 
	}

	//! ����
	void Disappear();


	//! �j�мު�ڰ��̍쐬(�Ȃ�)
	void BuildParticleGenerator() {}

	//! �����蔻�艞���Ȃ�
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId);

};

