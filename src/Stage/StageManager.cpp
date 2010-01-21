#include ".\stagemanager.h"
#include "..\\Management\\GameControl.h"
#include "..\\Stage\\Map.h"
#include "..\\Light\\Light.h"
#include "SpecialScreens\\GameOverScr.h"
#include "SpecialScreens\\TitleScr.h"
#include "SpecialScreens\\StageSelect.h"
#include "SpecialScreens\\StaffRoll.h"
#include "SpecialScreens\\TeamLogo.h"
#include "SpecialScreens\\CurtainRollScr.h"

#include <process.h>

#define GAME_OVER_IDX 20

#define STG_LOOP_POINT 20 // このステージ-1が終わったらタイトル画面に戻る
#define STG_SELECT_IDX 2
#define TUT1_IDX 3
#define ST11_IDX 9

/*
	ここでﾏｯﾌﾟﾁｯﾌﾟのテクスチャを読み込みます
*/
StageManager::StageManager(void)
{
	mCurrentIndex = 0;

	// ｽﾃｰｼﾞを作成
	maStages[0] = new TeamLogo();

	maStages[1] = new TitleScr(
		GS("TITLE_MAP"),
		GS("TITLE_HAICHI"), 
		string("graphics\\back.png"),
		string("graphics\\m_cp00.png"),
		SoundController::TITLE
		);

	maStages[2] = new StageSelect(
		GS("TITLE_MAP"),
		string("graphics\\back.png"),
		string("graphics\\m_cp00.png"),
		SoundController::TITLE
		);


	maStages[3] = new Stage( 
		GS("TUT1_MAP"),
		GS("TUT1_HAICHI"), 
		GS("TUT1_ZOKUSEI"),
		string("graphics\\back.png"),
		string("data\\tutorial\\1\\tyuto1.png"),
		SoundController::STG1,
		GF("STAGE1_TIME"),
		string("graphics\\txtgraphic\\ttg1.png"),
		string("graphics\\stageselect\\stg11.png"),
		string("graphics\\stageselect\\title11.png")
		);

	maStages[4] = new Stage( 
		GS("TUT2_MAP"),
		GS("TUT2_HAICHI"), 
		GS("TUT2_ZOKUSEI"),
		string("graphics\\back.png"),
		string("data\\tutorial\\2\\tyuto2.png"),
		SoundController::STG1,
		GF("STAGE1_TIME"),
		string("graphics\\txtgraphic\\ttg2.png"),
		string("graphics\\stageselect\\stg11.png"),
		string("graphics\\stageselect\\title11.png")
		);

	maStages[5] = new Stage( 
		GS("TUT3_MAP"),
		GS("TUT3_HAICHI"), 
		GS("TUT3_ZOKUSEI"),
		string("graphics\\back.png"),
		string("data\\tutorial\\3\\tyuto3.png"),
		SoundController::STG1,
		GF("STAGE1_TIME"),
		string("graphics\\txtgraphic\\ttg3.png"),
		string("graphics\\stageselect\\stg11.png"),
		string("graphics\\stageselect\\title11.png")
		);

	maStages[6] = new Stage( 
		GS("TUT4_MAP"),
		GS("TUT4_HAICHI"), 
		GS("TUT4_ZOKUSEI"),
		string("graphics\\back.png"),
		string("data\\tutorial\\4\\tyuto4.png"),
		SoundController::STG1,
		GF("STAGE1_TIME"),
		string("graphics\\txtgraphic\\ttg4.png"),
		string("graphics\\stageselect\\stg11.png"),
		string("graphics\\stageselect\\title11.png")
		);

	maStages[7] = new Stage( 
		GS("TUT5_MAP"),
		GS("TUT5_HAICHI"), 
		GS("TUT5_ZOKUSEI"),
		string("graphics\\back.png"),
		string("data\\tutorial\\5\\tyuto5.png"),
		SoundController::STG1,
		GF("STAGE1_TIME"),
		string("graphics\\txtgraphic\\ttg5.png"),
		string("graphics\\stageselect\\stg11.png"),
		string("graphics\\stageselect\\title11.png")
		);

	maStages[8] = new Stage( 
		GS("TUT6_MAP"),
		GS("TUT6_HAICHI"), 
		GS("TUT6_ZOKUSEI"),
		string("graphics\\back.png"),
		string("data\\tutorial\\6\\tyuto6.png"),
		SoundController::STG1,
		GF("STAGE1_TIME"),
		string("graphics\\txtgraphic\\ttg6.png"),
		string("graphics\\stageselect\\stg11.png"),
		string("graphics\\stageselect\\title11.png")
		);

	maStages[9] = new Stage( 
		GS("STAGE1_MAP"),
		GS("STAGE1_HAICHI"), 
		GS("STAGE1_ZOKUSEI"),
		string("graphics\\back.png"),
		string("graphics\\m_cp00.png"),
		SoundController::STG1,
		GF("STAGE1_TIME"),
		string("graphics\\txtgraphic\\stg11.png"),
		string("graphics\\stageselect\\stg11.png"),
		string("graphics\\stageselect\\title11.png")
		);

	maStages[10] = new Stage( 
		GS("STAGE12_MAP"),
		GS("STAGE12_HAICHI"), 
		GS("STAGE12_ZOKUSEI"),
		string("graphics\\back.png"),
		string("graphics\\m_cp00.png"),
		SoundController::STG1,
		GF("STAGE2_TIME"),
		string("graphics\\txtgraphic\\stg12.png"),
		string("graphics\\stageselect\\stg12.png"),
		string("graphics\\stageselect\\title12.png")
		);

	maStages[11] = new Stage( 
		GS("STAGE1_BOSS_MAP"),
		GS("STAGE1_BOSS_HAICHI"), 
		"",
		string("graphics\\back.png"),
		string("graphics\\m_cp01.png"),
		SoundController::BOSS1,
		GF("STAGE1_BOSS_TIME"),
		string("graphics\\txtgraphic\\stg13.png"),
		string("graphics\\stageselect\\stg13.png"),
		string("graphics\\stageselect\\title13.png")
		);

	maStages[12] = new Stage( 
		GS("STAGE2_MAP"),
		GS("STAGE2_HAICHI"), 
		GS("STAGE2_ZOKUSEI"),
		string("graphics\\stage2back.png"),
		string("graphics\\m_cp02.png"),
		SoundController::STG2,
		GF("STAGE2_TIME"),
		string("graphics\\txtgraphic\\stg21.png"),
		string("graphics\\stageselect\\stg21.png"),
		string("graphics\\stageselect\\title21.png")
		);

	maStages[13] = new Stage( 
		GS("STAGE22_MAP"),
		GS("STAGE22_HAICHI"), 
		GS("STAGE22_ZOKUSEI"),
		string("graphics\\stage2back.png"),
		string("graphics\\m_cp02.png"),
		SoundController::STG2,
		GF("STAGE2_TIME"),
		string("graphics\\txtgraphic\\stg22.png"),
		string("graphics\\stageselect\\stg22.png"),
		string("graphics\\stageselect\\title22.png")
		);

	maStages[14] = new Stage(
		GS("STAGE2_BOSS_MAP"),
		GS("STAGE2_BOSS_HAICHI"), 
		"",
		string("graphics\\stage2back.png"),
		string("graphics\\m_cp02.png"),
		SoundController::BOSS2,
		GF("STAGE2_BOSS_TIME"),
		string("graphics\\txtgraphic\\stg23.png"),
		string("graphics\\stageselect\\stg23.png"),
		string("graphics\\stageselect\\title23.png")
		);

	maStages[15] = new Stage( 
		GS("STAGE4_MAP"),
		GS("STAGE4_HAICHI"), 
		GS("STAGE4_ZOKUSEI"),
		string("graphics\\stage4back.png"),
		string("graphics\\m_cp03.png"),
		SoundController::STG3,
		GF("STAGE4_TIME"),
		string("graphics\\txtgraphic\\stg31.png"),
		string("graphics\\stageselect\\stg31.png"),
		string("graphics\\stageselect\\title31.png")
		);

	maStages[16] = new Stage( 
		GS("STAGE42_MAP"),
		GS("STAGE42_HAICHI"), 
		GS("STAGE42_ZOKUSEI"),
		string("graphics\\stage4back.png"),
		string("graphics\\m_cp03.png"),
		SoundController::STG3,
		GF("STAGE4_BOSS_TIME"),
		string("graphics\\txtgraphic\\stg32.png"),
		string("graphics\\stageselect\\stg32.png"),
		string("graphics\\stageselect\\title32.png")
		);

	maStages[17] = new Stage( 
		GS("STAGE4_BOSS_MAP"),
		GS("STAGE4_BOSS_HAICHI"), 
		"",
		string("graphics\\stage4back.png"),
		string("graphics\\m_cp03.png"),
		SoundController::BOSS3,
		GF("STAGE4_TIME"),
		string("graphics\\txtgraphic\\stg33.png"),
		string("graphics\\stageselect\\stg33.png"),
		string("graphics\\stageselect\\title33.png")
		);

	maStages[18] = new StaffRoll();

	maStages[19] = new CurtainRollScr(GS("CURTROLL_MAP"),
		string("graphics\\back.png"),
		string("graphics\\m_cp00.png"),
		SoundController::ENDING
		);

	maStages[GAME_OVER_IDX] = new GameOverScr();

}

