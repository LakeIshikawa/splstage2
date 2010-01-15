#pragma once

#include "Teki.h"

class Kumo : public Teki
{
public:
	Kumo(int rXPx, int rYPx);
	~Kumo(void);

	void _Move(); // 敵から
	
	TEKI_SETUP;

	void CollisionResponse(ICollidable* rCollObject, int rThisGroupId, int rOpGroupId);

	enum STATUS
	{
		ITO,
		OCHI,
		ARUKI
	};

	enum FRAMES
	{
		FR_ITO,
		FR_JIYUU
	};

private:
	// ﾙｰﾁﾝ
	void MapAtHt();

	// 変数群
	static int sMapAtHanteiX[4][MAX_TEN]; // 2点：　0- 床　1- 前
	static int sMapAtHanteiY[4][MAX_TEN];

	// 基本
	STATUS	mStatus;

	// 糸
	int mItoNobi;
	int mItoX;
	int mItoY;

	// 移動用
	int		mMoveStatus; //0-上で停止　1-下がり 2- 下で停止 3- 上り
	float	mTeishiTimer;

	// 当たり判定用
	int mShirabe[4];  // 当たったときに、壁の位置を返す（その軸の座標）
	int mAtari[4];	 // 当たってるとﾌﾗｸﾞが立つ


	//設定定数
	int KUMOSX;
	int KUMOSY;

	float ITO_SP;
	int ITO_LEN;
	float TEISHI_TIME;
	float ARUKI_SP;

};
