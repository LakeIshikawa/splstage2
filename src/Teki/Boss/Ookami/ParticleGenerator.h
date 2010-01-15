#include <string>
#include <vector>
#include <exception>
using namespace std;

#pragma once

#include "..\\..\\..\\Mob\\Collidable.h"

//! 破片ｼﾞｪﾈﾚｰﾀ
/****************************************************************//**
*	破片を飛び散らかす
*	\nosubgrouping
********************************************************************/
class ParticleGenerator
{

	public: 
		//! 標準ｺﾝｽﾄﾗｸﾀ
		ParticleGenerator(int rX, int rY) :
		  mMode(PG_LINEAR), mTimer(0.0f), mCurPartIdx(0), mX(rX), mY(rY){}

		//! 破片の飛ばし方
		enum PG_MODE {
			PG_RANDOM,	//! ｸﾞﾗﾌｨｯｸﾘｿｰｽをﾗﾝﾀﾞﾑに使用
			PG_LINEAR	//! ｸﾞﾗﾌｨｯｸｿｰｽを一個ずつ順番に使用
		};


		//! 破片の発射を予約
		void BookPartThrow(float rAngle, float rSpeed, 
			float rInterval, string rGraphicSrc);

		//! ﾓｰﾄﾞの指定
		void SetMode(PG_MODE rMode);


		//! 飛ばす
		void Generate();

protected:

	//! ﾃﾞｰﾀとして登録される発射予定のｵﾌﾞｼﾞｪｸﾄ
	class PartThrow{
	public:
		PartThrow(float rAngle, float rSpeed, float rInterval, string rGraphic):
		  angle(rAngle), speed(rSpeed), interval(rInterval), graphic(rGraphic), thrown(false){}

		float angle;
		float speed;
		float interval;
		string graphic;
		bool thrown;
	};

	PG_MODE mMode;
	vector<PartThrow> mData;
	float mTimer;
	int mCurPartIdx;
	int mX;
	int mY;
};

//! 破片
/****************************************************************//**
*	破片
*	\nosubgrouping
********************************************************************/
class Particle : public Collidable
{
public:
	
	//! 標準ｺﾝｽﾄﾗｸﾀ
	Particle(float rAngle, float rSpeed, string rGraphic, 
		int rStartX, int rStartY);

	//! 1ﾌﾚｰﾑ処理
	void Move();

	//! 当たり判定応答
	void CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId);

private:
	//! 角度
	float mAngle;
	//! 回転角度
	float mRotAngle;
	//! ｸﾞﾗﾌｨｯｸ
	string mGraphic;

	// 設定定数
	float OOKAMI_HSPTROTSP;

};
