#include <string>
#include <vector>
#include <exception>
#include <stdarg.h>
#include <fstream>
#include <iostream>
using namespace std;

#include "Animation.h"
#include "..\\Management\\GameControl.h"

/************************************************************//**
*	\return このｵﾌﾞｼﾞｪｸﾄのｺﾋﾟｰ
****************************************************************/
Animation* Animation::Clone()
{
	Animation* newAnim = new Animation();
	newAnim->mAnimData = mAnimData;
	newAnim->mAnimIntervals = mAnimIntervals;
	newAnim->mElapsedTime = mElapsedTime;
	newAnim->mFrameIdx = mFrameIdx;
	newAnim->mMode = mMode;
	newAnim->mGraphicSource = mGraphicSource;
	newAnim->mLoopCount = mLoopCount;
	newAnim->mLoopStartIdx = mLoopStartIdx;

	return newAnim;
}

/************************************************************//**
*	標準コンストラクタ
****************************************************************/
Animation::Animation()
{
	mMode			= ANMD_LOOP;
	
	mLoopStartIdx   = 0;

	mGraphicSource	= "";
	
	Rewind();
}

/************************************************************//**
*	標準デストラクタ
****************************************************************/
Animation::~Animation()
{}

/************************************************************//**
*	\param rElapsedTime 前回からの経過時間
****************************************************************/
void Animation::ElapseTime(float rElapsedTime) {

	// 時間の経過
	mElapsedTime += rElapsedTime;

	// ﾌﾚｰﾑ番号の更新
	if( mElapsedTime >= mAnimIntervals[mFrameIdx] ){
		mFrameIdx++;
	}

	// 終了条件
	if( mFrameIdx >= mAnimData.size() ){
		switch( mMode ) {
			case ANMD_LOOP:	
				{
					mFrameIdx = mLoopStartIdx; 
					mElapsedTime = 0.0f; 
					mLoopCount++;
					break; 
				}

			case ANMD_STOPATEND: 
				{
					mFrameIdx--; 
					mLoopCount = 1;
					break;
				}
		}
	}
}

/************************************************************//**
*	\param ... ｱﾆﾒｰｼｮﾝﾃﾞｰﾀ(int型)。必ず-1で終わらなければならない
****************************************************************/
void Animation::SetAnimData(int rFirst, ...) {

	// 引数のリストを初期化
	va_list ap;
	va_start(ap, rFirst);

	// 引数が-1以外の場合は、続く
	int val = rFirst;
	while(val != -1){
		mAnimData.push_back(val);
		val = va_arg(ap, int);
	}

	// リストを開放する
	va_end(ap);
}

/************************************************************//**
*	\param ... ｱﾆﾒｰｼｮﾝﾃﾞｰﾀ(float型)。必ず-1で終わらなければならない
****************************************************************/
void Animation::SetAnimIntervals(float rFirst, ...) {

	// 引数のリストを初期化
	va_list ap;
	va_start(ap, rFirst);

	// 引数が-1以外の場合は、続く
	float val = rFirst;
	while(val != -1){
		mAnimIntervals.push_back(val);
		val = va_arg(ap, double);
	}

	// リストを開放する
	va_end(ap);
}

/************************************************************//**
*	\param rMode ｱﾆﾒｰｼｮﾝﾓｰﾄﾞ
****************************************************************/
void Animation::SetAnimMode(ANIM_MODE rMode) {
	mMode = rMode;
}

/************************************************************//**
*	\param rMode ｱﾆﾒｰｼｮﾝﾓｰﾄﾞ
****************************************************************/
void Animation::SetGraphicSource(string rGraphicSource) {
	mGraphicSource = rGraphicSource;
}

/************************************************************//**
*	\param rMode ｱﾆﾒｰｼｮﾝﾓｰﾄﾞ
****************************************************************/
void Animation::SetLoopStartIdx(int rLoopStartIdx) {
	mLoopStartIdx = rLoopStartIdx;
}

/************************************************************//**
*	巻き戻し
****************************************************************/
void Animation::Rewind() {
	mFrameIdx = 0;
	mElapsedTime = 0.0f;
	mLoopCount = 0;
}

/************************************************************//**
*	\return 現在再生中のﾌﾚｰﾑ番号(ﾃﾞｰﾀとして入れた数字)
****************************************************************/
int Animation::GetCurFrameIdx() {
	return mAnimData[mFrameIdx];
}

/************************************************************//**
*	\return このｱﾆﾒｰｼｮﾝはﾙｰﾌﾟが終了した回数
*	ﾓｰﾄﾞがANMD_STOPATENDの場合は、終了の時に1になる
****************************************************************/
int Animation::GetLoopCount() {
	return mLoopCount;
}

/************************************************************//**
*	\return ｸﾞﾗﾌｨｯｸ源のﾌｧｲﾙ名
****************************************************************/
string Animation::GetGraphicSource() {
	return mGraphicSource;
}

/************************************************************//**
*	\param rPath ｱﾆﾒｰｼｮﾝﾌｧｲﾙのﾊﾟｽ
*	\return ｱﾆﾒｰｼｮﾝﾌｧｲﾙから読み込まれた設定の元で作られた
*			新ｱﾆﾒｰｼｮﾝｵﾌﾞｼﾞｪｸﾄ
****************************************************************/
Animation* Animation::ParseFromFile(string rPath)
{
	Animation* animation = new Animation();

	// 設定ﾌｧｲﾙを開く
	ifstream set_file( rPath.c_str() );
	if( !set_file.is_open() ) {
		// ファイル未発見
		GAMECONTROL->ThrowError("ｱﾆﾒｰｼｮﾝﾌｧｲﾙ未発見: %s", rPath);
	}

	string line;	// 行ﾊﾞｯﾌｧｰ
	// 読み込み
	while( getline( set_file, line ) ){
		// ｺﾒﾝﾄ
		if( (line.length() > 1 && line.substr( 0, 2 ).compare("//") == 0) ||
			line.compare("") == 0) continue;

		char* tokp = strtok( (char*)line.c_str(), " " );
		string prop = tokp;

		// 設定の認識

		// ｸﾞﾗﾌｨｯｸﾌｧｲﾙ名
		if( prop.compare( "GRAPHIC_SRC" ) == 0 ){
			tokp = strtok( NULL, "\"" );
			animation->SetGraphicSource( tokp );
		}

		// ﾃﾞｰﾀ
		if( prop.compare( "DATA" ) == 0 ){
			while( tokp = strtok( NULL, " ," ) )
				animation->mAnimData.push_back( atoi( tokp ) );
		}

		// ｲﾝﾀｰﾊﾞﾙ
		if( prop.compare( "INTERVAL" ) == 0 ){
			while( tokp = strtok( NULL, " ," ) )
				animation->mAnimIntervals.push_back( atof( tokp ) );
		}

		// ｱﾆﾒｰｼｮﾝﾓｰﾄﾞ
		if( prop.compare( "MODE" ) == 0 ){
			tokp = strtok( NULL, " " );
			if( strcmp( tokp, "LOOP") == 0 ) {
				animation->SetAnimMode( ANMD_LOOP );
			}
			else if ( strcmp( tokp, "STOP" ) == 0 ) {
				animation->SetAnimMode( ANMD_STOPATEND );
			}
			else
				GAMECONTROL->ThrowError("ﾌｧｲﾙ:%s  \n認識できないｱﾆﾒｰｼｮﾝﾓｰﾄﾞ: %s", rPath, tokp);
		}
	}

	return animation;
}