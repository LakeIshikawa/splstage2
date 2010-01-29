#include <stdarg.h>

#include ".\GameControl.h"
#include "..\\Light\\Light.h"
#include "..\\Stage\\Map.h"

#include "Cheats\\ChtInflictDamage.h"
#include "Cheats\\ChtDie.h"
#include "Cheats\\ChtJumpToStage.h"
#include "Cheats\\ChtNoDamage.h"

#include "..\\Options.h"

#include "..\\ParticleEmitter\\PeHibashira.h"

#include <time.h>

#define SAFE_INSTANCE(p, cl, par) if(p) {delete p; p=NULL;} else {p = new cl(par);}

GameControl* GameControl::sGameControl = new GameControl();

ParticleEmitter* pe;

GameControl::GameControl()
{
	mpDXController = NULL;
	mpSoundController = NULL;
	mpUserLightControl = NULL;
	mpLightManager = NULL;
	mpMobManager = NULL;
	mpEventManager = NULL;
	mpStageManager = NULL;
	mpFader = NULL;
	mpTxtGraphicController = NULL;
	mpSettings = NULL;
	mpSharedParams = NULL;
	mpMaku = NULL;
	mpCheatsController = NULL;

	g_bDeviceLost = false;
}

GameControl::~GameControl(void)
{
}


/*
	ゲームマインループ
*/
void GameControl::GameLoop()
{

	// デバイスが喪失された場合は救助する
	RestoreLostDevice();

	GetLightManager()->Move();
	GAMECONTROL->GetLightManager()->BuildAlphaMask();

	// clear the window to a deep blue
	LPDIRECT3DDEVICE9 d3ddev = GetDXController()->GetDevice();
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddev->BeginScene();    // begins the 3D scene

	GetStageManager()->Process();
	GetEventManager()->Process();

	GetTxtGraphicController()->Draw();
	GetFader()->Draw();

	GetSoundController()->Process();

	GetMaku()->Process();

	GetCheatsController()->CheckAndTrigger();

	d3ddev->EndScene();    // ends the 3D scene
	HRESULT hr = d3ddev->Present(NULL, NULL, NULL, NULL);   // displays the created frame on the screen

	if( hr == D3DERR_DEVICELOST )
		g_bDeviceLost = true;


	// ユーザーライトの操作
	GetUserLightControl()->Move();

	// 終了確認
	if( GetDXController()->KeyPush(DIK_ESCAPE) ) ExitDialog();

    return;
}

void GameControl::RestoreLostDevice()
{
	 HRESULT hr;

    if( g_bDeviceLost == true )
    {
        // Yield some CPU time to other processes
        Sleep( 100 ); // 100 milliseconds

        //
        // Test the cooperative level to see if it's okay to render.
        // The application can determine what to do on encountering a lost 
        // device by querying the return value of the TestCooperativeLevel 
        // method.
        //

		if( FAILED( hr = GetDXController()->GetDevice()->TestCooperativeLevel() ) )
        {
            // The device has been lost but cannot be reset at this time. 
            // Therefore, rendering is not possible and we'll have to return 
            // and try again at a later time.
            if( hr == D3DERR_DEVICELOST )
                return;

            // The device has been lost but it can be reset at this time. 
            if( hr == D3DERR_DEVICENOTRESET )
            {
                //
                // If the device can be restored, the application prepares the 
                // device by destroying all video-memory resources and any 
                // swap chains. 
                //

                //invalidateDeviceObjects();

                //
                // Then, the application calls the Reset method.
                //
                // Reset is the only method that has an effect when a device 
                // is lost, and is the only method by which an application can 
                // change the device from a lost to an operational state. 
                // Reset will fail unless the application releases all 
                // resources that are allocated in D3DPOOL_DEFAULT, including 
                // those created by the IDirect3DDevice9::CreateRenderTarget 
                // and IDirect3DDevice9::CreateDepthStencilSurface methods.
                //

				GetDXController()->ResetAfterLost();

                //
                // Finally, a lost device must re-create resources (including  
                // video memory resources) after it has been reset.
                //

                //restoreDeviceObjects();
            }

            return;
        }

        g_bDeviceLost = false;
    }
}

