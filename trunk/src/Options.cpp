#include "Options.h"

Options* Options::mInstance = new Options();

/**
	標準コンストラクタ
	自動的に呼ばれます
*/
Options::Options()
{
}

/**
	標準デストラクタ
*/
Options::~Options()
{}

/************************************************************//**
*	オプションを追加する
*	\param rKey オプションのID(唯一)
*	\param rVal オプションの値
*	see Option
****************************************************************/
void Options::Add(string key, Option val)
{
	mMapOptions[key] = val;
}

/************************************************************//**
*	オプションを参照する
*	\param rKey オプションのID(唯一)
*	\return オプションの値
****************************************************************/
Options::Option Options::GetOption(string key)
{
	return mMapOptions[key];
}

/************************************************************//**
*	オプションが存在するかを尋ねる
*	\param rKey オプションのID(唯一)
*	\return 指定のオプションが存在するか
****************************************************************/
bool Options::IsOptionSet(string key)
{
	return (mMapOptions.find(key) != mMapOptions.end());
}