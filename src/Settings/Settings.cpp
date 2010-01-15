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
	設定ファイルをパース
*/
int Settings::ParseSettings(string rFName)
{
	ifstream set_file( rFName.c_str() );
	if( !set_file.is_open() ) return 1;  // ファイル未発見

	string line;	// 行ﾊﾞｯﾌｧｰ

	// 読み込み
	while( getline( set_file, line ) ){
		if( (line.length() > 1 && line.substr( 0, 2 ).compare("//") == 0) ||
			line.compare("") == 0) continue;

		char* tokp = strtok( (char*)line.c_str(), "{ :" );
		string key = tokp;

		tokp = strtok( NULL, ": }");
		string entry = tokp;
		Entry* ent;
		if( entry.substr(0, 1).compare("\"") == 0 ){ //文字列
			ent = new EntryString(entry.substr(1, entry.length()-2));
		}
		else{ //フロート
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
	フローﾄを取得
*/
float Settings::GetFloat(string key)
{
	stdext::hash_map<string, Entry*>::iterator fnd = lstSets.find(key);

	if( fnd == lstSets.end() ){
		char err[200] = "致命的なエラー：設定項目未発見：";
		strcat(err, key.c_str());

		MessageBox(NULL, err, "エラー", MB_OK);
		exit(1);
	}
	EntryFloat* flt = static_cast<EntryFloat*>(fnd->second);
	return flt->GetFloat();
}

/*
	文字列を取得
*/
string Settings::GetString(string key)
{
	stdext::hash_map<string, Entry*>::iterator fnd = lstSets.find(key);

	if( fnd == lstSets.end() ){
		char err[200] = "致命的なエラー：設定項目未発見：";
		strcat(err, key.c_str());

		MessageBox(NULL, err, "エラー", MB_OK);
		exit(1);
	}
	EntryString* str = static_cast<EntryString*>(fnd->second);

	return str->GetString();
}
