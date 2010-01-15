#include ".\collisionset.h"

CollisionSet::CollisionSet(void)
{
	// ؽď�����
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
	Collision�ڰт�ǉ�����
*/
void CollisionSet::AddFrame(int rBango, Collision *pFrame)
{
	aFrames[rBango] = pFrame;
}

/*
	�w�肳�ꂽ�ڰт�ݒ肷��
*/
void CollisionSet::SetFrame(int rBango)
{
	mIndex = rBango;
}

/*
	�ڰт��Q�b�g
*/
Collision* CollisionSet::GetFrame(int rBango)
{
	return aFrames[rBango];
}

/*
	���ݎg�p�����ڰт��擾
*/
Collision* CollisionSet::GetCurFrame()
{
	return aFrames[mIndex];
}