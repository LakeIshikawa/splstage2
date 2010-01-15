#pragma once

#include <hash_map>
#include <string>

#include "Entry.h"
using namespace std;


/*
	設定を管理するクラス
*/
class Settings
{
public:
	Settings();
	~Settings();

	int ParseSettings(string rFName);

	// インターフェース
	float GetFloat(string key);
	string GetString(string key);


private:
	stdext::hash_map<string, Entry*> lstSets;
	
};