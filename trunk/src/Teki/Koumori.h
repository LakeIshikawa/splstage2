#pragma once

#include "Teki.h"

class Koumori : public Teki, public LightResponseAble
{
public:
	Koumori(int rXPx, int rYPx);
	~Koumori(void);

	void _Move(); // “G‚©‚ç

	TEKI_SETUP;
	
	// LightResponsable‚Ì‰Ë‹óÒ¿¯ÄŞ
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

	// ŠÖ”
	float DetermineShosoku(float rRaiseForce);
	void Nigeru();

	// İ’è’è”
	int KOMOSX;
	int KOMOSY;

	int MAAI_HABA;
	float KOMORAISE;
	float KOMOSPX;
	int KOMOCHOTEN;
};
