#include "LightResponseAble.h"
#include "..\\Management\\GameControl.h"
#include "..\\Light\\Light.h"

LightResponseAble::LightResponseAble(void)
{
	AddTask(this);
	mListenerOn = true;
}

LightResponseAble::~LightResponseAble(void)
{
}

/*
	この種類のオブジェクトは、Moveの前に
	スポットライトに当たってるかのチェックを
	行います
*/
void LightResponseAble::RunTask()
{
	if( !mListenerOn ) return;

	Light* ctrl_light = GAMECONTROL->GetUserLightControl()->GetControlLight();

	// スポットライトと当たり判定
	int scr = GAMECONTROL->GetStageManager()->GetCurScrollPointer();

	if( ctrl_light->AtHantei( GetAtHtPointX()-scr, GetAtHtPointY() ) )
	{
		// 色の判定
		COLOR ctrl_color = ctrl_light->GetColor();
		
		switch( ctrl_color )
		{
		case COLOR::AKA:
			ResponseAka();
			break;

		case COLOR::MIDORI:
			ResponseMidori();
			break;

		case COLOR::AO:
			ResponseAo();
			break;

		case COLOR::MUSHOKU:
			ResponseMushoku();
			break;

		default: break;
		}// switch
	}// if
	else // あたっていない！
	{
			NoLight();
	}
}

/*
	ライトに反応するかどうかを設定する
*/
void LightResponseAble::SetLightResponse(bool mOnOff)
{
	mListenerOn = mOnOff;
}