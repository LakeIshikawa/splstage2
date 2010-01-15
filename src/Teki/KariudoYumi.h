#pragma once

#include "Teki.h"

/*
	‹|‚ğ‚Á‚½ël
	–î‚ğ”„‚Á‚Ä‚­‚é
*/
class KariudoYumi : public Teki
{
public:
	KariudoYumi(int rXPx, int rYPx);
	~KariudoYumi(void);

	void _Move(); // “G‚©‚ç

	void Move();
	void Die();
	void Draw();

	TEKI_SETUP;
	

private:
	float mShootTimer;
	
	enum STATUS {
		WAIT1,
		SHOOT1,
		WAIT2,
		SHOOT2, 
		WAIT3,
		SHOOT3,
		IDLE,
		SHINDA
	}  
	mStatus;

	// ŠÖ”

	// İ’è’è”
	int KARIYUMISY;
	int KARIYUMISX;

	float KARIYUMI_WTM;
	float KARIYUMI_WTM2;
	int YUMITGT1;
	int YUMITGT2;
	float KARIYUMI_NKHI;
};
