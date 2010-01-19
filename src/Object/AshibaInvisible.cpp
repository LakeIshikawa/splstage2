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

	LoadResources();
}

/**
	�W���f�X�g���N�^
*/
AshibaInvisible::~AshibaInvisible()
{
}

/************************************************************//**
*	�`��
****************************************************************/
void AshibaInvisible::Draw()
{
	DX_SCROLL_CLWLIGHT_DRAW("graphics\\object\\mienai_asiba.png", 
		GAMECONTROL->GetDXController()->GetTextureOf("_AshibaInvTx"), 
		ASHIBASX, ASHIBASY, mX, mY, 0, 0, ASHIBASX, ASHIBASY);
}


/**
*	�f�o�C�X������ꂽ�Ƃ��ɂ�����
*/
void AshibaInvisible::OnLostDevice()
{

}

/**
*	�f�o�C�X������ꂽ�Ƃ��ɂ�����
*/
void AshibaInvisible::OnRestoredDevice()
{
	LoadResources();
}

/**
*	�`��e�N�X�`�����쐬����
*/
void AshibaInvisible::LoadResources()
{
	GAMECONTROL->GetDXController()->CreateNewTexture("_AshibaInvTx", ASHIBASX, ASHIBASY,
		1, 0, D3DFMT_A8B8G8R8, D3DPOOL_MANAGED );
}