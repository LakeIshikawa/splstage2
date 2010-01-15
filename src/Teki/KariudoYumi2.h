#pragma once

#include "Teki.h"

/*
	弓を持った狩人
	矢を売ってくる
*/
class KariudoYumi2 : public Teki
{
public:
	KariudoYumi2(int rXPx, int rYPx);
	~KariudoYumi2(void);

	void _Move(); // 敵から

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

	// 関数

	// 設定定数
	int KARIYUMI2SY;
	int KARIYUMI2SX;

	float KARIYUMI2_WTM;
	float KARIYUMI2_WTM2;
	int YUMI2TGT1;
	int YUMI2TGT2;
	float KARIYUMI2_NKHI;
};