/*
	一番最初に呼ばれる関数です。
	
	ゲームが起動する前に、すべての必要な初期化を
	行います。
	ルーチン化しています。
*/
void GameControl::GameInit(HWND rHwnd)
{
	
	srand(time(NULL));

	// 設定
	SAFE_INSTANCE( mpSettings, Settings );
	char* settingsFile = NULL;

	if( Options::GetOptions()->IsOptionSet("settings") ) 
		settingsFile = Options::GetOptions()->GetOption("settings").str;
	else settingsFile = "settings.txt";

	if (mpSettings->ParseSettings(settingsFile)){
		ThrowError( "致命的：設定ファイル未発見: %s", settingsFile );
		exit(1);
	}

	SAFE_INSTANCE( mpSharedParams, SharedParams );

	// 幕
	mpMaku = new MakuController();

	// 自機
	mpJiki = new Jiki(GI("HERINITX"), GI("HERINITY"));

	CreateControlsAndManagers( rHwnd );

	// 自機のリクエスト
	GetMobManager()->Request(GI("HEROINE_NO"), GI("HERINITX"), GI("HERINITY"), false);

	// スポットライトを作成
	GetLightManager()->AddLight(GetUserLightControl()->GetControlLight(), 0);
	GetLightManager()->GetLight(0)->TurnOff();	
//	GetLightManager()->AddLight(new Light(70), 1);

	// チートを作成する
	GetCheatsController()->Add( new ChtInflictDamage( DIK_I ) );
	GetCheatsController()->Add( new ChtDie( DIK_D ) );
	GetCheatsController()->Add( new ChtNoDamage( DIK_N ) );

	for( int i=0; i<GetStageManager()->GetNumStages(); i++){
		GetCheatsController()->Add( new ChtJumpToStage( DIK_1 + i ) );
	}

	// TEST
	//pe = new PeHibashira(400, 300, 1000, "graphics\\effect\\fire.jpg", 100, 100, 0);
	//pe->InitParticles( D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f) );
	
}

/* PRIVATE
	マネージャとコントローラオブジェクトを作成する
*/
void GameControl::CreateControlsAndManagers(HWND rHwnd)
{

	// D3D
	SAFE_INSTANCE( mpDXController, DXController, rHwnd );
	GetDXController()->InitD3D();
	GetDXController()->InitDIn();
	GetDXController()->InitFont();

	// SOUND
	SAFE_INSTANCE( mpSoundController, SoundController );
	mpSoundController->Init(rHwnd);

	// ライト
	SAFE_INSTANCE( mpUserLightControl, UserLightControl );
	SAFE_INSTANCE( mpLightManager, LightManager );

	// MOB
	SAFE_INSTANCE( mpMobManager, MobManager );

	// イベント
	SAFE_INSTANCE( mpEventManager, EventManager );

	// Fader
	SAFE_INSTANCE( mpFader, Fader );

	// ステージ
	SAFE_INSTANCE( mpStageManager, StageManager );
	mpStageManager->Init();

	// TXTGraphicContrller
	SAFE_INSTANCE( mpTxtGraphicController, TxtGraphicController );

	// チート
	SAFE_INSTANCE( mpCheatsController, CheatsController );
}

/**
	エラーメッセージの表示
*/
void GameControl::ThrowError(char* msg, ...)
{
	// 引数のリストを初期化
	va_list ap;
	va_start(ap, msg);

	// バッファーにメッセージを書き込む
	char buffer[256];
	vsprintf(buffer, msg, ap);

	MessageBox( NULL, buffer, "エラー", MB_OK );

	// リストを開放する
	va_end(ap);

}

/**
*	終了確認ダイアログ
*/
void GameControl::ExitDialog()
{
	if (MessageBox(GetDXController()->GetWindow(),"幕を閉じますか？","エピローグ",
		MB_YESNO|MB_ICONQUESTION|MB_TOPMOST|MB_DEFBUTTON2)==IDYES)
	{
		exit(0);
	}
}

/**
*	ﾃﾞｰﾀをﾚｼﾞｽﾄﾘｰに保存する
*/
void GameControl::SaveData(int stageIdx)
{
	// レジストリーに書き込む
	HKEY key;
	DWORD dwDisposition;

	if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\GekidanShimi\\SplendidStage"), 0, REG_NONE, REG_OPTION_NON_VOLATILE,
		KEY_WRITE|KEY_READ, NULL, &key, &dwDisposition) == ERROR_SUCCESS)
	{
		BYTE curval = 0;
		DWORD dwType = REG_DWORD;
		DWORD dwSize = sizeof(DWORD);
		RegQueryValueEx( key, TEXT("SaveIdx"), NULL, &dwType, &curval, &dwSize );

		// 現ｽﾃｰｼﾞが進んでる場合のみ保存する
		if( stageIdx > curval ){
			curval = (BYTE)stageIdx;
			RegSetValueEx( key, TEXT("SaveIdx"), NULL, REG_DWORD, (LPBYTE)(&curval), sizeof(DWORD) ); 
		}
	}

	RegCloseKey(key);
}