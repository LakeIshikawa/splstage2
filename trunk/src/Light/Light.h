#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "..\\Management\\UserLightControl.h"

// 便利な定義
#define COLOR UserLightControl::COLOR

/*
	丸型のスポットライト。
	ライトマネージャーが提供するインターフェースを
	通じて描画されます。
*/
class Light
{
	friend class LightManager;

public:
	Light(int rHankei);
	~Light();

	bool AtHantei(int rX, int rY);

	void Move();
	void Draw();

	void	SetSpX( float rSp );
	void	SetSpY( float rSp );
	void	SetPos( float rPosX, float rPosY );
	void	SetColor( COLOR rColor );

	bool	IsOn();
	void	TurnOn();
	void	TurnOff();

	float	GetSpX();
	float	GetSpY();
	float	GetX();
	float	GetY();
	int		GetHankei();
	COLOR	GetColor();


private:
	DWORD	GetWordColor();

	int mHankei;
	float mXCenter;
	float mYCenter;

	float mSpX;
	float mSpY;

	COLOR mColor;

	bool  mActive;

	// 設定定数
	int LIGHT_BASE;

};
