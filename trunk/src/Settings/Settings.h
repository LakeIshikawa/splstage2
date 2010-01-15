#pragma once

#include <hash_map>
#include <string>

#include "Entry.h"
using namespace std;


/*
	�ݒ���Ǘ�����N���X
*/
class Settings
{
public:
	Settings();
	~Settings();

	int ParseSettings(string rFName);

	// �C���^�[�t�F�[�X
	float GetFloat(string key);
	string GetString(string key);


private:
	stdext::hash_map<string, Entry*> lstSets;
	
};