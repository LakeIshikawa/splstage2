#pragma once

#include "Map.h"

/*
	一定の速度でスクロールするマップ
*/
class FixScrollMap : public Map
{
public:
	FixScrollMap();
	~FixScrollMap();

	void Scroll();
};