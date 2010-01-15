#pragma once

#include "Teki.h"

/*
	‹|‚ğ‚Á‚½ël
	–î‚ğ”„‚Á‚Ä‚­‚é
*/
class KariudoYumi3 : public Teki
{
public:
	KariudoYumi3(int rXPx, int rYPx);
	~KariudoYumi3(void);

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
	int KARIYUMI3SY;
	int KARIYUMI3SX;

	float KARIYUMI3_WTM;
	float KARIYUMI3_WTM2;
	int YUMI3TGT1;
	int YUMI3TGT2;
	float KARIYUMI3_NKHI;
};
