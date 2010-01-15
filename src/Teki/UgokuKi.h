#pragma once

#include "Teki.h"

/*
	動く木
*/
class UgokuKi : public Teki
{
public:
	UgokuKi(int rXPx, int rYPx);
	~UgokuKi(void);

	void _Move(); // 敵から

	TEKI_SETUP;
	

private:
	// ﾏｯﾌﾟ当たり判定ﾃﾞｰﾀ
	static int sMapAtHanteiX[4][MAX_TEN]; // 2点：　0- 床　1- 前
	static int sMapAtHanteiY[4][MAX_TEN];

	int mShirabe[4];  // 当たったときに、壁の位置を返す（その軸の座標）
	int mAtari[4];	 // 当たってるとﾌﾗｸﾞが立つ

	
	enum STATUS {
		KAKUSHI,		// 背景に待ち構えて待機
		ACTION,			// 前に出て動き出す
		ARUKI			// 動く
	}  
	mStatus;

	// ﾒｿｯﾄﾞ
	void MapAtHt();

	void CollisionResponse(Collidable* rCollObject, int rThisGroupId, int rOpGroupId);

	// 設定定数
	int UGOKUKISX;
	int UGOKUKISY;

	int UGOKUKIHANI;
	float UGOKUKISPX;

};
