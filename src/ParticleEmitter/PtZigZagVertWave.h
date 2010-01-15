#pragma once

#include "Particle.h"
#include "..\\Management\\Gamecontrol.h"

//! 左右ｼﾞｸﾞｻﾞｸﾞの波に動くﾊﾟｰﾃｨｸﾙ
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

	//! 位置に速度を足しこむ
	void UpdatePos() {
		
		// 動揺
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

		// 速度の足しこみ
		mCurVel += mAcc;
		Particle::UpdatePos();
	}

	//! 最初期化
	void Reset(){
		mAcc = D3DXVECTOR3((((float)rand()/RAND_MAX)-0.5f)*FIREPART_ZZSOKUDO,0,0);
		mZigZagTimer = 0.0f;
		mInited = false;
	}

	//! ｱｸｾｽ
	void SetLifeTimePlus( float rLifeTimePlus ) { mLifeTimePlus = rLifeTimePlus; }
	float GetLifeTimePlus() { return mLifeTimePlus; }

protected:
	D3DXVECTOR3 mAcc;		//!< 加速度
	float mZigZagTimer;		//!< ｼﾞｸﾞｻﾞｸﾞ転換までの時間
	bool mInited;			//!< 一回目の動揺は半分の時間のため
	float mLifeTimePlus;	//!< 頂上についてから消えるまでの距離

	// 設定定数
	float FIREPART_ZZHABA;
	float FIREPART_ZZSOKUDO;


};
