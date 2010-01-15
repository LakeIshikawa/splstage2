#pragma once

#include <string>
using namespace std;

#include "ParticleEmitter.h"
#include "PtZigZagVertWave.h"

//! �Β��^�߰��ٔ������u
/****************************************************************//**
*	��葬�x�B
*	�㉺�̂݁B
*	�߰Â��ِ���ø�����w���
*	\nosubgrouping
********************************************************************/
class PeHibashira : public ParticleEmitter
{
public:

	/****************************************************************//**
*	\name ײ̏z��
********************************************************************/
/*@{*/
	PeHibashira(int rX, int rY, int rNumParticles, string rTexture, 
		int rWidth, int rHeight, bool rUpdown);
	~PeHibashira(void);
/*@}*/


public:

	//! 1�ڰя���
	void Update();
	//! �߰è�ق̏�����
	void InitParticles(D3DCOLOR rColor);
	//! ��s�𔭎˂���
	void FireLine();

	//! �߰è�ق̎擾���@
	Particle* GetParticle(int rIdx) { return &mParticles[rIdx]; }

protected:
	//! ������ϰ
	float mFireTimer;

	//! �Β��̉���
	int mWidth;
	//! �Β��̏c��
	int mHeight;

	//! �߰è��
	PtZigZagVertWave* mParticles;

	//! �㉺
	bool mUpDown;

	// �ݒ�萔
	int HIBASHIRA_LNPART;
	float HIBASHIRA_FIREINT;
	float HIBASHIRA_BASESPX;
	float HIBASHIRA_PTLFTIME;

};
