#include <assert.h>
#pragma once

// マクロ群
#define DX_DRAW			GameControl::GetGameControl()->GetDXController()->Draw
#define DX_DRAW_BLEND	GameControl::GetGameControl()->GetDXController()->DrawBlend
#define DX_DRAWALPHA	GameControl::GetGameControl()->GetDXController()->DrawAlpha
#define DX_SCROLL_DRAW	GameControl::GetGameControl()->GetDXController()->ScrollDraw
#define DX_SCROLL_ROT_DRAW	GameControl::GetGameControl()->GetDXController()->ScrollRotDraw
#define DX_SCROLL_ROT_DRAWALPHA GameControl::GetGameControl()->GetDXController()->ScrollRotDrawAlpha
#define DX_CENTERROT_DRAWALPHA GameControl::GetGameControl()->GetDXController()->CenterRotDrawAlpha
#define DX_DRAW_CIRCLE	GameControl::GetGameControl()->GetDXController()->DrawCircle
#define DX_DRAW_RECT	GameControl::GetGameControl()->GetDXController()->DrawRect
#define DX_SCROLL_CLWLIGHT_DRAW GameControl::GetGameControl()->GetDXController()->ScrollClipWLightDraw
#define DX_SCROLL_SCREEN_DRAW GameControl::GetGameControl()->GetDXController()->ScrollScreenAlphaDraw

#define GAMECONTROL		GameControl::GetGameControl()
#define CONTROLLIGHT	GAMECONTROL->GetUserLightControl()->GetControlLight()

#define LIGH_END		GameControl::GetGameControl()->GetUserLightControl()->EndEffect()
#define MAP_ATHT		GameControl::GetGameControl()->GetStageManager()->GetCurMap()->AtariHantei
#define MAP_SUPERATHT	GameControl::GetGameControl()->GetStageManager()->GetCurMap()->SuperAtariHantei
#define ISGAMENGAI		GameControl::GetGameControl()->GetStageManager()->GetCurMap()->IsGamenGai

#define WAIT_TIMER(timer, byou) {(timer) += SP->FrameTime; if((timer) >= (byou)){timer = 0.0f;
#define WAIT_END }}

#define STAGE_CLEAR		GameControl::GetGameControl()->GetStageManager()->StageGoForward()

#define SAVE_DATA(n)	GameControl::GetGameControl()->SaveData(n)

#define SHOW			GameControl::GetGameControl()->GetDXController()->PrintDebugSting

#define GS				GameControl::GetGameControl()->GetSettings()->GetString
#define GF				GameControl::GetGameControl()->GetSettings()->GetFloat
#define GI				(int)GameControl::GetGameControl()->GetSettings()->GetFloat

#define SP				GameControl::GetGameControl()->GetSharedParams()

//! 指定のｸﾗｽの全ｵﾌﾞｼﾞｪｸﾄのﾀｰｹﾞｯﾄﾘｽﾄから自分をはずす
#define REMOVE_FROM_TARGET_LIST( cl ) GAMECONTROL->GetMobManager()->RemoveFromEveryTarget<cl>( this );

// verify(expression) マクロの定義 
//#define NDEBUG
#ifdef NDEBUG
#define verify(expression) expression
#else // #ifdef NDEBUG
#define verify(expression) assert( 0 != (expression) )
#endif // #ifdef NDEBUG


#include ".\UserLightControl.h"
#include "..\\Light\\LightManager.h"
#include "..\\Stage\\StageManager.h"
#include "..\\Mob\\MobManager.h"
#include "..\\Event\\EventManager.h"
#include "..\\Jiki\\Jiki.h"
#include "MakuController.h"
#include "DXController.h"
#include "SoundController.h"
#include "Fader.h"
#include "TxtGraphicController.h"
#include "..\\Settings\\Settings.h"
#include "..\\Settings\\SharedParams.h"
#include "Cheats\\CheatsController.h"


/*
	ゲームを操作するためのAPI
*/
class GameControl
{
public:

	// シングルトン
	static GameControl*	GetGameControl()		{ return sGameControl; }

	// マネージャー
	UserLightControl*	GetUserLightControl()	{ return mpUserLightControl; }
	LightManager*		GetLightManager()		{ return mpLightManager; }
	StageManager*		GetStageManager()		{ return mpStageManager; }
	MobManager*			GetMobManager()			{ return mpMobManager; }
	EventManager*		GetEventManager()		{ return mpEventManager; }
	DXController*		GetDXController()		{ return mpDXController; }
	SoundController*	GetSoundController()	{ return mpSoundController; }
	Fader*				GetFader()				{ return mpFader; }
	Settings*			GetSettings()			{ return mpSettings; }
	SharedParams*		GetSharedParams()		{ return mpSharedParams; }
	TxtGraphicController* GetTxtGraphicController() { return mpTxtGraphicController; }
	MakuController*		GetMaku()				{ return mpMaku; }
	CheatsController*	GetCheatsController()	{ return mpCheatsController; }

	// 自機
	Jiki*				GetJiki()				{ return mpJiki; }

	// ルーチン
	void				GameInit(HWND rHwnd);
	void				GameLoop();

	// エラー
	void				ThrowError(char* msg, ...);

	// 機能
	void 				SaveData(int stageIdx);

	// 終了確認ダイアログ
	void				ExitDialog();

	// デバイスが喪失されたら救助する
	void				RestoreLostDevice();

private:
	GameControl();
	~GameControl(void);

	// シングルトン
	static GameControl* sGameControl;

	// マネージャー
	UserLightControl*	mpUserLightControl;
	LightManager*		mpLightManager;
	StageManager*		mpStageManager;
	MobManager*			mpMobManager;
	EventManager*		mpEventManager;
	DXController*		mpDXController;
	SoundController*	mpSoundController;
	Fader*				mpFader;
	Settings*			mpSettings;
	SharedParams*		mpSharedParams;
	TxtGraphicController* mpTxtGraphicController;
	MakuController*		mpMaku;
	CheatsController*	mpCheatsController;

	// 自機
	Jiki*				mpJiki;

	// ルーチン
	void				CreateControlsAndManagers(HWND rHwnd);

	// デバイス喪失
	bool				g_bDeviceLost;

};
