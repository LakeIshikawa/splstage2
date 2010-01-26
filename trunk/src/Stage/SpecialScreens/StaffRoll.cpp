#include "StaffRoll.h"
#include "..\\..\\Management\\GameControl.h"
#include "..\\..\\Event\\StageClearEvt.h"

StaffRoll::StaffRoll()
{
	LoadResources();
}

StaffRoll::~StaffRoll()
{
	ReleaseResources();
}

/*
	�摜�̕\��
*/
void StaffRoll::Process(){

	// �w�i�̕`��
	DX_DRAW("graphics\\screen\\ed_back.png", 
		0, 0, 0, 0, SP->SCRSZX, SP->SCRSZY);
	
	switch( stage ){
	case 0:
		// ̪��޲�
		if( GAMECONTROL->GetFader()->FadeIn() ) {
			stage = 1;
			GAMECONTROL->GetSoundController()->SetBGM(SoundController::ENDING);
		}
		
		// CONGRATULATIONS
		GAMECONTROL->GetTxtGraphicController()->ShowWithAlphaFade(TxtGraphicController::CENTER, 
			GI("CONGRATSX"), GI("CONGRATSY"), "graphics\\screen\\ed_congratulations.png", GF("CONGRATSTIME"), 0.05f );

		break;

	case 1:
		// ��۰ق�
		if( GAMECONTROL->GetTxtGraphicController()->IsFinished() ) stage = 2;
		break;

	case 2:
		// ��۰�
		if( scrp<GI("STAFF_SY")+SP->SCRSZY/2 )
			scrp += GF("STAFF_SCRSP");
		// �`��
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
* ����۰ق�ø���ɉ摜+��̧Ͻ���`�悷��
*/
void StaffRoll::BuildStaffTexture()
{
	// ���޲��ƽ��ײĂ��y�Ɏg���邽�߂Ɏ擾����
	LPDIRECT3DDEVICE9 dev = GAMECONTROL->GetDXController()->GetDevice();
	LPD3DXSPRITE spr = GAMECONTROL->GetDXController()->GetMainSprite();

	LPDIRECT3DTEXTURE9 mStaffRollTx = GAMECONTROL->GetDXController()->GetTextureOf("_StaffRollTx");
	LPDIRECT3DTEXTURE9 mStaffRollTx2 = GAMECONTROL->GetDXController()->GetTextureOf("_StaffRollTx2");

	// ��̧Ͻ��������ݸ����ޯĂƂ��Ďw�肷��
	IDirect3DSurface9* oldsurf, *newsurf, *ed_str;

	// --------------------- �㔼�̉摜 --------------------------- //

	mStaffRollTx->GetSurfaceLevel(0, &newsurf);

	LPDIRECT3DTEXTURE9 mask = GAMECONTROL->GetDXController()->GetTextureOf("graphics\\screen\\ed_str_mask.png");
	mEdStr->GetSurfaceLevel(0, &ed_str);

	// �܂��߰
	dev->UpdateSurface( ed_str, NULL, newsurf, NULL );

	dev->EndScene();

	mRenderer->BeginScene(newsurf, NULL);
	
	spr->Begin(D3DXSPRITE_ALPHABLEND);

	// ��̧Ͻ�
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

	// �擾���ꂽø������J������
	newsurf->Release();
	ed_str->Release();


	// --------------------- �����̉摜 --------------------------- //
	mStaffRollTx2->GetSurfaceLevel(0, &newsurf);

	mEdStr2->GetSurfaceLevel(0, &ed_str);

	// �܂��߰
	dev->UpdateSurface( ed_str, NULL, newsurf, NULL );


	dev->EndScene();

	mRenderer->BeginScene(newsurf, NULL);
	
	spr->Begin(D3DXSPRITE_ALPHABLEND);

	// ��̧Ͻ�
	dev->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, true);
	dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
	dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	dev->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);
	dev->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
	dev->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_MIN);

	D3DXMatrixTranslation(&transl, 0, 2048 + scrp - SP->SCRSZY, 0);
	spr->SetTransform( &transl );

	spr->Draw(mask, NULL, NULL, &D3DXVECTOR3(0, 0, 0), D3DXCOLOR(1,1,1,1));

	D3DXMatrixIdentity( &transl);
	spr->SetTransform( &transl );
	spr->End();
	mRenderer->EndScene(0);

	// �擾���ꂽø������J������
	newsurf->Release();
	ed_str->Release();

	// ------------------------ �I�� -----------------------------//

	// �u�����hӰ�ނ�߂�
	dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	dev->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, false);

	dev->BeginScene();

}

/**
* �A���t�@�}�X�N�𓮓I�ɂ����ĕ`��
*/
void StaffRoll::DrawStaffWithAlphaMask()
{
	BuildStaffTexture();

	DX_DRAW("_StaffRollTx", 0, SP->SCRSZY - scrp, 0, 0, GI("STAFF_SX"), min(scrp,2048) );
	DX_DRAW("_StaffRollTx", 0, 2048 + SP->SCRSZY - scrp, 0, 0, GI("STAFF_SX"), min(scrp,2048) );
}

/**
* ���\�[�X���m�ۂ���
*/
void StaffRoll::LoadResources()
{
	// �����_�����O�^�[�Q�b�g�̃e�N�X�`��
	GAMECONTROL->GetDXController()->CreateNewTexture("_StaffRollTx",
		1024, 2048, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R3G3B2, D3DPOOL_DEFAULT);
	// �����_�����O�^�[�Q�b�g�̃e�N�X�`��
	GAMECONTROL->GetDXController()->CreateNewTexture("_StaffRollTx2",
		1024, 2048, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R3G3B2, D3DPOOL_DEFAULT);

	// �X�^�b�t���[���̃e�N�X�`��
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

	// �X�^�b�t���[���̃e�N�X�`��
	D3DXCreateTextureFromFileEx(GAMECONTROL->GetDXController()->GetDevice(),    // the device pointer
								"graphics\\screen\\ed_str2.png",
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
								&mEdStr2
								);

	// �T�C�Y�ƌ`���̎擾
	LPDIRECT3DSURFACE9 newsurf;
	mEdStr->GetSurfaceLevel(0, &newsurf);
	D3DSURFACE_DESC desc;
	newsurf->GetDesc( &desc );
	newsurf->Release();

	// �T�[�t�F�[�X�փ����_���[���쐬
	D3DXCreateRenderToSurface( GAMECONTROL->GetDXController()->GetDevice(), 
		                       desc.Width, 
		                       desc.Height, 
		                       desc.Format, 
		                       TRUE, 
		                       D3DFMT_D16, 
		                       &mRenderer);
}


/**
* ���\�[�X���J������
*/
void StaffRoll::ReleaseResources()
{
	// �X�^�b�t���[���̃e�N�X�`��
	mEdStr->Release();
	mEdStr = NULL;
	mEdStr2->Release();
	mEdStr = NULL;

	// �T�C�Y�ƌ`���̎擾
	mRenderer->Release();
}


/**
* ���[�X�g�f�o�C�X
*/
void StaffRoll::OnLostDevice()
{
	ReleaseResources();
}

/**
* ���[�X�g�f�o�C�X
*/
void StaffRoll::OnRestoredDevice()
{
	LoadResources();
}