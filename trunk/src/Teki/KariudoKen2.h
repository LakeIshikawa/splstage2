#pragma once

#include "Teki.h"

/*
	剣を持った狩人
*/
class KariudoKen2 : public Teki
{
public:
	KariudoKen2(int rXPx, int rYPx);
	~KariudoKen2(void);

	void _Move(); // 敵から

	void Move();
	void Die();
	void Draw();

	TEKI_SETUP;
	

private:
	// ﾏｯﾌﾟ当たり判定ﾃﾞｰﾀ
	static int sMapAtHanteiX[4][MAX_TEN]; // 2点：　0- 床　1- 前
	static int sMapAtHanteiY[4][MAX_TEN];

	int mShirabe[4];  // 当たったときに、壁の位置を返す（その軸の座標）
	int mAtari[4];	 // 当たってるとﾌﾗｸﾞが立つ

	float mKgTimer;	// タイマー

	bool mSeFl;	//SEﾌﾗｸﾞ


	enum STATUS {
		ARUKI,		// 歩き
		WAIT1,		// 攻撃直前
		KOGEKI,		// 攻撃
		WAIT2,		// 攻撃直後
		SHINDA		// 死
	}  
	mStatus;

	enum FRAMES
	{
		FR_KAMAE,	// ﾅｲﾌを構えてるとき
		FR_KNDOWN,	// ﾅｲﾌが下がってるとき
		FR_ZANZOU	// ﾅｲﾌを振ってるとき
	};


	// ﾒｿｯﾄﾞ
	void MapAtHt();
	void Ataridp();
	void HtFrame();

	// 設定定数
	int KARIKEN2SX;
	int KARIKEN2SY;

	float KARIKEN2SPX;
	float KARIKEN2KGHANI;
	float KARIKEN2WTM1;
	float KARIKEN2WTM2;
};
