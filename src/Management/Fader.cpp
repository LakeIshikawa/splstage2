#include "Fader.h"
#include "GameControl.h"

Fader::Fader()
{
	FADE_INCR = GF("FADE_INCR");
	fadeFactor = 0.0f;
}

Fader::~Fader(){}

/*
	�Ԃ��l�F
		0 - ������
		1 - ����
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
	�Ԃ��l�F
		0 - ������
		1 - ����
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
	̪��ނ̏�Ԃ���C�ɐݒ肷��
*/
void Fader::SetFadedOut( bool rFadedOut )
{
	fadeFactor = rFadedOut?1.0f:0.0f;
}

/*
	�t�F�[�h���x��ݒ肷��
*/
void Fader::SetSpeed(float rSp)
{
	FADE_INCR = rSp;
}

/*
	�т傤��
*/
void Fader::Draw()
{
	DX_DRAWALPHA("graphics\\fade.png", 0, 0, 0, 0, SP->SCRSZX, SP->SCRSZY, fadeFactor);
}