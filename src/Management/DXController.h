#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <map>
#include <string>

using namespace std;

// マクロ群
#define KEYDOWN(name, key) (name[key] & 0x80) 


/*
	ダイレクトXオブジェクトを管理するAPIです。
	ダイレクトXを包むインターフェースも提供します。
*/
class DXController
{
public:
	DXController(HWND rHwnd);
	~DXController(void);

	// --操作
	void InitD3D();
	void InitDIn();
	void InitFont();
	void FreeD3D();

	// --D3D関連
	void Draw(LPDIRECT3DTEXTURE9 rTexture, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry);
	void DrawBlend(std::string rFname, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry, D3DXCOLOR col);
	void DXController::DrawAlpha(LPDIRECT3DTEXTURE9 rTexture, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry, float alpha);
	void DXController::DrawAlpha(std::string rFname, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry, float alpha);
	void Draw(std::string rFname, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry);
	void ClipWLightDraw(std::string rFname, LPDIRECT3DTEXTURE9 rDrawBuffer, int rSx, int rSy, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry);
	void ScrollDraw(std::string rFname, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry);
	void ScrollRotDraw(std::string rFname, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry, float rAngle);
	void ScrollRotDrawAlpha(std::string rFname, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry, float rAngle, float rAlpha);
	void CenterRotDrawAlpha(std::string rFname, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry, float rAngle, int rCtX, int rCtY, float rAlpha);
	void ScrollClipWLightDraw(std::string rFname, LPDIRECT3DTEXTURE9 rDrawBuffer, int rSx, int rSy, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry);
	void ScrollScreenAlphaDraw(std::string rFname, int rX, int rY, int rTlx, int rTly, int rBrx, int rBry, float rAlpha);

	void DrawCircle(int rX, int rY, int rHankei);
	void DrawRect(int rRight, int rTop, int rLeft, int rBottom);

	void PrintDebugSting(int rX, int rY, char* rText, ...);

	LPDIRECT3DTEXTURE9 GetTextureOf( string rFName );
	void CreateNewTexture( string rFname, UINT width, UINT height, UINT MipLevels, DWORD usage, D3DFORMAT format, D3DPOOL pool );


	// --DInput関連
	// デバイス状態更新
	void UpdateMouseState();
	void UpdateKeyboardState();

	// デバイスを調べる
	bool KeyHold(int key);
	bool KeyPush(int key);
	bool KeyPull(int key);

	bool IsMouseClicked();

	// --設定
	void SetFullScreen( bool mOnOff );


	// デバイスが喪失された後はリセットするため
	void ResetAfterLost();


	// ---アクセス
	LPDIRECT3D9				GetDirect3D();
	LPDIRECT3DDEVICE9		GetDevice();
	LPD3DXSPRITE			GetMainSprite();

	LPDIRECTINPUT8			GetDirectInput();

	// マウス
	LPDIRECTINPUTDEVICE8	GetMouseDevice();
	DIMOUSESTATE2			GetMouseState();

	// キーボード
	LPDIRECTINPUTDEVICE8	GetKeyboardDevice();

	HWND					GetWindow() { return mpHwnd; }

	// フォント
	LPD3DXFONT ppFont;					//!< デバッグフォント
	LPD3DXSPRITE txtspt;				//!< テキスト描画用のスプライト 
	LPDIRECT3DDEVICE9		mpDevice;


private:
	HWND					mpHwnd;
	D3DPRESENT_PARAMETERS	d3dpp;

	// D3D
	LPDIRECT3D9				mpD3D;
	LPD3DXSPRITE			mpMainSprite;

	std::map<std::string, LPDIRECT3DTEXTURE9>
							mmTextureMap;

	bool					mFullScreen;

	// Dinput
	LPDIRECTINPUT8			mpDI;        

	LPDIRECTINPUTDEVICE8	mpMouseDevice;
	DIMOUSESTATE2			mMouseState;
	bool					mPrevMouseClicked;

	LPDIRECTINPUTDEVICE8	mpKeyboardDevice;
	char					mKeyboardState[256];
	char					mKeyboardStatePrev[256];

};
