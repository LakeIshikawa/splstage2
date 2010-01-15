#pragma once

/*
	ÉQÅ[ÉÄíÜÇ…ã§í ÇÃíËêî
*/
class SharedParams
{
public:
	SharedParams();
	~SharedParams();

	int SCRSZX;
	int SCRSZY;

	int CHSZY;
	int CHSZX;
	int CHIPNX;
	int CHIPNY;
	int CHNLN;

	int GRID_BOGYO;
	int GRID_KOUGEKI;
	int GRID_HANTEN;
	int GRID_ITO;
	int GRID_BOUND;
	int GRID_HOUSE;

	float FrameTime;
	int FRAMERATE;

	int CHIP_NOHIT;
	int CHIP_HIT;
	int CHIP_AMHIT;
	int CHIP_KGHIT;
	int CHIP_GMNGAIRT;
	int CHIP_GMNGAILT;
	int CHIP_GMNGAIUP;
	int CHIP_GMNGAIDN;

	float GRAVITY;

	int HEROINE_NO;
};