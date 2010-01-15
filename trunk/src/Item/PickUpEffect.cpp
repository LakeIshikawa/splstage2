#include <string>
#include <vector>
#include <exception>
#include <stdarg.h>
using namespace std;

#include "PickUpEffect.h"
#include "..\\Management\\GameControl.h"

/************************************************************//**
*	�W���R���X�g���N�^
****************************************************************/
PickUpEffect::PickUpEffect( string rGraphic ) : mGraphic( rGraphic )
{
	ITEMFXFADESP = GF("ITEMFXFADESP");

	mSizeX = GI("ITEMFXSX");
	mSizeY = GI("ITEMFXSY");

	mSpY =  GF("ITEMFXSHOSP");
	mAccY = GF("ITEMFXACCY");

	mY = GAMECONTROL->GetJiki()->GetY();
	mX = GAMECONTROL->GetJiki()->GetX() + abs(mSizeX - GAMECONTROL->GetJiki()->GetFrameSizeX())/2;

	mAlpha = 1.0f;
}

/************************************************************//**
*	�W���f�X�g���N�^
****************************************************************/
PickUpEffect::~PickUpEffect()
{}

/************************************************************//**
*	�X�V�ƕ`��
****************************************************************/
void PickUpEffect::Move()
{
	// Y����ڰ����Č���
	mSpY += mAccY;
	mY += mSpY;

	// ��̧��̪��ޱ��
	mAlpha -= ITEMFXFADESP;

	// ����
	if( mAlpha <= 0.0f )
		GAMECONTROL->GetMobManager()->Remove(this);

	// �`��
	DX_SCROLL_ROT_DRAWALPHA( mGraphic, mX, mY, 0, 0, mSizeX, mSizeY, 0.0f, mAlpha );
}
