#pragma once

#include "Entry.h"

using namespace std;

/*
	������
*/
class EntryString : public Entry
{
public:
	EntryString(string rString){mString = rString;}
	~EntryString(){}

	string GetString(){ return mString; }

private:
	string mString;
};