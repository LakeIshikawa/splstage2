#pragma once

#include "Stage.h"

#include <d3dx9.h>

#define N_STAGES 25 + 1

/*
	ステージを管理するクラス
*/
class StageManager
{
public:
	StageManager(void);
	~StageManager(void);

	Stage*	GetCurrentStage();
	void	StageGoForward();
	void	StageGoBack();

	float	GetCurScrollPointer();
	Map*	GetCurMap();

	void	Init();
	void	Process();

	// インターフェース
	void	GoToGameOver();
	void	GoToStartScreen();
	void	GoToStage(int rStageIdx);

	void 	ChangeStageOnSepThread(int rStageIdx);

	// アクセス
	int		GetNumStages();
	int		GetFirstStageIdx();
	int		GetNotTutorialFirstStageIdx();
	int		GetLastStageIdx();
	string  GetStageSelectImageGraphic(int stageIdx);
	string  GetStageSelectTitleGraphic(int stageIdx);

	bool	IsCurrentStageTutorial();

private:
	Stage*	maStages[N_STAGES];
	int		mCurrentIndex;

	int 	mNowLoadingTenNum;
	float 	mTimer;
};

struct THRARGS
{
	StageManager* sm;
	int			  gotoStg;
};

// ｽﾃｰｼﾞを別のスレッドでﾛｰﾄﾞﾙｰﾁﾝ
unsigned __stdcall changestage(void* rThrArgs);
