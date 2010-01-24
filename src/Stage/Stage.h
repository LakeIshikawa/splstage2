#pragma once

#include <string>

using namespace std;

#include "Map.h"
#include "Haichi.h"
#include "Zokusei.h"
#include "ScrollBackground.h"
#include "..\\Management\\SoundController.h"
#include "SeigenJikan.h"

class Stage
{
public:
	Stage(string rDataFname, string rTekiFname, string rZokuseiFname, string rScrollBckgImg, 
		string rMapChipGr, SoundController::BGMS rBgm, float rSeigenjikan, string rTitleGraphic,
		string rSelectImageGraphic, string SelectTitleGraphic);
	Stage();
	virtual ~Stage(void);

	// 処理
	virtual void	Load();
	virtual void	UnLoad();
	virtual void	Process();

	// ｱｸｾｽ
	Map*					GetMap();
	Haichi*					GetHaichi();
	CheckpointController*	GetCheckpointController();
	SeigenJikan*			GetSeigenJikan();
	string					GetSelectImageGraphic(){ return mSelectImageGraphic;}
	string					GetSelectTitleGraphic(){ return mSelectTitleGraphic;}
	SoundController::BGMS	GetBGM() { return mBgm; }

	void 					SetLoaded(bool rLoaded) { load_completed = rLoaded; }
	bool					IsLoaded() 			   { return load_completed; }

	// ローストデバイス
	virtual void	OnLostDevice();
	virtual void 	OnRestoredDevice();

protected:
	Map*	mpMap;
	Haichi* mpHaichi;
	Zokusei* mpZokusei;
	CheckpointController* mpCheckpointController;
	SeigenJikan* mpSeigenJikan;

	ScrollBackground* mpScrollBackground;
	string	mDataFname;
	string	mTekiFname;
	string	mZokuseiFname;
	string  mMapChipGr;
	SoundController::BGMS mBgm;
	string mTitleGraphic;
	string mSelectImageGraphic;
	string mSelectTitleGraphic;

	bool inited;
	bool bgm_played;
	int  title_stage;
	bool load_completed;


	void	Init();
};
