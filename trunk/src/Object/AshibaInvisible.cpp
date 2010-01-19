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

	LoadResources();
}

/**
	標準デストラクタ
*/
AshibaInvisible::~AshibaInvisible()
{
}

/************************************************************//**
*	描画
****************************************************************/
void AshibaInvisible::Draw()
{
	DX_SCROLL_CLWLIGHT_DRAW("graphics\\object\\mienai_asiba.png", 
		GAMECONTROL->GetDXController()->GetTextureOf("_AshibaInvTx"), 
		ASHIBASX, ASHIBASY, mX, mY, 0, 0, ASHIBASX, ASHIBASY);
}


/**
*	デバイスが失われたときにお応答
*/
void AshibaInvisible::OnLostDevice()
{

}

/**
*	デバイスが失われたときにお応答
*/
void AshibaInvisible::OnRestoredDevice()
{
	LoadResources();
}

/**
*	描画テクスチャを作成する
*/
void AshibaInvisible::LoadResources()
{
	GAMECONTROL->GetDXController()->CreateNewTexture("_AshibaInvTx", ASHIBASX, ASHIBASY,
		1, 0, D3DFMT_A8B8G8R8, D3DPOOL_MANAGED );
}