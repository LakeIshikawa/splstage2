#pragma once

#include "Collision.h"
#include <vector>

#define MAX_FRAMES 10

/*
	Collisionのｾｯﾄです。　ﾌﾚｰﾑを指定することによって、
	あらゆるあたり判定のﾌﾚｰﾑを使い分けることができます。

	例：　攻撃の当たり判定（足の部分だけが当たるとか）
	　　　防御の当たり判定（全身が当たる）
*/
class CollisionSet
{
public:
	CollisionSet(void);
	~CollisionSet(void);

	void AddFrame(int rBango, Collision* pFrame);
	void SetFrame(int rBango);
	Collision* GetFrame(int rFrameIdx);

	Collision* GetCurFrame();
	int	GetIndex() {return mIndex;}

private:
	int mIndex;

	Collision* aFrames[MAX_FRAMES];
};
