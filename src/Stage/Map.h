#pragma once

#include <string>
#include <vector>
#include <d3dx9.h>
#include "..\\Teki\\Teki.h"

using namespace std;

#define MAX_TEN 20

/*
	ﾏｯﾌﾟ
*/
class Map
{
public:
	
	////////////////////////////// タイプ宣言 ////////////////////////////////////
	typedef int HITPOINT[4][MAX_TEN];
	typedef int D4AR[4];


	Map(void);
	virtual ~Map(void);

	// ﾌｧｲﾙをﾛｰﾄﾞ
	virtual int Load(string rFName, string rMapChipGr);
	virtual void UnLoad();

	// 表示・ｽｸﾛｰﾙ
	virtual void Process();
	
	// ｽｸﾛｰﾙ
	void SetScrollP(int rScrlPoint);
	int  GetScrollP();
	float GetScrollSp();

	int	GetNGamen();
	int GetMaxScrollP();


	bool IsGamenGai(int rChipType);
	bool IsGamenGai(int rX, int rY, int rSx, int rSy);

	int AtariHantei(int rX, int rY); //当たり判定(引数はﾋﾟｸｾﾙ単位

	// ｽｰﾊﾟｰあたり判定！！ (関数解説をご参照ください)
	void SuperAtariHantei(float rX, float rY, bool rMuki, float rSpX, float rSpY,
		float rAccX, float rAccY, HITPOINT rMapAtHtX, HITPOINT rMapAtHtY,
		int rSizeX, int rSizeY, int *outAtari, int *outKabeIchi);



protected:
	
	// 変数群
	int	mNGamen;	// ｽﾃｰｼﾞの画面数

	vector< vector< int >* >	mData;			//ﾏｯﾌﾟﾃﾞｰﾀ
	LPDIRECT3DTEXTURE9*		mGamenSprites;	//画面ｽﾌﾟﾗｲﾄ配列

	float	mScpx;		// ｽｸﾛｰﾙﾎﾟｲﾝﾀ
	int		mMaxScr;	// ｽｸﾛｰﾙﾎﾟｲﾝﾀの最大値

	float	mScrSp;		// ｽｸﾛｰﾙ速度SS

	LPDIRECT3DTEXTURE9	mMapChipTexture;

	// 関数群
	void Draw();
	virtual void Scroll();

	int	GetMukiMult(int rMuki);

	int LoadFromFile(string rFName);

	// 設定定数
	int ALPHA_LINE;
	int BETA_LINE;
	float SCR_SP1;
	float SCR_SP2;
	int HER_SCRW;


};
