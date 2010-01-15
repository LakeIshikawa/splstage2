// splstg2.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "Main.h"
#include <d3dx9.h>
#include <d3d9.h>
#include <dinput.h>
#include "Management\\GameControl.h"
#include "Options.h"
#define MAX_LOADSTRING 100


// function prototypes
void initFont(LPDIRECT3DDEVICE9 pDevice);

void render_frame(void);    // renders a single frame
void cleanD3D(void);    // closes Direct3D and releases memory

void parseCommandLine( LPSTR cmdLine );
void analyzeArgs(int argc, char** argv);

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam);

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    // the handle for the window, filled by a function
    HWND hWnd;
    // this struct holds information for the window class
    WNDCLASSEX wc;

    // clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC)WindowProc;
    wc.hInstance = hInstance;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = "WindowClass1";

	ShowCursor(false);

    // register the window class
    RegisterClassEx(&wc);

	RECT wsize;
	SetRect(&wsize, 0, 0, 800, 600);

	AdjustWindowRectEx(&wsize, WS_OVERLAPPEDWINDOW, false, NULL);

    // create the window and use the result as the handle
    hWnd = CreateWindowEx(NULL,
                          "WindowClass1",    // name of the window class
                          "Splendid Stage v.1.0",   // title of the window
						  WS_POPUP,    // window style
                          100,    // x-position of the window
                          100,    // y-position of the window
						  wsize.right-wsize.left, wsize.bottom - wsize.top,
                          NULL,    // we have no parent window, NULL
                          NULL,    // we aren't using menus, NULL
                          hInstance,    // application handle
                          NULL);    // used with multiple windows, NULL

    // display the window on the screen
    ShowWindow(hWnd, nCmdShow);

	// parse command line
	parseCommandLine( lpCmdLine );

	// set up and initialize Direct3D
	GameControl::GetGameControl()->GameInit(hWnd);

    // enter the main loop:

    // this struct holds Windows event messages
    MSG msg;

	//LPD3DXSPRITE d3dspt;    // the pointer to our Direct3D Sprite interface

  // Enter the infinite message loop
while(TRUE)
{
	 // find out the starting time of each loop
          DWORD starting_point = GetTickCount();

    // Check to see if any messages are waiting in the queue
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        // If the message is WM_QUIT, exit the while loop
        if (msg.message == WM_QUIT)
            break;

        // Translate the message and dispatch it to WindowProc()
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Run game code here
	GameControl::GetGameControl()->GameLoop();


	 // wait until 1/40th of a second has passed
     while ((GetTickCount() - starting_point) < 25);
}


 // clean up DirectX and COM
    cleanD3D();

    // return this part of the WM_QUIT message to Windows
    return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch(message)
    {
        // this message is read when the window is closed
        case WM_DESTROY:
            {
                // close the application entirely
                PostQuitMessage(0);
                return 0;
            } break;
		//case	WM_KEYDOWN:

		//	if( wParam == VK_ESCAPE ){	//ESCAPEキーが押されたら

		//		int	ok = MessageBox( NULL, _T("終了しますか？"), _T("メッセージ"), MB_YESNO | MB_ICONQUESTION );

		//		if( ok == IDYES ){
		//			PostQuitMessage(0);		// アプリケーションを終了する
		//			return	0;
		//		}
		//		
		//	}
		//	break;

    }

    // Handle any messages the switch statement didn't
    return DefWindowProc (hWnd, message, wParam, lParam);
}

// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
    //d3ddev->Release();    // close and release the 3D device
    //d3d->Release();    // close and release Direct3D

    //return;
}

void parseCommandLine( LPSTR cmdLine ){
	 int    argc;
    char** argv;

    char*  arg;
    int    index;
    int    result;

    // count the arguments
    
    argc = 1;
    arg  = cmdLine;
    
    while (arg[0] != 0) {

        while (arg[0] != 0 && arg[0] == ' ') {
            arg++;
        }

        if (arg[0] != 0) {
        
            argc++;
        
            while (arg[0] != 0 && arg[0] != ' ') {
                arg++;
            }
        
        }
    
    }    
    
    // tokenize the arguments

    argv = (char**)malloc(argc * sizeof(char*));

    arg = cmdLine;
    index = 1;

    while (arg[0] != 0) {

        while (arg[0] != 0 && arg[0] == ' ') {
            arg++;
        }

        if (arg[0] != 0) {
        
            argv[index] = arg;
            index++;
        
            while (arg[0] != 0 && arg[0] != ' ') {
                arg++;
            }
        
            if (arg[0] != 0) {
                arg[0] = 0;    
                arg++;
            }
        
        }
    
    }    

    // put the program name into argv[0]

    char filename[_MAX_PATH];
    
    GetModuleFileName(NULL, filename, _MAX_PATH);
    argv[0] = filename;

    // call the user specified main function    
    
    analyzeArgs(argc, argv);
    
    free(argv);
}

/*
	引数に従ってシステムを設定します
*/
void analyzeArgs(int argc, char** argv){
	Options::Option op;

	for( int i=0; i<argc; i++){

		// ウインドー
		if( strcmp(argv[i], "-win") == 0 ){
			op.integ = 0;
			Options::GetOptions()->Add("win", op);
		}

		// 音なし
		else if( strcmp(argv[i], "-nosound") == 0 ){
			op.integ = 0;
			Options::GetOptions()->Add("nosound", op);
		}

		// チート
		else if( strcmp(argv[i], "-cheats") == 0 ){
			op.integ = 0;
			Options::GetOptions()->Add("cheats", op);
		}

		// 設定ﾌｧｲﾙの指定
		else if( strcmp(argv[i], "-settings") == 0 ){
			op.str= new char[strlen(argv[i+1])+1];
			strcpy(op.str, argv[i+1]);
			op.str[strlen(argv[i+1])] = 0;
			Options::GetOptions()->Add("settings", op);
		}
	}
}