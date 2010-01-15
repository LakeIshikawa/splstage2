#pragma once

#include "Entry.h"

using namespace std;

/*
	•‚—V“_€–Ú
*/
class EntryFloat : public Entry
{
public:
	EntryFloat(float rFloat){mFloat = rFloat;}
	~EntryFloat(){}

	float GetFloat(){ return mFloat; }

private:
	float mFloat;
};