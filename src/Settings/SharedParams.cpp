#include "SharedParams.h"
#include "..\\Management\\GameControl.h"

SharedParams::SharedParams()
{
	SCRSZX = GI("SCRSZX");
	SCRSZY = GI("SCRSZY");

	CHSZX = GI("CHSZX");
	CHSZY = GI("CHSZY");
	CHIPNX = GI("CHIPNX");
	CHIPNY = GI("CHIPNY");
	CHNLN = GI("CHNLN");

	GRID_BOGYO = GI("GRID_BOGYO");
	GRID_KOUGEKI = GI("GRID_KOUGEKI");
	GRID_HANTEN = GI("GRID_HANTEN");
	GRID_ITO = GI("GRID_ITO");
	GRID_BOUND = GI("GRID_BOUND");

	FrameTime = GF("FrameTime");
	FRAMERATE = GI("FRAMERATE");

	CHIP_NOHIT = GI("CHIP_NOHIT");
	CHIP_HIT = GI("CHIP_HIT");
	CHIP_AMHIT = GI("CHIP_AMHIT");
	CHIP_KGHIT = GI("CHIP_KGHIT");
	CHIP_GMNGAIRT = GI("CHIP_GMNGAIRT");
	CHIP_GMNGAILT = GI("CHIP_GMNGAILT");
	CHIP_GMNGAIUP = GI("CHIP_GMNGAIUP");
	CHIP_GMNGAIDN = GI("CHIP_GMNGAIDN");

	GRAVITY = GF("GRAVITY");

	HEROINE_NO = GI("HEROINE_NO");
}

SharedParams::~SharedParams()
{

}
