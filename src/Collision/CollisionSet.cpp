#include ".\collisionset.h"

CollisionSet::CollisionSet(void)
{
	// ﾘｽﾄ初期化
	for(int i=0; i<MAX_FRAMES; i++)
		aFrames[i] = NULL;

	mIndex = 0;
}

CollisionSet::~CollisionSet(void)
{
	for each( Collision* frame in aFrames ){
		delete frame;
	}
}


/*
	Collisionﾌﾚｰﾑを追加する
*/
void CollisionSet::AddFrame(int rBango, Collision *pFrame)
{
	aFrames[rBango] = pFrame;
}

/*
	指定されたﾌﾚｰﾑを設定する
*/
void CollisionSet::SetFrame(int rBango)
{
	mIndex = rBango;
}

/*
	ﾌﾚｰﾑをゲット
*/
Collision* CollisionSet::GetFrame(int rBango)
{
	return aFrames[rBango];
}

/*
	現在使用中のﾌﾚｰﾑを取得
*/
Collision* CollisionSet::GetCurFrame()
{
	return aFrames[mIndex];
}