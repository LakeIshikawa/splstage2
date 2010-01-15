#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\Mob\\Collidable.h"
#include "ParticleGenerator.h"

//! �Ƃ̊�{�׽
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class OokamiHouse: public Collidable
{

public:

	//! �W���ݽ�׸�
	OokamiHouse();
	//! �W���޽�׸�
	~OokamiHouse();


	//! �o���ʒu��ݒ�
	void SetPosX(int rX);
	//! ���ł�����
	void Destroy();
	
	//! �o��
	void Appear();
	//! ����
	virtual void Disappear();
	//! �j�А�����į��
	void StopParticles();

	//! 1�ڰя���
	void Move();

	//! ���̨���̎擾���@
	virtual string GetGraphicSrc() = 0;
	//! �j�мު�ڰ��̍����@
	virtual void BuildParticleGenerator() = 0;

protected:
	//! �o����������
	float mAppearedHeight;
	float mAlpha;

	ParticleGenerator* mPtGenerator;

	//! �ð��
	enum{
		APPEARING,
		DISAPPEARING
	} mStatus;

	int OOKAMI_HSSP;

};

