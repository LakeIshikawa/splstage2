#pragma once

#include <list>

#include "Map.h"

using namespace std;

#define ISASHIBAMOV(x) (x>=0 && x<=0x9F)

/*
	�����̔z�u�ް�
*/
class Zokusei : public Map
{
public:
	Zokusei(void);
	~Zokusei(void);

	int	Load(string rFname);
	void UnLoad();

};
