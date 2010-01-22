#include ".\DXController.h"
#include "GameControl.h"
#include "CustomDxDraw.h"
#include "..\\Options.h"
#include "..\\Light\\Light.h"
#include <d3dx9.h>
#include <process.h>


// 学校でコンパイルする時、次の行をアンコメントしてください
//#define GAKKOU

//#define FULL_SCREEN

DXController::DXController(HWND rHwnd)
{
	mpHwnd = rHwnd;
	mFullScreen = true;
	mPrevMouseClicked = false;

	hMutex = CreateMutex(NULL,FALSE,NULL);	//ミューテックス生成

}

DXController::~DXController(void)
{
}

// D3Dの初期化
void DXController::InitD3D()
{
	mpD3D = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

	memset(&d3dpp, 0, sizeof(d3dpp));
	
	if( !Options::GetOptions()->IsOptionSet("win") ){
		d3dpp.Windowed               = FALSE;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferWidth        = 800;
		d3dpp.BackBufferHeight       = 600;
		d3dpp.BackBufferFormat       = D3DFMT_X8R8G8B8;
		d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;
		d3dpp.MultiSampleType		 = D3DMULTISAMPLE_NONE;
		d3dpp.Flags					 = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	}

	else{
		d3dpp.Windowed               = TRUE;
		d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow			 = mpHwnd;
	}

    // create a device class using this information and the info from the d3dpp stuct
	mpD3D->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      mpHwnd,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
					  &mpDevice);

	HRESULT hr = mpDevice->SetDialogBoxMode(true);

	D3DXCreateSprite(mpDevice, &mpMainSprite);    // 画像描画用
	D3DXCreateSprite(mpDevice, &txtspt);		  // テキスト描画用

	return;
}

//Fontの初期化
void DXController::InitFont()
{
	D3DXCreateFont(mpDevice, 10, 10, FW_REGULAR, 0, true, SHIFTJIS_CHARSET, 
		OUT_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN, TEXT("Arial"), &ppFont);
}

/* 
	ファイル名で指定したグラフィックを描画します

	テクスチャのハッシュテーブルを調べ、ロード済みの
	グラフィックはそのまま描画し、まだロードされていない
	グラフィックはロードして、テーブルに追加して描画します。
*/
void DXController::Draw(std::string rFname, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry)
{
	DrawAlpha(rFname, rX, rY, rTlx, rTly, rBrx, rBry, 1.0f);
}

// 画面に描画する
void DXController::DrawAlpha(std::string rFname, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry, float alpha)
{
	LPDIRECT3DTEXTURE9 texture = GetTextureOf( rFname );

	if(texture)
		DrawAlpha(texture, rX, rY, rTlx, rTly, rBrx, rBry, alpha);
}

// ファイル名からテクスチャーを取得
LPDIRECT3DTEXTURE9	DXController::GetTextureOf( string rFname )
{
	WaitForSingleObject(hMutex,INFINITE); //mutex 間は他のスレッドから変数を変更できない
  
	LPDIRECT3DTEXTURE9 texture = NULL;

	// マップにあったらマップから
	std::map<std::string, LPDIRECT3DTEXTURE9>::iterator find;
	find = mmTextureMap.find( rFname );

	if( find != mmTextureMap.end() )
		texture = find->second;

	else {
		if(D3DXCreateTextureFromFileEx(mpDevice,    // the device pointer
								rFname.c_str(),
								D3DX_DEFAULT, 
								D3DX_DEFAULT,
								D3DX_DEFAULT,
								NULL,				// regular usage
								D3DFMT_UNKNOWN,     // 32-bit pixels with alpha
								D3DPOOL_MANAGED,    // typical memory handling
								D3DX_DEFAULT,		// no filtering
								D3DX_DEFAULT,		// no mip filtering
								0,	
								NULL,
								NULL,
								&texture)!=D3D_OK){
			CHAR msg[40];
			ZeroMemory(msg, 40);
			strcat( msg, "ファイル未発見:" );
			strcat( msg, rFname.c_str() );
			MessageBox( NULL, msg, "エラー", MB_OK );
			mmTextureMap[rFname] = NULL;
			return NULL;
		}

		// マップに追加
		mmTextureMap[rFname] = texture;
	}

	ReleaseMutex(hMutex);
	return texture;
}

