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
class OokamiHouseRog: public OokamiHouse
{

public:

	//! ���̨���̎擾���@
	string GetGraphicSrc() 
	{ 
		return "graphics\\teki\\ookami\\roghouse.png"; 
	}

	//! �j�мު�ڰ��̍쐬
	void BuildParticleGenerator()
	{
		mPtGenerator = new ParticleGenerator(mX + mSizeX/2, mY - mSizeY/2);
		mPtGenerator->BookPartThrow(D3DX_PI*14/9, 7.5f, 0.2f, "graphics\\teki\\ookami\\effect_debris3.png");
		mPtGenerator->BookPartThrow(D3DX_PI*46/36, 12.0f, 0.2f, "graphics\\teki\\ookami\\effect_debris4.png");
		mPtGenerator->BookPartThrow(D3DX_PI*13/9, 10.0f, 0.2f, "graphics\\teki\\ookami\\effect_debris3.png");
		mPtGenerator->BookPartThrow(D3DX_PI*33/18, 12.5f, 0.2f, "graphics\\teki\\ookami\\effect_debris4.png");
		mPtGenerator->BookPartThrow(D3DX_PI*315/180, 15.0f, 0.2f, "graphics\\teki\\ookami\\effect_debris3.png");
		mPtGenerator->BookPartThrow(D3DX_PI*17/9, 12.5f, 0.2f, "graphics\\teki\\ookami\\effect_debris4.png");

		mPtGenerator->SetMode(ParticleGenerator::PG_LINEAR);
	}

	// �����蔻�艞���Ȃ�
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId){}

};

