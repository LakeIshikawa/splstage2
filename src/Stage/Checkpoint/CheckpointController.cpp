#include "CheckpointController.h"
#include "Checkpoint.h"
#include "..\\..\\Management\\GameControl.h"


/************************************************************//**
*	コンストラクタ
****************************************************************/
CheckpointController::CheckpointController()
{}

/************************************************************//**
*	\param rAddMe 追加するチェックポイント
****************************************************************/
void CheckpointController::Add(Checkpoint *rAddMe)
{
	lstCheckpoints.push_back( rAddMe );
}

/************************************************************//**
*	\param rDeathPoint 死んだところのX座標(スクロール入り)
****************************************************************/
int CheckpointController::GetStartPointX(int rDeathPointX)
{
	for each( Checkpoint* c in lstCheckpoints ){
		if( c->GetX() < rDeathPointX ){
			return c->GetX();
		}
	}

	// スタートから
	return GI("HERINITX");
}

/************************************************************//**
*	\param rDeathPoint 死んだところのX座標(スクロール入り)
****************************************************************/
int CheckpointController::GetStartPointY(int rDeathPointX)
{
	for each( Checkpoint* c in lstCheckpoints ){
		if( c->GetX() < rDeathPointX ){
			return c->GetY();
		}
	}

	// スタートから
	return GI("HERINITY");
}

/************************************************************//**
*	リストの順番を逆にする
****************************************************************/
void CheckpointController::ReverseList()
{
	if( !lstCheckpoints.empty() )
		lstCheckpoints.reverse();
}

/************************************************************//**
*	チェックポイントを全部消します
****************************************************************/
void CheckpointController::UnLoad()
{
	for each( Checkpoint* c in lstCheckpoints ){
		delete c;
	}

	lstCheckpoints.clear();
}