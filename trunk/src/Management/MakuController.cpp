#include "MakuController.h"
#include "GameControl.h"

MakuController::MakuController()
{
	MAKU_UP = GI("MAKU_UP");
	MAKU_DOWN = GI("MAKU_DOWN");
	MAKU_UD = GI("MAKU_UD");
	
	mStatus = CLOSE;
	mPos = MAKU_DOWN;
}

MakuController::~MakuController()
{}

/*
	���C������
*/
void MakuController::Process()
{
	switch (mStatus){
		case OPENING:
			mPos -= MAKU_UD;
			if( mPos <= MAKU_UP ){
				mPos = MAKU_UP;
				mStatus = OPEN;
			}
			break;

		case CLOSING:
			mPos += MAKU_UD;
			if( mPos >= MAKU_DOWN ){
				mPos = MAKU_DOWN;
				mStatus = CLOSE;
			}
			break;
	}
}

/*
	�`��
*/
void MakuController::Draw()
{
	DX_DRAW("graphics\\interface\\inte_curtain_l.png",   0, 0,  0, 0, 50, 535);			//��
	DX_DRAW("graphics\\interface\\inte_curtain_r.png", 750, 0,  0, 0, 50, 535);			//�E

	DX_DRAW("graphics\\interface\\inte_curtain_top.png", 0, 0,  0, 550-mPos, 800, 550);	//��

}

/*
	������
*/
void MakuController::Open()
{
	mStatus = OPENING;
}

/*
	����
*/
void MakuController::Close()
{
	mStatus = CLOSING;
}

/*
	�����Ă��邩
*/
bool MakuController::IsOpen()
{
	return mStatus == OPEN;
}

/*
	���Ă��邩
*/
bool MakuController::IsClosed()
{
	return mStatus == CLOSE;
}

/*
	�����I�ɏオ������Ԃɂ���
*/
void MakuController::SetOpened()
{
	mStatus = OPEN;
	mPos = MAKU_UP;
}

/*
	�����I�ɉ���������Ԃɂ���
*/
void MakuController::SetClosed()
{
	mStatus = CLOSE;
	mPos = MAKU_DOWN;
}
