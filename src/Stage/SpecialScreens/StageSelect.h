#pragma once

#include "..\\Stage.h"

/*
	À²ÄÙ‰æ–Ê
*/
class StageSelect : public Stage
{
public:
	StageSelect(string rDataFname, string rScrollBckgImg, string rMapChipGr, SoundController::BGMS rBgm);
	~StageSelect();

	void Process();
	void Load();
	void UnLoad();

	void SetSelectedIdx(int rIdx);

private:

	void Init();
	void LoadSaveData();
	void ProcessUserControl();
	void DrawInterface();
	void DrawInterfaceAboveLight();
	void GoToLeft();
	void GoToRight();

	int stage;
	int selectedIdx;
	int saveStageTdx;

	int scroll;
	int scrollNLRdir;
	float alpha;
	float curScroll;
};