#include "Fader.h"
#include "GameControl.h"

Fader::Fader()
{
	FADE_INCR = GF("FADE_INCR");
	fadeFactor = 0.0f;
}

Fader::~Fader(){}

/*
	返し値：
		0 - 処理中
		1 - 完成
*/
int Fader::FadeOut()
{
	fadeFactor += FADE_INCR;
	if( fadeFactor > 1.0f ) fadeFactor = 1.0f;

	if( fadeFactor == 1.0f )
		return 1;
	else return 0;

}

/*
	返し値：
		0 - 処理中
		1 - 完成
*/
int Fader::FadeIn()
{
	fadeFactor -= FADE_INCR;
	if( fadeFactor < 0.0f ) fadeFactor = 0.0f;

	if( fadeFactor == 0.0f )
		return 1;
	else return 0;
}

/*
	ﾌｪｰﾄﾞの状態を一気に設定する
*/
void Fader::SetFadedOut( bool rFadedOut )
{
	fadeFactor = rFadedOut?1.0f:0.0f;
}

/*
	フェード速度を設定する
*/
void Fader::SetSpeed(float rSp)
{
	FADE_INCR = rSp;
}

/*
	びょうが
*/
void Fader::Draw()
{
	DX_DRAWALPHA("graphics\\fade.png", 0, 0, 0, 0, SP->SCRSZX, SP->SCRSZY, fadeFactor);
}