StageManager::~StageManager(void)
{
}

/*
	ｽﾃｰｼﾞﾏﾈｰｼﾞｬｰの処理
*/
void StageManager::Process()
{
	if( maStages[mCurrentIndex]->IsLoaded() )
		maStages[mCurrentIndex]->Process();
	else{
		GAMECONTROL->GetFader()->SetFadedOut( false );
		// ﾛｰﾄﾞ中
		DX_DRAW("graphics\\fade.png", 0, 0, 0, 0, SP->SCRSZX, SP->SCRSZY);
		
		// now loading..
		char nowloading[15] = "now loading";
		int i;
		for(i=11; i<11+mNowLoadingTenNum; i++)
			nowloading[i] = '.';

		for( ; i<13; i++)
			nowloading[i] = ' ';

		// ｱﾆﾒｰｼｮﾝ
		WAIT_TIMER(mTimer, 0.5)
			mNowLoadingTenNum = (mNowLoadingTenNum+1)%4;
		WAIT_END

		// 描画
		GAMECONTROL->GetDXController()->PrintDebugSting(650, 570, nowloading);
	}
}

/*
	ﾏﾈｰｼﾞｬの初期化
*/
void StageManager::Init()
{
	unsigned id;
	maStages[mCurrentIndex]->Load();
	maStages[mCurrentIndex]->SetLoaded(true);
}

