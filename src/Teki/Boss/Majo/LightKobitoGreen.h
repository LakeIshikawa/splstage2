#pragma once

#include "LightKobito.h"
#include "..\\..\\..\\Management\\GameControl.h"

/*
	青で殺される
*/
class LightKobitoGreen : public LightKobito
{
public:
	LightKobitoGreen();
	LightKobitoGreen( Majo* mParent );

	TEKI_SETUP;

	void _Move();

	void	ResponseAka(){}
	void	ResponseMidori();
	void	ResponseAo(){}
	void	ResponseMushoku(){}
	void	NoLight(){}

	int		GetAtHtPointX() { return mX + mSizeX/2; }
	int		GetAtHtPointY() { return mY + mSizeY/2; }

private:
	void Init();

};