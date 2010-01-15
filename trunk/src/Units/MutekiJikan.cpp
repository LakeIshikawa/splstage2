#include <string>
#include <vector>
#include <exception>
#include <assert.h>
using namespace std;

#include "MutekiJikan.h"
#include "..\\Management\\GameControl.h"

/************************************************************//**
*	�W���ݽ�׸�
****************************************************************/
MutekiJikan::MutekiJikan() {
	mTimer = -0.0f;
	mMutekiFl = false;
	mMutekiTime = -1.0f;
}

/************************************************************//**
*	���Ԃ��o�߂�����
****************************************************************/
void MutekiJikan::Run() 
{
	verify(mMutekiTime >= 0);

	if( mMutekiFl ){
		// �o��
		mTimer += SP->FrameTime;

		// ���G���ԏI������
		if( mTimer >= mMutekiTime ){
			mTimer = 0.0f;
			mMutekiFl = false;
		}
	}
}

/************************************************************//**
*	���G���Ԃ̐ݒ�
****************************************************************/
void MutekiJikan::SetMutekiTime(float rTime) {
	mMutekiTime = rTime;
}

/************************************************************//**
*	���G���Ԃ����
****************************************************************/
void MutekiJikan::Start() {
	mMutekiFl = true;
}

/************************************************************//**
*	\return ���G��Ԃ�
****************************************************************/
bool MutekiJikan::IsMuteki() {
	return mMutekiFl;
}


/************************************************************//**
*	\return ���̵�޼ު�Ă̺�߰
****************************************************************/
MutekiJikan* MutekiJikan::Clone() {

	MutekiJikan* mtjk = new MutekiJikan();

	// ̨���ނ̺�߰
	mtjk->mMutekiFl = mMutekiFl;
	mtjk->mMutekiTime = mMutekiTime;
	mtjk->mTimer = mTimer;

	return mtjk;
}