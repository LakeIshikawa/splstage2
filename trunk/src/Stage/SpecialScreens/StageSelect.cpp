#include "StageSelect.h"
#include "..\\..\\Management\\GameControl.h"
#include "..\\..\\Light\\Light.h"
#include "..\\..\\Event\\StageClearEvt.h"
#include "..\\..\\Stage\\FixScrollMap.h"

#define LIGHT_AT 30

StageSelect::StageSelect(string rDataFname, string rScrollBckgImg, string rMapChipGr, SoundController::BGMS rBgm)
{
	mDataFname = rDataFname;
	mMapChipGr = rMapChipGr;
	mBgm = rBgm;
	
	mpScrollBackground = new ScrollBackground(rScrollBckgImg);
	mpMap = new FixScrollMap();
}

void StageSelect::Init()
{
	stage = 0;
	scroll = 0;
	scrollNLRdir = 0;
	alpha = 1.0f;
	curScroll = 0;
	LoadSaveData();
	selectedIdx = saveStageTdx;
}

StageSelect::~StageSelect(void)
{
}

void StageSelect::Process()
{
	switch( stage ){

	// フェードイン
	case 0:
		if( GAMECONTROL->GetFader()->FadeIn() ){
			//幕をあげる
			GAMECONTROL->GetMaku()->Open();
			GAMECONTROL->GetSoundController()->SetBGM(mBgm);
			stage = 1;
		}
		break;

	// 幕をあげる
	case 1:
		if( GAMECONTROL->GetMaku()->IsOpen() ) stage = 2;
		break;

	// 操作を有効にする
	case 2:
		GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOn();
		stage = 3;
		break;

	// ﾕｰｻﾞｰの操作を受け付けて応答する
	case 3:
		ProcessUserControl();
		break;

	// 幕ダウン、ﾌｪｰﾄﾞアウト
	case 4:
		if( GAMECONTROL->GetMaku()->IsClosed() ){
			if( GAMECONTROL->GetFader()->FadeOut() ){
				StageManager* sm = GAMECONTROL->GetStageManager();
				sm->GoToStage( selectedIdx + sm->GetFirstStageIdx() );
			}
		}
	}	


	//描画
	mpScrollBackground->Draw();

	GetMap()->Process();

	DrawInterface();
	
	GAMECONTROL->GetLightManager()->Draw();

	GAMECONTROL->GetMaku()->Draw();

}

void StageSelect::Load()
{
	// これは・・・すまない・・・　俺は・・　もう・・・　ッグ！！！！
	GAMECONTROL->GetFader()->Draw();
	GAMECONTROL->GetDXController()->PrintDebugSting(650, 570, "now loading...");
	GAMECONTROL->GetDXController()->mpDevice->EndScene();
	GAMECONTROL->GetDXController()->mpDevice->Present(NULL, NULL, NULL, NULL);
	GAMECONTROL->GetDXController()->mpDevice->BeginScene();

	mpMap->Load( mDataFname, mMapChipGr );
	mpHaichi->Load( mTekiFname, mpCheckpointController );
	GAMECONTROL->GetJiki()->SetPos(-500, 0);
	GAMECONTROL->GetJiki()->ResetLife();
	GAMECONTROL->GetJiki()->ResetTension();
	GAMECONTROL->GetJiki()->ResetEmpacy();
	GAMECONTROL->GetJiki()->ResetChain();
	GAMECONTROL->GetJiki()->ResetTempParams();
	GAMECONTROL->GetJiki()->SetSuperPause();
	GAMECONTROL->GetJiki()->SetMuki(1);

	GAMECONTROL->GetUserLightControl()->GetControlLight()->SetPos( SP->SCRSZX/2, SP->SCRSZY/2 );
	GAMECONTROL->GetSoundController()->PauseBGM();

	mpScrollBackground->SetScrollP(mpMap->GetScrollP());

	Init();
}

void StageSelect::UnLoad()
{
	mpMap->UnLoad();
}

void StageSelect::SetSelectedIdx(int rIdx)
{
	selectedIdx = rIdx;
}

