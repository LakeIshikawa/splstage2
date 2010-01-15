#include "Light.h"
#include <math.h>
#include <d3d9.h>

#include "..\\Management\\GameControl.h"

/*
	ライトを　作成
*/
Light::Light(int rHankei)
{
	LIGHT_BASE = GI("LIGHT_BASE");

	mHankei = rHankei;
	mSpX = 0;
	mSpY = 0;
	mXCenter = SP->SCRSZX/2;
	mYCenter = SP->SCRSZY/2;;
	mColor = COLOR::MUSHOKU;
	mActive = false;
}

/*
	ライトとの当たり判定

	@param rX	当たり判定候補のX
	@param rY	当たり判定候補のY
*/
bool Light::AtHantei(int rX, int rY)
{
	int sa_x = rX - (int)mXCenter;
	int sa_y = rY - (int)mYCenter;

	int sa = (int)sqrt((double)sa_x*sa_x + sa_y*sa_y);

	return sa < mHankei;
}

/*
	速度を座標に足しこむ（フレームごとにマネージャーから呼ばれる）

	ライトが画面外に出ないことを保証します。
*/
void Light::Move()
{
	// 更新したら画面外に出るか？
	int new_x = mXCenter+mSpX;
	int new_y = mYCenter+mSpY;

	if(new_x-mHankei>=0 && new_x+mHankei<=SP->SCRSZX)
		mXCenter+=mSpX;

	if(new_y-mHankei>=0 && new_y+mHankei<=SP->SCRSZY)
		mYCenter+=mSpY;
}

/*
	ﾗｲﾄの部分の描画を行います
*/
void Light::Draw()
{
	switch( mColor ){
		case COLOR::AKA:
			DX_DRAWALPHA("graphics\\light_red.png", mXCenter-mHankei, mYCenter-mHankei,
				0, 0, mHankei*2, mHankei*2, LIGHT_BASE/255.0f);
			break;

		case COLOR::AO:
			DX_DRAWALPHA("graphics\\light_blue.png", mXCenter-mHankei, mYCenter-mHankei,
				0, 0, mHankei*2, mHankei*2, LIGHT_BASE/255.0f);
			break;

		case COLOR::MIDORI:
			DX_DRAWALPHA("graphics\\light_yellow.png", mXCenter-mHankei, mYCenter-mHankei,
				0, 0, mHankei*2, mHankei*2, LIGHT_BASE/255.0f);
			break;

		case COLOR::MUSHOKU:
		default:
		break;	
	}
}

//　セッター
void Light::SetSpX( float rSp )
{
	mSpX = rSp;
}

//　セッター
void Light::SetSpY( float rSp )
{
	mSpY = rSp;
}

// セッター
void Light::SetColor( COLOR rColor )
{
	mColor = rColor;
}

//　ゲッター
float Light::GetSpX()
{
	return mSpX;
}

//　ゲッター
float Light::GetSpY()
{
	return mSpY;
}

//　ゲッター
float Light::GetX()
{
	return mXCenter;
}

//　ゲッター
float Light::GetY()
{
	return mYCenter;
}

//　ゲッター
int	Light::GetHankei()
{
	return mHankei;
}

//　ゲッター
COLOR Light::GetColor()
{
	return mColor;
}

// ゲッター
DWORD Light::GetWordColor()
{
	switch( mColor ){

		case COLOR::MUSHOKU:
			return 0x00000000;
			break;

		case COLOR::AKA:
			return 0x00ff0000 + LIGHT_BASE;
			break;

		case COLOR::AO:
			return 0x000000ff + LIGHT_BASE;
			break;

		case COLOR::MIDORI:
			return 0x00ffff00 + LIGHT_BASE;
			break;
	}
	return 0x00000000;
}

/*
	位置を変える。
	危険：　処理が重い。
*/
void Light::SetPos(float rPosX, float rPosY){
	mXCenter = rPosX;
	mYCenter = rPosY;
}

// ライトのOn/Off性
bool Light::IsOn()
{
	return mActive;
}

void Light::TurnOn()
{
	mActive = true;
}

void Light::TurnOff()
{
	mActive = false;
}