// 新しくテクスチャを作成する
void DXController::CreateNewTexture(string rFname, UINT width, UINT height, UINT MipLevels, DWORD usage, D3DFORMAT format, D3DPOOL pool)
{
	WaitForSingleObject(hMutex,INFINITE); //mutex 間は他のスレッドから変数を変更できない
  
	LPDIRECT3DTEXTURE9 texture = NULL;
	D3DXCreateTexture(GetDevice(), width, height, MipLevels, usage, format, pool, &texture);
	mmTextureMap[rFname] = texture;

	ReleaseMutex(hMutex);
}

// 新しくテクスチャを作成する
void DXController::CreateNewTexture(UINT width, UINT height, UINT MipLevels, DWORD usage, D3DFORMAT format, D3DPOOL pool, LPDIRECT3DTEXTURE9* txt )
{
	WaitForSingleObject(hMutex,INFINITE); //mutex 間は他のスレッドから変数を変更できない
  
	D3DXCreateTexture(GetDevice(), width, height, MipLevels, usage, format, pool, txt);

	ReleaseMutex(hMutex);
}

// 画面に描画する
void DXController::Draw(LPDIRECT3DTEXTURE9 rTexture, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry)
{
	DrawAlpha(rTexture, rX, rY, rTlx, rTly, rBrx, rBry, 1.0f);
}

// 画面に描画する
void DXController::DrawAlpha(LPDIRECT3DTEXTURE9 rTexture, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry, float alpha)
{
	RECT border;
	border.top = rTly;
	border.left = rTlx;
	border.bottom = rBry;
	border.right = rBrx;

	D3DXVECTOR3 trans((float)rX, (float)rY, 0.0f);
	GetMainSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	GetMainSprite()->Draw(rTexture, &border, NULL, &trans, D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));

	GetMainSprite()->End();
}

// ｽｸﾘｰﾝRGB加法で画面に描画する
void DXController::ScrollScreenAlphaDraw(std::string rFname, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry, float rAlpha)
{
	int scpx = GAMECONTROL->GetStageManager()->GetCurScrollPointer();

	RECT border;
	border.top = rTly;
	border.left = rTlx;
	border.bottom = rBry;
	border.right = rBrx;

	D3DXVECTOR3 trans((float)rX-scpx, (float)rY, 0.0f);
	GetMainSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	GetDevice()->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	GetDevice()->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
	GetDevice()->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	GetMainSprite()->Draw(GetTextureOf(rFname), &border, NULL, &trans, D3DXCOLOR(1.0f, 1.0f, 1.0f, rAlpha));

	GetMainSprite()->End();
}

/*
	絶対座標に画像を描きます。　
	座標にｽｸﾛｰﾙﾎﾟｲﾝﾀｰが足しこまれる。

	画面外の場合、描画を行いません。
*/
void DXController::ScrollDraw(std::string rFname, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry)
{
	int scpx = GAMECONTROL->GetStageManager()->GetCurScrollPointer();

	if( rX + rBrx >= scpx && rX <= SP->SCRSZX + scpx )
		Draw(rFname, rX-scpx, rY, rTlx, rTly, rBrx, rBry);
}

/*
	スクロールを計算に入れて、ライトと接触してる領域だけが
	描画されます。
	\param rDrawBuffer 一時的なバッファー・メモリの管理は外でやってください
	@see ScrollDraw
*/

void DXController::ScrollClipWLightDraw(std::string rFname, LPDIRECT3DTEXTURE9 rDrawBuffer, 
										int rSx, int rSy, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry)
{
	int scpx = GAMECONTROL->GetStageManager()->GetCurScrollPointer();

	if( rX + rBrx >= scpx && rX <= SP->SCRSZX + scpx )
		ClipWLightDraw(rFname, rDrawBuffer, rSx, rSy, rX-scpx, rY, rTlx, rTly, rBrx, rBry);
}