// ｹﾞｯﾀｰ
float StageManager::GetCurScrollPointer()
{
	return maStages[mCurrentIndex]->GetMap()->GetScrollP();
}

// ｹﾞｯﾀｰ
Map* StageManager::GetCurMap()
{
	return maStages[mCurrentIndex]->GetMap();
}

// ステージフォーワード
void StageManager::StageGoForward()
{
	// チュートリアルｽﾃｰｼﾞの場合は、一回ｽﾃｰｼﾞ選択画面に戻る
	if( mCurrentIndex >= GetFirstStageIdx() && mCurrentIndex < GetNotTutorialFirstStageIdx() )
	{
		int save_idx = mCurrentIndex;
		GoToStage( STG_SELECT_IDX );
		((StageSelect*) GetCurrentStage())->SetSelectedIdx(save_idx+1-GetFirstStageIdx());
	}
	else{
		GoToStage( (mCurrentIndex + 1) % STG_LOOP_POINT );
	}
}

/*
	ゲームオーバー画面へいきます。

	前提：　画面が既にフェードアウトされた状態で
	この関数が呼ばれること
*/
void StageManager::GoToGameOver()
{
	GoToStage(GAME_OVER_IDX);
}


/*
	スタート画面へいきます。

	前提：　画面が既にフェードアウトされた状態で
	この関数が呼ばれること
*/
void StageManager::GoToStartScreen()
{
	GoToStage(0);
}

