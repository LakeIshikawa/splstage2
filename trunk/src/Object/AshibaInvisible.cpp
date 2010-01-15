#include "AshibaInvisible.h"
#include "..\\Management\\GameControl.h"

/**
	�W���R���X�g���N�^
*/
AshibaInvisible::AshibaInvisible(int rXPx, int rYPx, float rZ, int sizex, int sizey) 
	: Ashiba(rXPx, rYPx, rZ, "", sizex, sizey)
{
	ASHIBASX = GI("ASHIBASX");
	ASHIBASY = GI("ASHIBASY");
	D3DXCreateTexture(GAMECONTROL->GetDXController()->GetDevice(), 
		ASHIBASX, ASHIBASY, 1, 0, D3DFMT_A8B8G8R8, D3DPOOL_MANAGED, &mDrawingTexture);

}

/**
	�W���f�X�g���N�^
*/
AshibaInvisible::~AshibaInvisible()
{
	mDrawingTexture->Release();
}

/************************************************************//**
*	�`��
****************************************************************/
void AshibaInvisible::Draw()
{
	DX_SCROLL_CLWLIGHT_DRAW("graphics\\object\\mienai_asiba.png", mDrawingTexture, 
		ASHIBASX, ASHIBASY, mX, mY, 0, 0, ASHIBASX, ASHIBASY);
}