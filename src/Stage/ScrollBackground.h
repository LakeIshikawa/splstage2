#pragma once

#include <iostream>
using namespace std;

/*
	スクロール背景
*/
class ScrollBackground
{
public:
	ScrollBackground(string rGraphic);
	~ScrollBackground();

	void Draw();
	
	// アクセス
	void SetScrollP(float rSp);

private:
	float mScpx;
	float mScrSpx;

	string mGraphic;

};