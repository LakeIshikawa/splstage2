#include "Settings.h"
#include "EntryFloat.h"
#include "EntryString.h"
#include "Entry.h"
#include "windows.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Settings::Settings()
{}

Settings::~Settings()
{}

/*
	�ݒ�t�@�C�����p�[�X
*/
int Settings::ParseSettings(string rFName)
{
	ifstream set_file( rFName.c_str() );
	if( !set_file.is_open() ) return 1;  // �t�@�C��������

	string line;	// �s�ޯ̧�

	// �ǂݍ���
	while( getline( set_file, line ) ){
		if( (line.length() > 1 && line.substr( 0, 2 ).compare("//") == 0) ||
			line.compare("") == 0) continue;

		char* tokp = strtok( (char*)line.c_str(), "{ :" );
		string key = tokp;

		tokp = strtok( NULL, ": }");
		string entry = tokp;
		Entry* ent;
		if( entry.substr(0, 1).compare("\"") == 0 ){ //������
			ent = new EntryString(entry.substr(1, entry.length()-2));
		}
		else{ //�t���[�g
			int base = entry.substr(0, 2).compare("0x") == 0?16:10;
			if( base == 16 ){
				ent = new EntryFloat(strtol(entry.c_str(), NULL, base));
			}
			else{
				ent = new EntryFloat(atof(entry.c_str()));
			}
		}

		lstSets.insert(pair<string, Entry*>(key, ent));
		continue;
		
	}// while
	
	set_file.close();

	return 0;
}


/*
	�t���[Ă��擾
*/
float Settings::GetFloat(string key)
{
	stdext::hash_map<string, Entry*>::iterator fnd = lstSets.find(key);

	if( fnd == lstSets.end() ){
		char err[200] = "�v���I�ȃG���[�F�ݒ荀�ږ������F";
		strcat(err, key.c_str());

		MessageBox(NULL, err, "�G���[", MB_OK);
		exit(1);
	}
	EntryFloat* flt = static_cast<EntryFloat*>(fnd->second);
	return flt->GetFloat();
}

/*
	��������擾
*/
string Settings::GetString(string key)
{
	stdext::hash_map<string, Entry*>::iterator fnd = lstSets.find(key);

	if( fnd == lstSets.end() ){
		char err[200] = "�v���I�ȃG���[�F�ݒ荀�ږ������F";
		strcat(err, key.c_str());

		MessageBox(NULL, err, "�G���[", MB_OK);
		exit(1);
	}
	EntryString* str = static_cast<EntryString*>(fnd->second);

	return str->GetString();
}
