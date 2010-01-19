#include <string>
#include <vector>
#include <stdarg.h>
using namespace std;

#include "AnimationSet.h"
#include "..\\Management\\GameControl.h"

/************************************************************//**
*	�W���R���X�g���N�^
****************************************************************/
AnimationSet::AnimationSet()
{
	mCurIdx = 0;
}

/************************************************************//**
*	�W���f�X�g���N�^
****************************************************************/
AnimationSet::~AnimationSet()
{
	for each(pair<int, Animation*> p in mAnimations){
		delete p.second;
	}
}

/************************************************************//**
*	\param rElapsedTime �O�񂩂�̌o�ߎ���
****************************************************************/
void AnimationSet::ElapseTime(float rElapsedTime)
{
	verify( mAnimations[mCurIdx] != NULL );
	
	// ���Ԃ��o�߂�����
	if( !mAnimations.empty() ){
		mAnimations[mCurIdx]->ElapseTime( rElapsedTime );
	}
}

/************************************************************//**
*	\param rIdx ��Ұ��݂��ے����鐮���B�擾����ɂ͂�����g�p���܂��B
*	\param rNewAnimation �ǉ������݂̱�Ұ���
****************************************************************/
void AnimationSet::AddAnimation(int rIdx, Animation* rNewAnimation) 
{
	verify(mAnimations[rIdx] == NULL);
	mAnimations[rIdx] = rNewAnimation;
}

/************************************************************//**
*	\param rIdx �擾��������Ұ��݂̔ԍ�
*	\return ���̱�Ұ���
****************************************************************/
Animation* AnimationSet::GetAnimation(int rIdx) 
{
	verify( mAnimations[rIdx] != NULL );
	return mAnimations[rIdx];
}

/************************************************************//**
*	\param rIdx �ݒ肵������Ұ��݂̔ԍ�
****************************************************************/
void AnimationSet::SetCurAnimation(int rIdx)
{
	verify( mAnimations[rIdx] != NULL );
	mCurIdx = rIdx;
}

/************************************************************//**
*	\return ���ݍĐ����̱�Ұ���
****************************************************************/
Animation* AnimationSet::GetCurAnimation()
{
	verify( mAnimations[mCurIdx] != NULL );
	return mAnimations[mCurIdx];
}


/************************************************************//**
*	\return ���ݍĐ�����Ұ��݂̔ԍ�
****************************************************************/
int AnimationSet::GetCurAnimationIdx()
{
	verify( mAnimations[mCurIdx] != NULL );
	return mCurIdx;
}