/**
* ﾕｰｻﾞｰが矢印にクリックしたら、ｽﾃｰｼﾞの画像が別の画像にｽﾗｲﾄﾞする。
* ﾕｰｻﾞｰがｽﾃｰｼﾞ画像をクリックしたら、ｹﾞｰﾑ開始
*/
void StageSelect::ProcessUserControl()
{
	if( GAMECONTROL->GetDXController()->IsMouseClicked() )
	{
		// ﾗｲﾄの位置
		int lx = GAMECONTROL->GetUserLightControl()->GetControlLight()->GetX();
		int ly = GAMECONTROL->GetUserLightControl()->GetControlLight()->GetY();
		
		// 矢印
		// -- 左
		int lyx = GI("STGSELECT_LARX") + GI("STGSELECT_ARSX")/2;
		int lyy = GI("STGSELECT_ARY") + GI("STGSELECT_ARSY")/2;
		if( sqrt( pow((float)(lyx-lx), 2) + pow((float)(lyy-ly), 2)) <= LIGHT_AT ){
			GoToLeft();
			return;
		}

		// -- 右
		int ryx = GI("STGSELECT_RARX") + GI("STGSELECT_ARSX")/2;
		if( sqrt( pow((float)(ryx-lx), 2) + pow((float)(lyy-ly), 2) ) <= LIGHT_AT ){
			GoToRight();
			return;
		}

		// ｽﾃｰｼﾞ開始
		int top = GI("STGSELECT_IMGY");
		int left = SP->SCRSZX/2 - GI("STGSELECT_IMGSX")/2;
		int bottom = top + GI("STGSELECT_IMGSY");
		int right = left + GI("STGSELECT_IMGSX");

		// ｽﾃｰｼﾞ開始が選択されたか
		if( lx >= left && lx <= right && ly>=top && ly <= bottom && selectedIdx <= saveStageTdx && scroll == 0){
			GAMECONTROL->GetMaku()->Close();
			GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOff();
			stage = 4;
		}
	}
}

/**
* ｽﾃｰｼﾞ選択ｲﾝﾀｰﾌｪｰｽの描画
*/
void StageSelect::DrawInterface()
{
	
	// ﾀｲﾄﾙ
	StageManager* sm = GAMECONTROL->GetStageManager();
	
	// ﾌｪｰﾄﾞ
	alpha += 0.05f;
	if( alpha > 1.0f ) alpha = 1.0f;
	// 現ﾀｲﾄﾙ
	DX_DRAWALPHA(sm->GetStageSelectTitleGraphic(sm->GetFirstStageIdx() + selectedIdx), 
		SP->SCRSZX/2-GI("STGSELECT_TITSX")/2, GI("STGSELECT_TITY"), 0, 0, 
		GI("STGSELECT_TITSX"), GI("STGSELECT_TITSY"), alpha );
	// 前ﾀｲﾄﾙ
	if( scrollNLRdir != 0 ){
		int scridx = selectedIdx + (scrollNLRdir==1?1:-1);	
		string graphic = sm->GetStageSelectTitleGraphic(sm->GetFirstStageIdx() + scridx);
		DX_DRAWALPHA(graphic,SP->SCRSZX/2-GI("STGSELECT_TITSX")/2, GI("STGSELECT_TITY"), 0, 0, 
			GI("STGSELECT_TITSX"), GI("STGSELECT_TITSY"), 1.0f-alpha );
	}

	// 矢印
	DX_DRAW("graphics\\stageselect\\left.png", GI("STGSELECT_LARX"), GI("STGSELECT_ARY"),
		0, 0, GI("STGSELECT_ARSX"), GI("STGSELECT_ARSY") );
	DX_DRAW("graphics\\stageselect\\right.png", GI("STGSELECT_RARX"), GI("STGSELECT_ARY"),
		0, 0, GI("STGSELECT_ARSX"), GI("STGSELECT_ARSY") );


	// ｲﾒｰｼﾞ画像
	// ｽﾗｲﾄﾞｲﾝ
	if( scrollNLRdir == 2 ) scroll -= GI("STGSELECT_SLDSP");
	else if( scrollNLRdir == 1 ) scroll += GI("STGSELECT_SLDSP");
	// 停止条件
	if( scrollNLRdir == 2 && scroll < 0 ) { scroll = 0; scrollNLRdir = 0; }
	if( scrollNLRdir == 1 && scroll > 0 ) { scroll = 0; scrollNLRdir = 0; }

	// 現在ｲﾒｰｼﾞ
	DX_DRAW(saveStageTdx >= selectedIdx ? sm->GetStageSelectImageGraphic(sm->GetFirstStageIdx() + selectedIdx) : 
		"graphics\\stageselect\\stgNA.png",	SP->SCRSZX/2-GI("STGSELECT_IMGSX")/2 + scroll, GI("STGSELECT_IMGY"), 0, 0, 
		GI("STGSELECT_IMGSX"), GI("STGSELECT_IMGSY") );
	
	// 前回ｲﾒｰｼﾞ(ｽｸﾛｰﾙ用)
	if( scrollNLRdir != 0 ){
		bool leftright = scrollNLRdir == 1;
		int scridx = selectedIdx + (leftright?1:-1);
		string graphic = saveStageTdx >= scridx? sm->GetStageSelectImageGraphic(sm->GetFirstStageIdx() + scridx) : 
			"graphics\\stageselect\\stgNA.png";
		int scroll2 = leftright ? GI("STGSELECT_SLDDIST") +scroll : scroll - GI("STGSELECT_SLDDIST");

		DX_DRAW(graphic, SP->SCRSZX/2-GI("STGSELECT_IMGSX")/2 + scroll2, GI("STGSELECT_IMGY"), 0, 0, 
			GI("STGSELECT_IMGSX"), GI("STGSELECT_IMGSY") );
	}

	// 全体図
	DX_DRAW("graphics\\stageselect\\stageallgray.png", SP->SCRSZX/2-GI("STGSELECT_ALLSX")/2, 
		GI("STGSELECT_ALLY"), 0, 0, GI("STGSELECT_ALLSX"), GI("STGSELECT_ALLSY") );
	DX_DRAW("graphics\\stageselect\\stageall.png", SP->SCRSZX/2-GI("STGSELECT_ALLSX")/2, 
		GI("STGSELECT_ALLY"), 0, 0, GI("STGSELECT_ALL1SX") * (saveStageTdx+1), GI("STGSELECT_ALLSY") );
	DX_DRAW_BLEND("graphics\\stageselect\\stageall.png", SP->SCRSZX/2-GI("STGSELECT_ALLSX")/2 + GI("STGSELECT_ALL1SX") * (saveStageTdx+1), 
		GI("STGSELECT_ALLY"), GI("STGSELECT_ALL1SX") * (saveStageTdx+1), 0, GI("STGSELECT_ALLSX"), GI("STGSELECT_ALLSY"),
		D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));

	// ｶｰｿﾙ
	// ｽｸﾛｰﾙ
	float sp = GI("STGSELECT_ALL1SX") / ((float)GI("STGSELECT_SLDDIST")/GI("STGSELECT_SLDSP"));
	curScroll += scrollNLRdir == 1 ? -0.78 : scrollNLRdir == 2 ? 0.78 : 0;
	if( scrollNLRdir == 0 ) curScroll = 0;
	DX_DRAW("graphics\\stageselect\\cursor.png", SP->SCRSZX/2-GI("STGSELECT_ALLSX")/2 + selectedIdx*GI("STGSELECT_ALL1SX") + curScroll,
		GI("STGSELECT_ALLY"), 0, 0, GI("STGSELECT_CURSORSX"), GI("STGSELECT_CURSORSY") );

	// 枠
	DX_DRAW("graphics\\stageselect\\Image_frame.png", SP->SCRSZX/2-GI("STGSELECT_FRAMESX")/2,
		GI("STGSELECT_IMGY")-10, 0, 0, GI("STGSELECT_FRAMESX"), GI("STGSELECT_FRAMESY"));

}