/*
	ライトと接触してる領域だけが描画されます
*/
void DXController::ClipWLightDraw(std::string rFname, LPDIRECT3DTEXTURE9 rDrawBuffer, 
								  int rSx, int rSy, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry)
{
	LPDIRECT3DTEXTURE9 texture = GetTextureOf( rFname );

	if(texture){
		
		// バッファーにライトに当たるピクセルだけを書き込みます
		LPDWORD desdata, srcdata;// = (LPDWORD)p.pBits;
		D3DLOCKED_RECT des, src;
		rDrawBuffer->LockRect(0, &des, NULL, 0);
		texture->LockRect(0, &src, NULL, 0);

		Light* curLight = GAMECONTROL->GetUserLightControl()->GetControlLight();

		for( int y=0; y<rSy; y++){
			desdata = (LPDWORD)((LPBYTE)des.pBits + des.Pitch * y);
			srcdata = (LPDWORD)((LPBYTE)src.pBits + src.Pitch * y);
			for( int x=0; x<rSx; x++ ){
				if( curLight->AtHantei(rX + x, rY + y) )
					*(desdata+x) = *(srcdata+x);
				else
					*(desdata+x) = 0x00000000;
			}
		}

		rDrawBuffer->UnlockRect(0);
		texture->UnlockRect(0);
	}

	Draw(rDrawBuffer, rX, rY, rTlx, rTly, rBrx, rBry);
	//GetDevice()->SetTe
}

/*
	絶対座標に画像を回転したものを描画します。
	座標にｽｸﾛｰﾙﾎﾟｲﾝﾀｰが足しこまれる。

	画面外の場合、描画を行いません。

	@param rAngle ﾗｼﾞｱﾝ単位
*/
void DXController::ScrollRotDraw(std::string rFname, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry, float rAngle)
{
	ScrollRotDrawAlpha(rFname, rX, rY, rTlx, rTly, rBrx, rBry, rAngle, 1.0f);
}

/**
	絶対座標に画像を回転したものを描画します。
	座標にｽｸﾛｰﾙﾎﾟｲﾝﾀｰが足しこまれる。

	画面外の場合、描画を行いません。

	@param rAngle ﾗｼﾞｱﾝ単位
	@param ralpha ｱﾙﾌｧ値(0～1)
*/
void DXController::ScrollRotDrawAlpha(std::string rFname, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry, float rAngle, float rAlpha)
{
	int scpx = GAMECONTROL->GetStageManager()->GetCurScrollPointer();

	if( rX + rBrx >= scpx && rX <= SP->SCRSZX + scpx ){
		D3DXMATRIX cur;
		GetMainSprite()->GetTransform(&cur);

		D3DXVECTOR2 center(rX - scpx + (rBrx-rTlx)/2.0f, rY + (rBry-rTly)/2.0f);
		D3DXMATRIX rot;
	
		D3DXMatrixTransformation2D(&rot, NULL, 0.0f, NULL, &center, rAngle, NULL);
		GetMainSprite()->SetTransform(&rot);

		DrawAlpha(rFname, rX-scpx, rY, rTlx, rTly, rBrx, rBry, rAlpha);
		GetMainSprite()->SetTransform(&cur);
	}
}


/**
	絶対座標に画像を回転したものを描画します。
	座標にｽｸﾛｰﾙﾎﾟｲﾝﾀｰが足しこまれる。

	画面外の場合、描画を行いません。

	@param rAngle ﾗｼﾞｱﾝ単位
	@param ralpha ｱﾙﾌｧ値(0～1)
	@param rCtX 回転中心X
	@param rCtY 回転中心Y
*/
void DXController::CenterRotDrawAlpha(std::string rFname, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry, float rAngle, int rCtX, int rCtY, float rAlpha)
{
	
	D3DXMATRIX cur;
	GetMainSprite()->GetTransform(&cur);

	D3DXVECTOR2 center(rX + rCtX, rY + rCtY);
	D3DXMATRIX rot;

	D3DXMatrixTransformation2D(&rot, NULL, 0.0f, NULL, &center, rAngle, NULL);
	GetMainSprite()->SetTransform(&rot);

	DrawAlpha(rFname, rX, rY, rTlx, rTly, rBrx, rBry, rAlpha);
	GetMainSprite()->SetTransform(&cur);
}

