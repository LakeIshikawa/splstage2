#pragma once

#include "LightKobito.h"
#include "..\\..\\Management\\GameControl.h"

/*
	青で殺される
*/
class LightKobitoRed : public LightKobito
{
public:
	LightKobitoRed();
	LightKobitoRed( Majo* mParent );
	~LightKobitoRed();

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