/**
* 保存ﾃﾞｰﾀをﾛｰﾄﾞする方法-
*/
void StageSelect::LoadSaveData()
{
	// 初期値
	saveStageTdx = 6;

	// レジストリーから読み込む
	HKEY key;
	DWORD dwDisposition;

	if (RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\GekidanShimi\\SplendidStage"), 0, REG_NONE, REG_OPTION_NON_VOLATILE,
		KEY_WRITE|KEY_READ, NULL, &key, &dwDisposition) == ERROR_SUCCESS)
	{
		DWORD dwType = REG_DWORD;
		DWORD dwSize = sizeof( DWORD );
		BYTE res = 0;
		RegQueryValueEx( key, TEXT("SaveIdx"), NULL, &dwType, &res, &dwSize ); 
		saveStageTdx = (int) res;
	}

	RegCloseKey( key );

	// 6が初期値地のため、ﾊﾞｯｸサポートやバグを防ぐために、6以下は直す
	if( saveStageTdx < 6 ) {
		saveStageTdx = 6;
	}
	if( saveStageTdx > GAMECONTROL->GetStageManager()->GetLastStageIdx() - GAMECONTROL->GetStageManager()->GetFirstStageIdx() ){
		saveStageTdx = GAMECONTROL->GetStageManager()->GetLastStageIdx() - GAMECONTROL->GetStageManager()->GetFirstStageIdx();
	}
}

/**
* 左のｽﾃｰｼﾞに選択を移す
*/
void StageSelect::GoToLeft()
{
	if( selectedIdx > 0 /*&& scrollNLRdir == 0*/){
		selectedIdx--;
		// ｽｸﾛｰﾙ
		scroll = -GI("STGSELECT_SLDDIST");
		scrollNLRdir = 1;
		// アルファﾌｪｰﾄﾞ
		alpha = 0.0f;
		// ｶｰｿﾙ
		curScroll = GI("STGSELECT_ALL1SX");
	}
}


/**
* 右のｽﾃｰｼﾞに選択を移す
*/
void StageSelect::GoToRight()
{
	if( selectedIdx < GAMECONTROL->GetStageManager()->GetLastStageIdx() - 
		GAMECONTROL->GetStageManager()->GetFirstStageIdx() )
	{
		selectedIdx++;
		scroll = GI("STGSELECT_SLDDIST");
		scrollNLRdir = 2;
		// アルファﾌｪｰﾄﾞ
		alpha = 0.0f;
		// ｶｰｿﾙ
		curScroll = -GI("STGSELECT_ALL1SX");
	}
}
