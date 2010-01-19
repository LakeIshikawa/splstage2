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
		if( GAMECONTROL->GetFader()->FadeIn() ) {
			stage = 1;
			GAMECONTROL->GetSoundController()->SetBGM(SoundController::ENDING);
		}
		
		// CONGRATULATIONS
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
	}

	if( !GAMECONTROL->GetSoundController()->IsBGMPlaying() && stage == 2){
		if( GAMECONTROL->GetFader()->FadeOut() ){
			STAGE_CLEAR;
		}
	}
	

}

void StaffRoll::Load()
{
	GAMECONTROL->GetSoundController()->ResetBGMs();
	Init();
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

	LPDIRECT3DTEXTURE9 mStaffRollTx = GAMECONTROL->GetDXController()->GetTextureOf("_StaffRollTx");

	// ｱﾙﾌｧﾏｽｸをﾚﾝﾀﾞﾘﾝｸﾞﾀｰｹﾞｯﾄとして指定する
	IDirect3DSurface9* oldsurf, *newsurf, *ed_str;
	mStaffRollTx->GetSurfaceLevel(0, &newsurf);


	LPDIRECT3DTEXTURE9 mask = GAMECONTROL->GetDXController()->GetTextureOf("graphics\\screen\\ed_str_mask.png");
	mEdStr->GetSurfaceLevel(0, &ed_str);

	// まるｺﾋﾟｰ
	dev->UpdateSurface( ed_str, NULL, newsurf, NULL );


	dev->EndScene();

	mRenderer->BeginScene(newsurf, NULL);
	
	spr->Begin(D3DXSPRITE_ALPHABLEND);

	// ｱﾙﾌｧﾏｽｸ
	dev->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, true);
	dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
	dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	dev->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);
	dev->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
	dev->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_MIN);

	D3DXMATRIX transl;
	D3DXMatrixTranslation(&transl, 0, scrp - SP->SCRSZY, 0);
	spr->SetTransform( &transl );

	spr->Draw(mask, NULL, NULL, &D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1,1,1,1));

	D3DXMatrixIdentity( &transl);
	spr->SetTransform( &transl );
	spr->End();
	mRenderer->EndScene(0);

	// 取得されたﾃｸｽﾁｬを開放する
	newsurf->Release();

	// ブレンドﾓｰﾄﾞを戻す
	dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	dev->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, false);

	dev->BeginScene();

}

/**
* アルファマスクを動的にかけて描画
*/
void StaffRoll::DrawStaffWithAlphaMask()
{
	BuildStaffTexture();

	DX_DRAW("_StaffRollTx", 0, SP->SCRSZY - scrp, 0, 0, GI("STAFF_SX"), scrp );
}

/**
* リソースを確保する
*/
void StaffRoll::LoadResources()
{
	// レンダリングターゲットのテクスチャ
	GAMECONTROL->GetDXController()->CreateNewTexture("_StaffRollTx",
		1024, 4096, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R3G3B2, D3DPOOL_DEFAULT);

	// スタッフロールのテクスチャ
	D3DXCreateTextureFromFileEx(GAMECONTROL->GetDXController()->GetDevice(),    // the device pointer
								"graphics\\screen\\ed_str.png",
								D3DX_DEFAULT, 
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								NULL,				// regular usage
								D3DFMT_A8R8G8B8,     // 32-bit pixels with alpha
								D3DPOOL_SYSTEMMEM,    // typical memory handling
								D3DX_DEFAULT,		// no filtering
								D3DX_DEFAULT,		// no mip filtering
								0,	
								NULL,
								NULL,
								&mEdStr
								);

	// サイズと形式の取得
	LPDIRECT3DSURFACE9 newsurf;
	mEdStr->GetSurfaceLevel(0, &newsurf);
	D3DSURFACE_DESC desc;
	newsurf->GetDesc( &desc );
	newsurf->Release();

	// サーフェースへレンダラーを作成
	D3DXCreateRenderToSurface( GAMECONTROL->GetDXController()->GetDevice(), 
		                       desc.Width, 
		                       desc.Height, 
		                       desc.Format, 
		                       TRUE, 
		                       D3DFMT_D16, 
		                       &mRenderer);
}


/**
* リソースを開放する
*/
void StaffRoll::ReleaseResources()
{
	// スタッフロールのテクスチャ
	mEdStr->Release();
	mEdStr = NULL;

	// サイズと形式の取得
	mRenderer->Release();
}


/**
* 
*/
void StaffRoll::OnLostDevice()
{
	ReleaseResources();
}