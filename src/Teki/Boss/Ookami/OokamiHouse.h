#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\Mob\\Collidable.h"
#include "ParticleGenerator.h"

//! 家の基本ｸﾗｽ
/****************************************************************//**
*	\nosubgrouping
********************************************************************/
class OokamiHouse: public Collidable
{

public:

	//! 標準ｺﾝｽﾄﾗｸﾀ
	OokamiHouse();
	//! 標準ﾃﾞｽﾄﾗｸﾀ
	~OokamiHouse();


	//! 出現位置を設定
	void SetPosX(int rX);
	//! 消滅させる
	void Destroy();
	
	//! 出現
	void Appear();
	//! 消去
	virtual void Disappear();
	//! 破片生成をｽﾄｯﾌﾟ
	void StopParticles();

	//! 1ﾌﾚｰﾑ処理
	void Move();

	//! ｸﾞﾗﾌｨｯｸの取得方法
	virtual string GetGraphicSrc() = 0;
	//! 破片ｼﾞｪﾈﾚｰﾀの作る方法
	virtual void BuildParticleGenerator() = 0;

protected:
	//! 出現した高さ
	float mAppearedHeight;
	float mAlpha;

	ParticleGenerator* mPtGenerator;

	//! ｽﾃｰﾀｽ
	enum{
		APPEARING,
		DISAPPEARING
	} mStatus;

	int OOKAMI_HSSP;

};

