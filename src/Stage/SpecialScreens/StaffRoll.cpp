#include "StaffRoll.h"
#include "..\\..\\Management\\GameControl.h"
#include "..\\..\\Event\\StageClearEvt.h"

StaffRoll::StaffRoll()
{

}

StaffRoll::~StaffRoll()
{}

/*
	画像の表示
*/
void StaffRoll::Process(){

	// 背景の描画
	DX_DRAW("graphics\\screen\\ed_back.png", 
		0, 0, 0, 0, SP->SCRSZX, SP->SCRSZY);
	
	switch( stage ){
	case 0:
		// ﾌｪｰﾄﾞｲﾝ
		if( GAMECONTROL->GetFader()->FadeIn() ) stage = 1;
		GAMECONTROL->GetTxtGraphicController()->ShowWithAlphaFade(TxtGraphicController::CENTER, 
			GI("CONGRATSX"), GI("CONGRATSY"), "graphics\\screen\\ed_congratulations.png", GF("CONGRATSTIME"), 0.05f );
		break;

	case 1:
		// ｽｸﾛｰﾙへ
		if( GAMECONTROL->GetTxtGraphicController()->IsFinished() ) stage = 2;
		break;

	case 2:
		// ｽｸﾛｰﾙ
		if( scrp<GI("STAFF_SY")+SP->SCRSZY/2 )
			scrp += GF("STAFF_SCRSP");
		// 描画
		DrawStaffWithAlphaMask();
		break;
	break;
	}

	if( !GAMECONTROL->GetSoundController()->IsBGMPlaying() ){
		if( GAMECONTROL->GetFader()->FadeOut() ){
			STAGE_CLEAR;
		}
	}
	

}

void StaffRoll::Load()
{
	GAMECONTROL->GetSoundController()->SetBGM(SoundController::ENDING);

	Init();

	// アルファマスク用
	D3DXCreateTexture(GAMECONTROL->GetDXController()->GetDevice(),
		1024, 4096, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, &mStaffRollTx);
	
}

void StaffRoll::Init(){
	stage = 0;
	scrp = 0;
}

void StaffRoll::UnLoad()
{}

/**
* ｽﾀｯﾌﾛｰﾙのﾃｸｽﾁに画像+ｱﾙﾌｧﾏｽｸを描画する
*/
void StaffRoll::BuildStaffTexture()
{
	// ﾃﾞﾊﾞｲｽとｽﾌﾟﾗｲﾄを楽に使えるために取得する
	LPDIRECT3DDEVICE9 dev = GAMECONTROL->GetDXController()->GetDevice();
	LPD3DXSPRITE spr = GAMECONTROL->GetDXController()->GetMainSprite();

	// ｱﾙﾌｧﾏｽｸをﾚﾝﾀﾞﾘﾝｸﾞﾀｰｹﾞｯﾄとして指定する
	IDirect3DSurface9* oldsurf, *newsurf;
	mStaffRollTx->GetSurfaceLevel(0, &newsurf);

	dev->GetRenderTarget(0, &oldsurf);
	dev->SetRenderTarget(0, newsurf);

	// ﾃｸｽﾁｬをｱﾙﾌｧ0で埋める
	dev->Clear(0,
               NULL,
               D3DCLEAR_TARGET,
			   D3DCOLOR_ARGB(1,0,0,0),
               1.0f,
               0);

	LPDIRECT3DTEXTURE9 img = GAMECONTROL->GetDXController()->GetTextureOf("graphics\\screen\\ed_str.png");
	LPDIRECT3DTEXTURE9 mask = GAMECONTROL->GetDXController()->GetTextureOf("graphics\\screen\\ed_str_mask.png");
	
	dev->BeginScene();
	spr->Begin(D3DXSPRITE_ALPHABLEND);

	// 画像を描画
	dev->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, true);
	dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	dev->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ZERO);
	dev->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
	dev->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD);
	spr->Draw(img, NULL, NULL, &D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1,1,1,1));

	spr->End();
	dev->EndScene();

		// ｼｰﾝ開始
	dev->BeginScene();
	spr->Begin(D3DXSPRITE_ALPHABLEND);

	// ｱﾙﾌｧﾏｽｸ
	dev->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, true);
	dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
	dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	dev->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);
	dev->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
	dev->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_MIN);
	spr->Draw(mask, NULL, NULL, &D3DXVECTOR3(0, scrp - SP->SCRSZY, 0), D3DXCOLOR(1,1,1,1));

	spr->End();
	dev->EndScene();

	// ﾚﾝﾀﾞﾘﾝｸﾞﾀｰｹﾞｯﾄを戻す
	dev->SetRenderTarget(0, oldsurf);

	// 取得されたﾃｸｽﾁｬを開放する
	oldsurf->Release();
	newsurf->Release();

	// ブレンドﾓｰﾄﾞを戻す
	dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	dev->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, false);
}

/**
* アルファマスクを動的にかけて描画
*/
void StaffRoll::DrawStaffWithAlphaMask()
{
	BuildStaffTexture();

	DX_DRAW(mStaffRollTx, 0, SP->SCRSZY - scrp, 0, 0, GI("STAFF_SX"), scrp );
}