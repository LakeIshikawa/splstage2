#include ".\stage.h"
#include "..\\Management\\GameControl.h"
#include "..\\Light\\Light.h"
#include "Checkpoint\\CheckpointController.h"

Stage::Stage(string rDataFname, string rTekiFname, string rZokuseiFname, 
	string rScrollBckgImg, string rMapChipGr, SoundController::BGMS rBgm,  
	float rSeigenjikan, string rTitleGraphic, string rSelectImageGraphic,
	string rSelectTitleGraphic)
{
	mDataFname = rDataFname;
	mTekiFname = rTekiFname;
	mZokuseiFname = rZokuseiFname;
	mMapChipGr = rMapChipGr;
	mBgm = rBgm;
	mSelectImageGraphic = rSelectImageGraphic;
	mSelectTitleGraphic = rSelectTitleGraphic;
	
	mpScrollBackground = new ScrollBackground(rScrollBckgImg);
	mpMap = new Map();
	mpHaichi = new Haichi();
	mpZokusei = new Zokusei();
	mpCheckpointController = new CheckpointController();
	mpSeigenJikan = new SeigenJikan();
	mpSeigenJikan->SetMaxJikan(rSeigenjikan);
	mTitleGraphic = rTitleGraphic;

	load_completed = false;
}

Stage::Stage()
{
	mDataFname = "";
	mTekiFname = "";
	mZokuseiFname = "";
	mMapChipGr = "";
	mSelectImageGraphic = "";
	mSelectTitleGraphic = "";

	mpScrollBackground = NULL;
	mpMap = NULL;
	mpHaichi = NULL;
	mpCheckpointController = NULL;
	mpSeigenJikan = NULL;

	load_completed = false;
}

Stage::~Stage(void)
{
	delete mpMap;
	delete mpHaichi;
	delete mpZokusei;
	delete mpSeigenJikan;

}

// ﾏｯﾌﾟを取得
Map* Stage::GetMap()
{
	return mpMap;
}

// 配置ﾃﾞｰﾀを取得
Haichi* Stage::GetHaichi()
{
	return mpHaichi;
}

// 配置ﾃﾞｰﾀを取得
CheckpointController* Stage::GetCheckpointController()
{
	return mpCheckpointController;
}

// 制限時間を取得
SeigenJikan* Stage::GetSeigenJikan()
{
	return mpSeigenJikan;
}

// ﾏｯﾌﾟをﾛｰﾄﾞする
void Stage::Load()
{
	// これは・・・すまない・・・　俺は・・　もう・・・　ッグ！！！！
	/*GAMECONTROL->GetFader()->Draw();
	GAMECONTROL->GetDXController()->PrintDebugSting(650, 570, "now loading...");
	GAMECONTROL->GetDXController()->mpDevice->EndScene();
	GAMECONTROL->GetDXController()->mpDevice->Present(NULL, NULL, NULL, NULL);
	GAMECONTROL->GetDXController()->mpDevice->BeginScene();*/


	mpMap->Load( mDataFname, mMapChipGr );
	mpMap->SetScrollP(0);
	mpHaichi->Load( mTekiFname, mpCheckpointController );
	if( mZokuseiFname.compare("")!=0 ) 
		mpZokusei->Load( mZokuseiFname );

	inited = false;
	title_stage = 0;
	GAMECONTROL->GetJiki()->SetPos(GF("HERINITX"), GF("HERINITY"));
	GAMECONTROL->GetJiki()->ResetTempParams();
	GAMECONTROL->GetJiki()->SetSuperPause();
	GAMECONTROL->GetJiki()->SetMuki(1);

	GAMECONTROL->GetUserLightControl()->GetControlLight()->SetPos( SP->SCRSZX/2, SP->SCRSZY/2 );
	GAMECONTROL->GetJiki()->GetInterface()->Hide();

	GAMECONTROL->GetSoundController()->ResetBGMs();
	GAMECONTROL->GetSoundController()->SetBGM(mBgm);
				
	mpSeigenJikan->SeigenJikanReset();

}

// リソースを開放する
void Stage::UnLoad()
{
	mpMap->UnLoad();
	mpHaichi->UnLoad();
	mpCheckpointController->UnLoad();
}

/*
	1- ﾏｯﾌﾟの処理を行う
	2- 配置の出現確認を行う
*/
void Stage::Process()
{
	if( !inited ){
		Init();
	}

	mpScrollBackground->SetScrollP(mpMap->GetScrollP() / 3);
	mpScrollBackground->Draw();
	mpMap->Process();
	mpHaichi->Process();
	
	// チュートリアル以外は制限時間が経過する
	if( !GAMECONTROL->GetStageManager()->IsCurrentStageTutorial() )
		mpSeigenJikan->Process();

	//GAMECONTROL->GetLightManager()->Move();

	GAMECONTROL->GetMobManager()->Process();

	GAMECONTROL->GetLightManager()->Draw();

	GAMECONTROL->GetJiki()->GetInterface()->Draw();
}

/*
	開始演出
	終わったら1を返す
*/
void Stage::Init()
{
	// ﾌｪｰﾄﾞｲﾝ
	if( GAMECONTROL->GetFader()->FadeIn() ){
		
		// タイトル表示
		if( title_stage == 0 ){
			title_stage = 1;
			GAMECONTROL->GetTxtGraphicController()->
				ShowWithEnterFromRight( GI("STGTITLE_Y"), GI("STGTITLE_SX"), GI("STGTITLE_SY"), mTitleGraphic, GF("STGTITLE_SPX") );
		}
		// act start
		if( GAMECONTROL->GetTxtGraphicController()->IsFinished() ){
			if( title_stage == 1 ){
				title_stage = 2;
				GAMECONTROL->GetTxtGraphicController()->
				ShowWithEnterFromRight( GI("STGACTSTART_Y"), GI("STGACTSTART_SX"), GI("STGACTSTART_SY"), "graphics\\txtgraphic\\actstart.png", GF("STGTITLE_SPX") );
			}
		}

		// 幕
		if( GAMECONTROL->GetTxtGraphicController()->IsFinished() ){

			if( GAMECONTROL->GetMaku()->IsClosed() ) GAMECONTROL->GetMaku()->Open();
			// 幕をあげる
			if( GAMECONTROL->GetMaku()->IsOpen() ){
				inited = true;
				GAMECONTROL->GetUserLightControl()->GetControlLight()->TurnOn();
				GAMECONTROL->GetJiki()->SetSuperControl();
				GAMECONTROL->GetJiki()->GetInterface()->Show();
				GAMECONTROL->GetStageManager()->GetCurrentStage()->GetSeigenJikan()->SeigenJikanOn();	
			}
		}


		// ﾏｳｽｸﾘｯｸ演出スキップ
		if( GAMECONTROL->GetDXController()->IsMouseClicked() ){
			// 幕を強制的に持ち上げる
			GAMECONTROL->GetMaku()->SetOpened();
			// 文字を消す
			GAMECONTROL->GetTxtGraphicController()->Reset();
			title_stage = 2;
		}
	}
}
