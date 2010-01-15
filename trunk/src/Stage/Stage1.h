#pragma once

#include "Map.h"
#include "Haichi.h"
#include "Stage.h"

class Stage1 : public Stage
{
public:
	Stage1(string rDataFname, string rTekiFname);
	~Stage1(void);

	// ˆ—
	void	Process();

};
