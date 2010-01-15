#include <exception>
using namespace std;

#include "Tenbin.h"
#include "..\\Management\\GameControl.h"

/************************************************************//**
*	標準コンストラクタ
****************************************************************/
Tenbin::Tenbin(int rXPx, int rYPx, float rZ)
{
	mX = rXPx;
	mY = rYPx;
	mZ = rZ;

	mAshibaL = NULL;
	mAshibaR = NULL;
}

/************************************************************//**
	標準デストラクタ
****************************************************************/
Tenbin::~Tenbin()
{
	if( mAshibaL ) delete mAshibaL;
	if( mAshibaR ) delete mAshibaR;
}

/************************************************************//**
*	左足場と右足場の総合性を保証する
*	- 一方の足場にものが乗ってる時、その足場が自然と下がり、
*	　他方の足場をこのメソッドが上昇させます
*	- どの足場にも何も乗っていない場合、足場をそろぞれの静止状態
*	  (配置状態)に戻す
****************************************************************/
void Tenbin::Move() {

	//***********************
	//***** 初期の処理 ******
	//***********************

	// 足場がまだ存在しなければ
	if( mAshibaL == NULL ){

		// 足場を作成して
		mAshibaL = new AshibaTenbin(mX, mY, mZ);
		mAshibaL->SetGraphic(0);

		mAshibaR = new AshibaTenbin(mX + mHrSpace + 
			GI("TENASHIBASX"), mY + mVrSpace, mZ);
		mAshibaR->SetGraphic(1);
	}

	//***********************
	//*** 1フレームの処理 ***
	//***********************

	// 足場の子を移動させる
	mAshibaL->Process();
	mAshibaR->Process();

	// if 左の足場に物が乗っていれば
	if( mAshibaL->GetRidersNum() > 0 ){

		// -- 左の足場を下げて、右の足場を上げて、終了
		mAshibaL->BringDown();
		mAshibaR->BringUp();
		return;
	}

	// if 右の足場に物が乗っていれば
	if( mAshibaR->GetRidersNum() > 0 ){

		// -- 右の足場を下げて、左の足場を上げて、終了
		mAshibaR->BringDown();
		mAshibaL->BringUp();
		return;
	}

	// その他の場合は、足場を静止状態に戻して終了
	mAshibaL->BringBack();
	mAshibaR->BringBack();
}

/************************************************************//**
*	足場と足場の横空白の設定
*	\param rHrSpacePx 横空白
****************************************************************/
void Tenbin::SetHrSpace(int rHrSpacePx) {
	mHrSpace = rHrSpacePx;
}

/************************************************************//**
*	足場と足場の縦ずれの設定
*	「-」の場合は、左の足場が下がっている
*	「+」の場合は、左の足場が上がっている
*	\param rVrSpacePx 縦のずれ
****************************************************************/
void Tenbin::SetVrSpace(int rVrSpacePx) {
	mVrSpace = rVrSpacePx;
}

/************************************************************//**
*	足場を削除して、次に天秤がリクエストされた時足場が再作成
*	されるようにします。
****************************************************************/
void Tenbin::Reset() {
	if( mAshibaL ) { delete mAshibaL; mAshibaL = NULL; }
	if( mAshibaR ) { delete mAshibaR; mAshibaR = NULL; }
}
