#pragma once

#include <string>

using namespace std;

/*
	ステージクリア、アクトスタートなどで
	表示する文字グラフィックの管理

	一回に一枚の表示まで可能となります。
	複数のグラフィックを同時に表示したい場合、
	このコントローラーの複数インスタンスをかかって
	ください。
	
	:UGLY:
	:UGLY:
*/
class TxtGraphicController
{
public:
	TxtGraphicController();
	~TxtGraphicController();

	enum POSITION{
		CENTER
	};

	// アルファでﾌｪｰﾄﾞｲﾝする
	void ShowWithAlphaFade(POSITION rPos, int rSx, int rSy, 
		string rGraphic, float rTime, float rSp);
	
	// 右から文字が入ってきて、いったん真ん中に止まって、左に出て行く
	void ShowWithEnterFromRight( int rY, int sX, int sY, string rGraphic, float rSpX );

	// 表示は終了したかを判定する
	bool IsFinished();

	// 現在行われている作業を中断し、初期状態に戻ります
	void Reset();

	void Draw();

private:
	float mTimer;
	
	enum STATUS{
		FADING_IN,
		DISPLAY,
		FADING_OUT,
		ENTERING,
		ENT_STOPPING,
		EXITING
	} mStatus;

	// 引数保存
	float mAlpha;
	float mSp;
	float mTime;
	POSITION mPos;
	int mSx;
	int mSy;
	string mGraphic;

	int mY;
	int mX;
	float mSpX;

	bool mIsFinished;

};