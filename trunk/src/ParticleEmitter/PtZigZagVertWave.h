#pragma once

#include "Particle.h"
#include "..\\Management\\Gamecontrol.h"

//! ���E�޸޻޸ނ̔g�ɓ����߰è��
/****************************************************************//**
*	\see ParticleEmitter
*	\nosubgrouping
********************************************************************/
class PtZigZagVertWave : public Particle
{

public:
	PtZigZagVertWave () : Particle() { 
		Reset(); 
		FIREPART_ZZHABA = GF("FIREPART_ZZHABA");
		FIREPART_ZZSOKUDO = GF("FIREPART_ZZSOKUDO");
	}
	~PtZigZagVertWave (void){}

	//! �ʒu�ɑ��x�𑫂�����
	void UpdatePos() {
		
		// ���h
		if( !mInited){
			WAIT_TIMER(mZigZagTimer, FIREPART_ZZHABA/2)
				mAcc *= -1;
				mInited = true;
			WAIT_END
		}
		else{
			WAIT_TIMER(mZigZagTimer, FIREPART_ZZHABA)
				mAcc *= -1;
			WAIT_END
		}

		// ���x�̑�������
		mCurVel += mAcc;
		Particle::UpdatePos();
	}

	//! �ŏ�����
	void Reset(){
		mAcc = D3DXVECTOR3((((float)rand()/RAND_MAX)-0.5f)*FIREPART_ZZSOKUDO,0,0);
		mZigZagTimer = 0.0f;
		mInited = false;
	}

	//! ����
	void SetLifeTimePlus( float rLifeTimePlus ) { mLifeTimePlus = rLifeTimePlus; }
	float GetLifeTimePlus() { return mLifeTimePlus; }

protected:
	D3DXVECTOR3 mAcc;		//!< �����x
	float mZigZagTimer;		//!< �޸޻޸ޓ]���܂ł̎���
	bool mInited;			//!< ���ڂ̓��h�͔����̎��Ԃ̂���
	float mLifeTimePlus;	//!< ����ɂ��Ă��������܂ł̋���

	// �ݒ�萔
	float FIREPART_ZZHABA;
	float FIREPART_ZZSOKUDO;


};
