#pragma once

#include "Teki.h"

class Koumori : public Teki, public LightResponseAble
{
public:
	Koumori(int rXPx, int rYPx);
	~Koumori(void);

	void _Move(); // 敵から

	TEKI_SETUP;
	
	// LightResponsableの架空ﾒｿｯﾄﾞ
	void ResponseAka();
	void ResponseAo();
	void ResponseMidori();
	void ResponseMushoku();
	void NoLight() {}

	int GetAtHtPointX() { return Teki::CenterX(); }
	int GetAtHtPointY() { return Teki::CenterY(); }

	void RunTask();

private:
	enum STATUS
	{
		WAIT,
		MOVE,
		NIGE
	} mStatus;

	bool mIsSEStopped;

	// 関数
	float DetermineShosoku(float rRaiseForce);
	void Nigeru();

	//! オーバーライド
	void Die();

	// 設定定数
	int MAAI_HABA;
	float KOMORAISE;
	float KOMOSPX;
	int KOMOCHOTEN;
};
