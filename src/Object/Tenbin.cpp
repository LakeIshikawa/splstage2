#include <exception>
using namespace std;

#include "Tenbin.h"
#include "..\\Management\\GameControl.h"

/************************************************************//**
*	�W���R���X�g���N�^
****************************************************************/
Tenbin::Tenbin(int rXPx, int rYPx, float rZ)
{
	mX = rXPx;
	mY = rYPx;
	mZ = rZ;

	mAshibaL = NULL;
	mAshibaR = NULL;
}

/************************************************************//**
	�W���f�X�g���N�^
****************************************************************/
Tenbin::~Tenbin()
{
	if( mAshibaL ) delete mAshibaL;
	if( mAshibaR ) delete mAshibaR;
}

/************************************************************//**
*	������ƉE����̑�������ۏ؂���
*	- ����̑���ɂ��̂�����Ă鎞�A���̑��ꂪ���R�Ɖ�����A
*	�@�����̑�������̃��\�b�h���㏸�����܂�
*	- �ǂ̑���ɂ���������Ă��Ȃ��ꍇ�A��������낼��̐Î~���
*	  (�z�u���)�ɖ߂�
****************************************************************/
void Tenbin::Move() {

	//***********************
	//***** �����̏��� ******
	//***********************

	// ���ꂪ�܂����݂��Ȃ����
	if( mAshibaL == NULL ){

		// ������쐬����
		mAshibaL = new AshibaTenbin(mX, mY, mZ);
		mAshibaL->SetGraphic(0);

		mAshibaR = new AshibaTenbin(mX + mHrSpace + 
			GI("TENASHIBASX"), mY + mVrSpace, mZ);
		mAshibaR->SetGraphic(1);
	}

	//***********************
	//*** 1�t���[���̏��� ***
	//***********************

	// ����̎q���ړ�������
	mAshibaL->Process();
	mAshibaR->Process();

	// if ���̑���ɕ�������Ă����
	if( mAshibaL->GetRidersNum() > 0 ){

		// -- ���̑���������āA�E�̑�����グ�āA�I��
		mAshibaL->BringDown();
		mAshibaR->BringUp();
		return;
	}

	// if �E�̑���ɕ�������Ă����
	if( mAshibaR->GetRidersNum() > 0 ){

		// -- �E�̑���������āA���̑�����グ�āA�I��
		mAshibaR->BringDown();
		mAshibaL->BringUp();
		return;
	}

	// ���̑��̏ꍇ�́A�����Î~��Ԃɖ߂��ďI��
	mAshibaL->BringBack();
	mAshibaR->BringBack();
}

/************************************************************//**
*	����Ƒ���̉��󔒂̐ݒ�
*	\param rHrSpacePx ����
****************************************************************/
void Tenbin::SetHrSpace(int rHrSpacePx) {
	mHrSpace = rHrSpacePx;
}

/************************************************************//**
*	����Ƒ���̏c����̐ݒ�
*	�u-�v�̏ꍇ�́A���̑��ꂪ�������Ă���
*	�u+�v�̏ꍇ�́A���̑��ꂪ�オ���Ă���
*	\param rVrSpacePx �c�̂���
****************************************************************/
void Tenbin::SetVrSpace(int rVrSpacePx) {
	mVrSpace = rVrSpacePx;
}

/************************************************************//**
*	������폜���āA���ɓV�������N�G�X�g���ꂽ�����ꂪ�č쐬
*	�����悤�ɂ��܂��B
****************************************************************/
void Tenbin::Reset() {
	if( mAshibaL ) { delete mAshibaL; mAshibaL = NULL; }
	if( mAshibaR ) { delete mAshibaR; mAshibaR = NULL; }
}
