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
	メイン処理
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
	描画
*/
void MakuController::Draw()
{
	DX_DRAW("graphics\\interface\\inte_curtain_l.png",   0, 0,  0, 0, 50, 535);			//左
	DX_DRAW("graphics\\interface\\inte_curtain_r.png", 750, 0,  0, 0, 50, 535);			//右

	DX_DRAW("graphics\\interface\\inte_curtain_top.png", 0, 0,  0, 550-mPos, 800, 550);	//上

}

/*
	あける
*/
void MakuController::Open()
{
	mStatus = OPENING;
}

/*
	閉じる
*/
void MakuController::Close()
{
	mStatus = CLOSING;
}

/*
	あけているか
*/
bool MakuController::IsOpen()
{
	return mStatus == OPEN;
}

/*
	閉じているか
*/
bool MakuController::IsClosed()
{
	return mStatus == CLOSE;
}

/*
	強制的に上がった状態にする
*/
void MakuController::SetOpened()
{
	mStatus = OPEN;
	mPos = MAKU_UP;
}

/*
	強制的に下がった状態にする
*/
void MakuController::SetClosed()
{
	mStatus = CLOSE;
	mPos = MAKU_DOWN;
}
