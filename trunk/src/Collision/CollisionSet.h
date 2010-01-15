#pragma once

#include "Collision.h"
#include <vector>

#define MAX_FRAMES 10

/*
	Collision�̾�Ăł��B�@�ڰт��w�肷�邱�Ƃɂ���āA
	�����邠���蔻����ڰт��g�������邱�Ƃ��ł��܂��B

	��F�@�U���̓����蔻��i���̕���������������Ƃ��j
	�@�@�@�h��̓����蔻��i�S�g��������j
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
