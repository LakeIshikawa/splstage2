#pragma once

#include "..\\..\\Teki.h"
#include "ThrowApple.h"

#include <list>

/*
	ボスの魔女
*/
class Majo : public Teki
{
public:

	// 基本
	enum STATUS{
		WIN,
		WINBACK,
		WINDAMAGE,
		DOOR,
		DOORTHROW,
		DOORTHROWEND,
		DOOREXIT,
		DOORDAMAGE,
		DIYING,
		DEAD
	};


	Majo();
	~Majo();

	void _Move(); // 敵から

	TEKI_SETUP;

	// インターフェース
	void InflictDamage();
	void Activate();

	// ﾙｰﾁﾝ
	void MapAtHt();

	void DousaEnd();

	void CollisionResponse(ICollidable *rCollObject, int rThisGroupId, int rOpGroupId);

	void DieIfGamenGai() {}

	void KobitoDied();

	int GetEntPt() { return mEntPt; }
	STATUS GetStatus() { return mStatus; }

	static Map::HITPOINT sMapAtHanteiX; // 2点：　0- 床　1- 前
	static Map::HITPOINT sMapAtHanteiY;

	static int sShutugenX[5];
	static int sShutugenY[5];

	static int sRingoX[5];
	static int sRingoY[5];

	static float sDieSpX[5];


	
private:

	// 出現地を選ぶ
	void SelectEntPoint();

	void RollingAppleCreate(int rXPx, int rYPx, int rType);
	void ThrowAppleCreate(int rXPx, int rYPx, int rMuki);
	void AppleOtosu();
	void AppleThrow();
	void KobitoCreate();

	void Die();

	STATUS	mStatus;

	STATUS mSaveStatus;

	enum FRAME{
		FR_WIN,
		FR_DOOR
	};

	// タイマー
	float	mTaikiTimer;
	float	mDieTimer;

	float mSaveSpX;

	// 当たり判定用
	int mShirabe[4];  // 当たったときに、壁の位置を返す（その軸の座標）
	int mAtari[4];	 // 当たってるとﾌﾗｸﾞが立つ

	Apple* mDropMe;
	ThrowApple* mThrowMe;

	int mEntPt;

	bool mKobitoOut;

	int mHp;

	// 設定定数
	int MAJOSX;
	int MAJOSY;
	float MAJO_ARUKI_SPX;

	bool mActive;
	bool dmgFlag;
	
};
