#pragma once

#include "Teki.h"

class Kaeru : public Teki
{
public:
	Kaeru(int rXPx, int rYPx);
	~Kaeru(void);

	void _Move(); // 敵から

	TEKI_SETUP;

	enum STATUS
	{
		TAIKI,
		JUMP_START,
		JUMP
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

	int KAERUSX;
	int KAERUSY;

	float TAIKI_TIME;
	float JUMPSTART_TIME;
	float JMPSPX;
	float JMPTAKASA;

};
