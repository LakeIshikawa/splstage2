#pragma once

#include "LightKobito.h"
#include "..\\..\\..\\Management\\GameControl.h"

/*
	ê¬Ç≈éEÇ≥ÇÍÇÈ
*/
class LightKobitoRed : public virtual LightKobito
{
public:
	LightKobitoRed();
	LightKobitoRed( Majo* mParent );

	TEKI_SETUP;

	void _Move();

	void	ResponseAka();
	void	ResponseMidori(){}
	void	ResponseAo(){}
	void	ResponseMushoku(){}
	void	NoLight(){}

	int		GetAtHtPointX() { return mX + mSizeX/2; }
	int		GetAtHtPointY() { return mY + mSizeY/2; }

private:
	void Init();

};