#pragma once

#include "Map.h"

/*
	���̑��x�ŃX�N���[������}�b�v
*/
class FixScrollMap : public Map
{
public:
	FixScrollMap();
	~FixScrollMap();

	void Scroll();
};