/*
	ブレンド描画
*/
void DXController::DrawBlend(std::string rFname, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry, D3DXCOLOR col)
{
	RECT border;
	border.top = rTly;
	border.left = rTlx;
	border.bottom = rBry;
	border.right = rBrx;

	D3DXVECTOR3 trans((float)rX, (float)rY, 0.0f);
	GetMainSprite()->Begin(D3DXSPRITE_ALPHABLEND);
	GetMainSprite()->Draw(GetTextureOf(rFname), &border, NULL, &trans, col);

	GetMainSprite()->End();
}


/*
	円形を描画する　＊ﾃﾞﾊﾞｯｸﾞ用*
*/
void DXController::DrawCircle(int rX, int rY, int rHankei)
{
	const int NUMPOINTS = 24;
    const float PI = 3.14159;

	D3DTLVERTEX Circle[NUMPOINTS + 1];
	int i;
	float X;
	float Y;
	float Theta;
	float WedgeAngle;	//Size of angle between two points on the circle (single wedge)

	//Precompute WedgeAngle
	WedgeAngle = (float)((2*PI) / NUMPOINTS);

	//Set up vertices for a circle
	//Used <= in the for statement to ensure last point meets first point (closed circle)
	for(i=0; i<=NUMPOINTS; i++)
	{
		//Calculate theta for this vertex
		Theta = i * WedgeAngle;
		
		//Compute X and Y locations
		X = (float)(rX + rHankei * cos(Theta));
		Y = (float)(rY - rHankei * sin(Theta));

		Circle[i] = CreateD3DTLVERTEX(X, Y, 0.0f, 1.0f, RGB(100, 100, 100), 0.0f, 0.0f);
	}

	//Now draw the circle
    mpDevice->SetFVF(D3DFVF_TL);
	mpDevice->SetTexture(0, NULL);
	mpDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, NUMPOINTS, &Circle[0], sizeof(Circle[0]));

}

/*
	長方形を描画する　＊ﾃﾞﾊﾞｯｸﾞ用*
*/
void DXController::DrawRect(int rRight, int rTop, int rLeft, int rBottom)
{
	D3DTLVERTEX Rect[5];

	Rect[0] = CreateD3DTLVERTEX(rRight, rTop, 0.0f, 1.0f, RGB(100, 100, 100), 0.0f, 0.0f);
	Rect[1] = CreateD3DTLVERTEX(rLeft, rTop, 0.0f, 1.0f, RGB(100, 100, 100), 0.0f, 0.0f);
	Rect[2] = CreateD3DTLVERTEX(rLeft, rBottom, 0.0f, 1.0f, RGB(100, 100, 100), 0.0f, 0.0f);
	Rect[3] = CreateD3DTLVERTEX(rRight, rBottom, 0.0f, 1.0f, RGB(100, 100, 100), 0.0f, 0.0f);
	Rect[4] = Rect[0];

	mpDevice->SetFVF(D3DFVF_TL);
	mpDevice->SetTexture(0, NULL);
	mpDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, &Rect[0], sizeof(Rect[0]));
}


/*!
	デバッグようの情報を画面にプリントします。

	@param	rX		画面のX座標（ﾋﾟｸｾﾙ）
	@param	rY		画面のY座標（ﾋﾟｸｾﾙ）
	@param	rText	プリントされる文字列

*/
void DXController::PrintDebugSting(int rX, int rY, char* rText, ...){

	va_list args;
	va_start (args, rText);

	char buffer[256];
	sprintf(buffer,rText,args);

	RECT pos;
	SetRect(&pos, rX, rY, 0, 0);

	txtspt->Begin(D3DXSPRITE_ALPHABLEND);

	//長方形を自動的に計算します
	ppFont->DrawTextA(txtspt, buffer, -1, &pos, DT_CALCRECT || DT_NOCLIP, D3DCOLOR_XRGB(0,255,255));

	//描画
	ppFont->DrawTextA(txtspt, buffer, -1, &pos,DT_NOCLIP, D3DCOLOR_XRGB(0,0,0));

	txtspt->End();

}

// ゲッター
LPDIRECT3D9 DXController::GetDirect3D()
{
	return mpD3D;
}

