#pragma once

#include <string>
using namespace std;

#include "ParticleEmitter.h"
#include "PtZigZagVertWave.h"

//! 火柱型ﾊﾟｰﾁｸﾙ発生装置
/****************************************************************//**
*	一定速度。
*	上下のみ。
*	ﾊﾟｰﾃぃｸﾙ数とﾃｸｽﾁｬｰ指定可
*	\nosubgrouping
********************************************************************/
class PeHibashira : public ParticleEmitter
{
public:

	/****************************************************************//**
*	\name ﾗｲﾌ循環
********************************************************************/
/*@{*/
	PeHibashira(int rX, int rY, int rNumParticles, string rTexture, 
		int rWidth, int rHeight, bool rUpdown);
	~PeHibashira(void);
/*@}*/


public:

	//! 1ﾌﾚｰﾑ処理
	void Update();
	//! ﾊﾟｰﾃｨｸﾙの初期化
	void InitParticles(D3DCOLOR rColor);
	//! 一行を発射する
	void FireLine();

	//! ﾊﾟｰﾃｨｸﾙの取得方法
	Particle* GetParticle(int rIdx) { return &mParticles[rIdx]; }

protected:
	//! 発射ﾀｲﾏｰ
	float mFireTimer;

	//! 火柱の横幅
	int mWidth;
	//! 火柱の縦幅
	int mHeight;

	//! ﾊﾟｰﾃｨｸﾙ
	PtZigZagVertWave* mParticles;

	//! 上下
	bool mUpDown;

	// 設定定数
	int HIBASHIRA_LNPART;
	float HIBASHIRA_FIREINT;
	float HIBASHIRA_BASESPX;
	float HIBASHIRA_PTLFTIME;

};
