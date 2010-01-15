#pragma once

#include "Particle.h"
#include "..\\Management\\Gamecontrol.h"

//! ç∂âEºﬁ∏ﬁªﬁ∏ﬁÇÃîgÇ…ìÆÇ≠ ﬂ∞√®∏Ÿ
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

	//! à íuÇ…ë¨ìxÇë´ÇµÇ±Çﬁ
	void UpdatePos() {
		
		// ìÆóh
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

		// ë¨ìxÇÃë´ÇµÇ±Ç›
		mCurVel += mAcc;
		Particle::UpdatePos();
	}

	//! ç≈èâä˙âª
	void Reset(){
		mAcc = D3DXVECTOR3((((float)rand()/RAND_MAX)-0.5f)*FIREPART_ZZSOKUDO,0,0);
		mZigZagTimer = 0.0f;
		mInited = false;
	}

	//! ±∏æΩ
	void SetLifeTimePlus( float rLifeTimePlus ) { mLifeTimePlus = rLifeTimePlus; }
	float GetLifeTimePlus() { return mLifeTimePlus; }

protected:
	D3DXVECTOR3 mAcc;		//!< â¡ë¨ìx
	float mZigZagTimer;		//!< ºﬁ∏ﬁªﬁ∏ﬁì]ä∑Ç‹Ç≈ÇÃéûä‘
	bool mInited;			//!< àÍâÒñ⁄ÇÃìÆóhÇÕîºï™ÇÃéûä‘ÇÃÇΩÇﬂ
	float mLifeTimePlus;	//!< í∏è„Ç…Ç¬Ç¢ÇƒÇ©ÇÁè¡Ç¶ÇÈÇ‹Ç≈ÇÃãóó£

	// ê›íËíËêî
	float FIREPART_ZZHABA;
	float FIREPART_ZZSOKUDO;


};
