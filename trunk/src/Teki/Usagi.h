#pragma once

#include "Teki.h"

class Usagi : public Teki
{
public:
	Usagi(int rXPx, int rYPx);
	~Usagi(void);

	void _Move(); // 敵から

	TEKI_SETUP;

	enum STATUS
	{
		TAIKI,
		JUMP_START,
		JUMP,
		LAND
	};

private:
	// ﾙｰﾁﾝ
	void MapAtHt();

	void DieIfGamenGai();

	// ﾃﾞｰﾀ
	static int sMapAtHanteiX[4][MAX_TEN]; // 2点：　0- 床　1- 前
	static int sMapAtHanteiY[4][MAX_TEN];

	// 基本
	STATUS	mStatus;

	// 移動用
	float	mTaikiTimer;

	// 当たり判定用
	int mShirabe[4];  // 当たったときに、壁の位置を返す（その軸の座標）
	int mAtari[4];	 // 当たってるとﾌﾗｸﾞが立つ

	int USAGISX;
	int USAGISY;

	float UTAIKI_TIME;
	float UJUMPSTART_TIME;
	float UJMPSPX;
	float UJMPTAKASA;

};