// ゲッター
LPDIRECT3DDEVICE9 DXController::GetDevice()
{
	return mpDevice;
}

// ゲッター
LPD3DXSPRITE DXController::GetMainSprite()
{
	return mpMainSprite;
}


// DInputを初期化
void DXController::InitDIn()
{
	BOOL    bExclusive;
    BOOL    bForeground;
    BOOL    bImmediate;
    DWORD   dwCoopFlags;

	bExclusive = 0;
	bForeground = 0;
	bImmediate = 0;

	dwCoopFlags = DISCL_NONEXCLUSIVE | DISCL_BACKGROUND;

	// DI オブジェクト
	DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (VOID**)&mpDI, NULL );

	// マウス
	mpDI->CreateDevice( GUID_SysMouse, &mpMouseDevice, NULL );
	mpMouseDevice->SetDataFormat( &c_dfDIMouse2 );
	mpMouseDevice->SetCooperativeLevel( mpHwnd, dwCoopFlags );

	 DIPROPDWORD dipdw;
    dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    dipdw.dwData            = 16; // Arbitary buffer size
	mpMouseDevice->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );

	mpMouseDevice->Acquire();

	// キーボード
	mpDI->CreateDevice( GUID_SysKeyboard, &mpKeyboardDevice, NULL );
	mpKeyboardDevice->SetDataFormat( &c_dfDIKeyboard );
	mpKeyboardDevice->SetCooperativeLevel( mpHwnd, dwCoopFlags );

	mpKeyboardDevice->Acquire();
}


// マウスの状態を取得します
void DXController::UpdateMouseState()
{
	mPrevMouseClicked = mMouseState.rgbButtons[0];
	mpMouseDevice->GetDeviceState( sizeof(DIMOUSESTATE2), &mMouseState );
}

// ゲッター
LPDIRECTINPUTDEVICE8 DXController::GetMouseDevice()
{
	return mpMouseDevice;
}

// ゲッター
DIMOUSESTATE2 DXController::GetMouseState()
{
	return mMouseState;
}

// クリック
bool DXController::IsMouseClicked()
{
	return mMouseState.rgbButtons[0] && !mPrevMouseClicked;
}

// マウスの状態を取得します
void DXController::UpdateKeyboardState()
{
	memcpy(mKeyboardStatePrev, mKeyboardState, sizeof(mKeyboardStatePrev));
	mpKeyboardDevice->GetDeviceState( sizeof(mKeyboardState), &mKeyboardState );
}


// キーが押されている場合、trueを返します。　押されていない場合、false。
bool DXController::KeyHold(int key)
{
	return KEYDOWN(mKeyboardState, key);
}

// キーが押される瞬間だけtrue
bool DXController::KeyPush(int key)
{
	return ( KEYDOWN(mKeyboardState, key) && !KEYDOWN(mKeyboardStatePrev, key) );
}

// キーが押される瞬間だけtrue
bool DXController::KeyPull(int key)
{
	return ( !KEYDOWN(mKeyboardState, key) && KEYDOWN(mKeyboardStatePrev, key) );
}

// フールスクリーンを設定する
void DXController::SetFullScreen( bool mOnOff ){
	mFullScreen = mOnOff;
}

/**
 *  デバイスが喪失された後、復活するための処理
 */
void DXController::ResetAfterLost()
{
	// 全リソース開放
	mpMainSprite->Release();
	txtspt->Release();

	// テクスチャ
	for each(pair<string, LPDIRECT3DTEXTURE9> tx in mmTextureMap) {
		tx.second->Release();
	}
	mmTextureMap.clear();

	GAMECONTROL->GetStageManager()->OnLostDevice();

	// リセット
	GetDevice()->Reset(&d3dpp);

	// 全リソース復活
	mpDevice->SetDialogBoxMode(true);
	D3DXCreateSprite(mpDevice, &mpMainSprite);    // 画像描画用
	D3DXCreateSprite(mpDevice, &txtspt);		  // テキスト描画用

	GAMECONTROL->GetLightManager()->LoadResources();
	GAMECONTROL->GetStageManager()->OnRestoredDevice();
}