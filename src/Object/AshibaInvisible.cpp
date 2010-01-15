#include "AshibaInvisible.h"
#include "..\\Management\\GameControl.h"

/**
	標準コンストラクタ
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
	標準デストラクタ
*/
AshibaInvisible::~AshibaInvisible()
{
	mDrawingTexture->Release();
}

/************************************************************//**
*	描画
****************************************************************/
void AshibaInvisible::Draw()
{
	DX_SCROLL_CLWLIGHT_DRAW("graphics\\object\\mienai_asiba.png", mDrawingTexture, 
		ASHIBASX, ASHIBASY, mX, mY, 0, 0, ASHIBASX, ASHIBASY);
}