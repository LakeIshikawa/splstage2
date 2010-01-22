#include <string>
#include <vector>
#include <exception>
using namespace std;

#include "ParticleGenerator.h"
#include "..\\..\\..\\Management\\GameControl.h"

/************************************************************//**
*	破片の発射を登録します
*	\param rAngle 発射の初角度
*	\param rSpeed 速度
*	\param rInterval 次の発射までの時間
*	\param rGraphicScr 使用するｸﾞﾗﾌｨｯｸのﾌｧｲﾙ名
****************************************************************/
void ParticleGenerator::BookPartThrow(float rAngle, float rSpeed, 
			float rInterval, string rGraphicSrc)
{
	mData.push_back(PartThrow(rAngle, rSpeed, rInterval, rGraphicSrc));
}

/************************************************************//**
*	発射ﾓｰﾄﾞを設定します
****************************************************************/
void ParticleGenerator::SetMode(PG_MODE rMode)
{
	mMode = rMode;
}

/************************************************************//**
*	1ﾌﾚｰﾑ処理
*	破片を続々と作成して飛ばす。破片の所属はMobControllerとなる
****************************************************************/
void ParticleGenerator::Generate()
{
	// まだ発射していなければ発射する
	if( !mData[mCurPartIdx].thrown ){
		mData[mCurPartIdx].thrown = true;
		Particle* newpart = 
			new Particle(mData[mCurPartIdx].angle, mData[mCurPartIdx].speed, 
			mData[mCurPartIdx].graphic, mX, mY);

		GAMECONTROL->GetMobManager()->Request(newpart, true);
	}

	// 次の破片まで待つ
	WAIT_TIMER(mTimer, mData[mCurPartIdx].interval)
		switch( mMode ){
			case PG_LINEAR:
				{
					mCurPartIdx++;
					if( mCurPartIdx >= mData.size() ) {

						//全破片リセット
						for (int i=0; i<mData.size(); i++) mData[i].thrown = false;
						mCurPartIdx = 0;
					}
					break;
				}

			case PG_RANDOM:
				{
					mData[mCurPartIdx].thrown = false;
					mCurPartIdx = rand()%(mData.size());
					break;
				}
	}
	WAIT_END
}



/************************************************************//**
*	初期化
****************************************************************/
Particle::Particle(float rAngle, float rSpeed, string rGraphic, 
		int rStartX, int rStartY)
{
	mX = rStartX;
	mY = rStartY;
	mSpX = cos(rAngle) * rSpeed;
	mSpY = sin(rAngle) * rSpeed;
	mGraphic = rGraphic;
	mSizeX = GI("OOKAMI_HSPTSX");
	mSizeY = GI("OOKAMI_HSPTSY");
	OOKAMI_HSPTROTSP = GF("OOKAMI_HSPTROTSP")*((rand()%2)==0?1:-1);

	mRotAngle = 0.0f;

	// 当たり判定
	AddFrame(0);
	AddCircle(0, SP->GRID_BOGYO, 24, 24, 24);
	AddTarget(GAMECONTROL->GetJiki());

	mZ = 111.0f;

}

/************************************************************//**
*	1ﾌﾚｰﾑ処理
****************************************************************/
void Particle::Move()
{
	// 画面外は消滅する
	DieIfGamenGai();

	// 動き
	mSpY += SP->GRAVITY;
	mX += mSpX;
	mY += mSpY;

	// 回転
	mRotAngle += OOKAMI_HSPTROTSP;
	if( mRotAngle >= D3DX_PI*2 ) mRotAngle = 0.0f;

	//描画
	DX_SCROLL_ROT_DRAW(mGraphic, mX, mY, 0, 0, mSizeX, mSizeY, mRotAngle);
}


/************************************************************//**
*	当たり判定応答
****************************************************************/
void Particle::CollisionResponse(ICollidable* rCollObject, 
		int rThisGroupId, int rOpGroupId)
{
	Jiki* jiki = dynamic_cast<Jiki*>(rCollObject);
	jiki->InflictDamage();
}
