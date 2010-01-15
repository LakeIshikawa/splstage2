#include "TxtGraphicController.h"
#include "GameControl.h"

TxtGraphicController::TxtGraphicController()
{
	mTimer = 0.0f;
	mAlpha = 0.0f;
}

TxtGraphicController::~TxtGraphicController()
{}

/*
	�\�����I��������true��Ԃ��܂�
	�\�����̏ꍇ��false
*/
void TxtGraphicController::ShowWithAlphaFade(POSITION rPos,
											 int rSx, int rSy,
											 string rGraphic, 
											 float rTime, 
											 float rSp)
{
	mPos = rPos;
	mSx = rSx;
	mSy = rSy;
	mGraphic = rGraphic;
	mSp = rSp;
	mTime = rTime;

	mIsFinished = false;
	mStatus = FADING_IN;
}

/*
	�\�����I��������true��Ԃ��܂�
	�\�����̏ꍇ��false
*/
void TxtGraphicController::ShowWithEnterFromRight(int rY,
											 int rSx, int rSy,
											 string rGraphic, float rSpX)
{
	mY = rY;
	mX = SP->SCRSZX;
	mSx = rSx;
	mSy = rSy;
	mSpX = rSpX;
	mGraphic = rGraphic;
	
	mIsFinished = false;
	mStatus = ENTERING;
}

/*
	�`��
*/
void TxtGraphicController::Draw()
{
	if( mIsFinished ) return; //�I���������\���ɂ���

	// ����
	switch( mStatus ){
		case FADING_IN:
			mAlpha += mSp;
			if( mAlpha >=1.0f ){
				mAlpha = 1.0f;
				mStatus = DISPLAY;
			}
			break;

		case DISPLAY:
			WAIT_TIMER(mTimer, mTime)
				mStatus = FADING_OUT;
			WAIT_END
				break;

		case FADING_OUT:
			mAlpha -= mSp;
			if( mAlpha <= 0.0f ){
				mAlpha = 0.0f;
				mIsFinished = true;
			}
			break;

		case ENTERING:
			mX -= mSpX;
			// ��ʂ̒��S�ɂ�����~�܂�
			if( mX + mSx/2 <= SP->SCRSZX/2 )
				mStatus = ENT_STOPPING;
			break;

		case ENT_STOPPING:
			WAIT_TIMER(mTimer, 1.0f)
				mStatus = EXITING;
			WAIT_END
			break;

		case EXITING:
			mX -= mSpX;
			if( mX + mSx < 0 )
				mIsFinished = true;
			break;
	}

	// �`��
	switch( mStatus ){
	case FADING_IN:
	case DISPLAY:
	case FADING_OUT:
		switch (mPos){
			case CENTER:
				DX_DRAWALPHA(mGraphic, (SP->SCRSZX-mSx)/2, (SP->SCRSZY-mSy)/2, 0, 0, mSx, mSy, mAlpha);
				break;
		}
		break;

	case ENTERING:
	case ENT_STOPPING:
	case EXITING:
		DX_DRAW( mGraphic, mX, mY, 0, 0, mSx, mSy);
		break;
	}
}

/*
	�I��������
*/
bool TxtGraphicController::IsFinished()
{
	return mIsFinished;
}

/*
	�X�L�b�v
*/
void TxtGraphicController::Reset()
{
	mIsFinished = true;
	mTimer = 0.0f;
	mAlpha = 0.0f;
}