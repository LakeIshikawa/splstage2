#pragma once

#include <iostream>
using namespace std;

/*
	�X�N���[���w�i
*/
class ScrollBackground
{
public:
	ScrollBackground(string rGraphic);
	~ScrollBackground();

	void Draw();
	
	// �A�N�Z�X
	void SetScrollP(float rSp);

private:
	float mScpx;
	float mScrSpx;

	string mGraphic;

};