#pragma once

#include <list>

using namespace std;

class Checkpoint;

/****************************************************************//**
*	\file CheckpointController.h
*	チェックポイントの管理
********************************************************************/

//! チェックポイントを管理するオブジェクト
/****************************************************************//**
*	ヒロインが死亡したとき復活する位置の管理を担当する
*
*	\nosubgrouping
********************************************************************/
class CheckpointController 
{
	/************************************************************//**
	*	\name ﾗｲﾌ循環
	****************************************************************/
	/*@{*/
	public:
		CheckpointController(void);
		~CheckpointController(void) {}
	/*@}*/

	/************************************************************//**
	*	\name 使うﾒｿｯﾄﾞ
	*	処理に便利な機能を提供するﾒｿｯﾄﾞ。
	****************************************************************/	
	/*@{*/

	//! 追加
	void Add( Checkpoint* rAddMe );

	//! アンロード
	void UnLoad();

	//! 復活位置の取得(X)
	int GetStartPointX( int rDeathPointX );

	//! 復活位置の取得(Y)
	int GetStartPointY( int rDeathPointX );

	//! リストを逆にする
	void ReverseList();

	/*@}*/


private:
	list<Checkpoint*> lstCheckpoints;

};