/**
	内部使用です。
	一瞬で飛びます。
	\rStageIdx このｽﾃｰｼﾞに飛ぶ
*/
void StageManager::GoToStage(int rStageIdx)
{
	GAMECONTROL->GetMobManager()->Reset();
	
	// ﾁｭｰﾄﾘｱﾙの場合は生活ﾊﾟﾗﾒｰﾀをﾘｾｯﾄする
	if( IsCurrentStageTutorial() ){
		GAMECONTROL->GetJiki()->ResetChain();
		GAMECONTROL->GetJiki()->ResetEmpacy();
		GAMECONTROL->GetJiki()->ResetLife();
		GAMECONTROL->GetJiki()->ResetTension();
	}

	// 現在実行中のｽﾃｰｼﾞを無効にする
	maStages[mCurrentIndex]->SetLoaded(false);
	mNowLoadingTenNum = 0;
	mTimer = 0.0f;

	THRARGS* t = new THRARGS;
	t->sm = this;
	t->gotoStg = rStageIdx;
	_beginthreadex( NULL, 0, changestage, t, 0, NULL);
}

/**
	\return 現在処理中のｽﾃｰｼﾞ
*/
Stage* StageManager::GetCurrentStage()
{
	return maStages[mCurrentIndex];
}

/*
	ｽﾃｰｼﾞの数を取得する
*/
int StageManager::GetNumStages()
{
	return STG_LOOP_POINT;
}

/*
	選択画面に入るような、最初のｽﾃｰｼﾞの番号を返す
*/
int StageManager::GetFirstStageIdx()
{
	return TUT1_IDX;
}

/*
	選択画面に入るような、ﾁｭｰﾄﾘｱる以外で、最初のｽﾃｰｼﾞの番号を返す
*/
int StageManager::GetNotTutorialFirstStageIdx()
{
	return ST11_IDX;
}

/*
	選択画面に入るような、最終ｽﾃｰｼﾞの番号を返す
*/
int StageManager::GetLastStageIdx()
{
	return TUT1_IDX + 14;
}

/**
* \param stageIdx ｽﾃｰｼﾞ番号
* \return 指定されたのｽﾃｰｼﾞの選択画面用の画像のﾊﾟｽ
*/
string StageManager::GetStageSelectImageGraphic(int stageIdx)
{
	return maStages[stageIdx]->GetSelectImageGraphic();
}

/**
* \param stageIdx ｽﾃｰｼﾞ番号
* \return 指定されたのｽﾃｰｼﾞの選択画面用のﾀｲﾄﾙ画像のﾊﾟｽ
*/
string StageManager::GetStageSelectTitleGraphic(int stageIdx)
{
	return maStages[stageIdx]->GetSelectTitleGraphic();
}

/**
*	現在実行中のｽﾃｰｼﾞがﾁｭｰﾄﾘｱﾙであるかないかを返す
**/
bool StageManager::IsCurrentStageTutorial()
{
	return mCurrentIndex >= GetFirstStageIdx() && mCurrentIndex < GetNotTutorialFirstStageIdx();
}

/**
*	別のスレッドから呼ばれます。
*	ｽﾃｰｼﾞ移動を行います。
*/
void StageManager::ChangeStageOnSepThread(int rStageIdx)
{
	maStages[mCurrentIndex]->UnLoad();

	mCurrentIndex = rStageIdx;

	maStages[mCurrentIndex]->Load();

	// ﾃﾞｰﾀを保存する
	if( mCurrentIndex >= GetNotTutorialFirstStageIdx() && mCurrentIndex <= GetLastStageIdx() ){
		SAVE_DATA( mCurrentIndex - GetFirstStageIdx() );
	}

	maStages[mCurrentIndex]->SetLoaded(true);

	GAMECONTROL->GetFader()->SetFadedOut( true );
}

/*
	スレッド用関数
*/
unsigned __stdcall changestage(void* rThrArgs)
{
	StageManager* sm = ((THRARGS*)rThrArgs)->sm;
	int gotoStage = ((THRARGS*)rThrArgs)->gotoStg;
		
	sm->ChangeStageOnSepThread( gotoStage );
	
	delete rThrArgs;
	return 0;
}

/**
*	デバイスが失われたときにお応答
*/
void StageManager::OnLostDevice()
{
	GetCurrentStage()->OnLostDevice();
}

/**
*	デバイスが失われたときにお応答
*/
void StageManager::OnRestoredDevice()
{
	GetCurrentStage()->OnRestoredDevice();
}