#include <string>
#include <vector>
#include <algorithm>
#include <exception>
#include <assert.h>
using namespace std;

#include "ActionControllable.h"
#include "ActionState.h"
#include "IActionThread.h"
#include "..\\..\\Management\\GameControl.h"
#include "..\\MobDrawer\\MobDrawer.h"


/************************************************************//**
*	初期ｽﾃｰﾄを作ります。
*	作る方法は実現ｸﾗｽが指定するとします。
****************************************************************/
ActionControllable::ActionControllable(){
	mIsDead = false;
}

/************************************************************//**
*	まだ残っているｱｸｼｮﾝを消去します
****************************************************************/
ActionControllable::~ActionControllable(){

}


/************************************************************//**
*	- 移動させる
*	- 新しいｱｸｼｮﾝを作成する
*	- ｱﾆﾒｰｼｮﾝさせる
*	- 描画させる
****************************************************************/
void ActionControllable::Move() {

	verify(!mStates.empty());

	// 現在実行中のｽﾃｰﾄを取得
	ActionState* curAction = mStates.back();
	// 現在実行中のｱｸｼｮﾝを1ﾌﾚｰﾑ進ませる
	bool finished = curAction->Update();

	// ｱﾆﾒｰｼｮﾝに時間が経過したことを通知する
	curAction->ElapseTime( SP->FrameTime );

	// 現在実行中のｱｸｼｮﾝが終了の場合
	if( finished ) {
		// ｴｸﾞｼﾞｯﾄを通知する
		curAction->OnExit();
		// 終了したｱｸｼｮﾝをﾘｽﾄから解除
		mStates.remove( curAction );

		// 消滅の場合は、現ｽﾃｰﾄを開放して終了する
		if( mIsDead ){
			delete curAction;
			return;
		}
	
		// 実行見込みのｱｸｼｮﾝがかったら
		if( mStates.empty()){
			// 新ｽﾃｰﾄを作る
			AddNewStates( curAction );
			if( !mStates.back()->WasInterrupted() ) mStates.back()->OnEnter();
		}
		// まだ実行見込みのｱｸｼｮﾝがあったら
		else {
			// 新しい現ｽﾃｰﾄをﾋﾞﾙﾄﾞ
			mStates.back()->BuildState( curAction, this );
			if( !mStates.back()->WasInterrupted() ) mStates.back()->OnEnter();
		}
		// 不要になった前ｽﾃｰﾄを開放
		delete curAction;
		// 現ｽﾃｰﾄとして新しく作ったｽﾃｰﾄを指定
		curAction = mStates.back();
	} //if finished

	// 平行処理
	for each( IActionThread* t in mThreads ){
		t->Run();
	}

	// 描画
	if( curAction->GetMobDrawer() ){
		curAction->GetMobDrawer()->Draw();
	}
}


/************************************************************//**
*	\return 現在使用中の当たり判定
****************************************************************/
Collision* ActionControllable::GetCurFrame()
{
	verify( !mStates.empty() );
	return mStates.back()->GetCollision();
}


/************************************************************//**
*	ｱｸｼｮﾝが割り込みで追加されます。現在実行中のｱｸｼｮﾝは2番目の場所
*	に移動され、割り込みｱｸｼｮﾝが終わりしだい再開します。
*	
*	\note 再開するときの初期情報は、ｱｸｼｮﾝが定めるものですし、
*	特別な処理などありません。ただし、OnEnter()は再び呼び出されない。
*	割り込みｱｸｼｮﾝは普通のｱｸｼｮﾝとして追加され、普通のｱｸｼｮﾝと
*	同様に終了する。
****************************************************************/
void ActionControllable::BreakInAction(ActionState* rNewState) {

	// ﾘｽﾄが空ではないぞ
	verify(!mStates.empty());

	// 現在実行中のｱｸｼｮﾝの取得
	ActionState* curAction = mStates.back();
	curAction->SetInterrupted(true);

	// 追加見込みのｽﾃｰﾄをﾋﾞﾙﾄﾞ
	rNewState->BuildState( curAction, this );
	rNewState->OnEnter();

	// 追加
	mStates.push_back( rNewState );
}

/************************************************************//**
*	ｱｸｼｮﾝをﾘｽﾄに追加します。すべての実行見込みｱｸｼｮﾝが終わり次第
*	実行されます。
****************************************************************/
void ActionControllable::QueueAction(ActionState* rNewState) {
	mStates.push_front( rNewState );
}

/************************************************************//**
*	\param rNewState 現ｱｸｼｮﾝが終了し次第、このｱｸｼｮﾝが実行される
****************************************************************/
void ActionControllable::AddNextAction(ActionState* rNewState) {

	list<ActionState*>::iterator st = mStates.end();
	st--;
	mStates.insert( st, rNewState );
}

/************************************************************//**
*	ｱｸｼｮﾝが割り込みで追加されます。現在実行中のｱｸｼｮﾝは強制的に
*	終了します。その際にOnExit()が呼ばれます。
****************************************************************/
void ActionControllable::BreakInActionNoResume(ActionState* rNewState) {

	// ﾘｽﾄが空ではないぞ
	verify(!mStates.empty());

	// 現在実行中のｱｸｼｮﾝの取得
	ActionState* curAction = mStates.back();
	curAction->OnExit();
	mStates.pop_back();

	// 追加見込みのｽﾃｰﾄをﾋﾞﾙﾄﾞ
	rNewState->BuildState( curAction, this );
	rNewState->OnEnter();

	// 追加
	mStates.push_back( rNewState );
}

/************************************************************//**
*	無条件
****************************************************************/
void ActionControllable::RemoveAllActions(ActionState* rExclude) 
{
	//for each (ActionState* as in mStates) delete as;
	mStates.clear();
	mStates.push_back(rExclude);
	mThreads.clear();
}

/************************************************************//**
*	リストの決まったとこに追加する
****************************************************************/
void ActionControllable::InsertAfter(ActionState* rInsertMe, ActionState* rAfterMe)
{
	mStates.insert( find(mStates.begin(), mStates.end(), rAfterMe ), rInsertMe );
}

/************************************************************//**
*	現在ﾘｽﾄに入っているアクションをﾗﾝﾄﾞﾑな順番に置き換える
****************************************************************/
void ActionControllable::ShuffleActions() 
{
	vector<ActionState*> temp;
	temp.resize(mStates.size());
	copy(mStates.begin(), mStates.end(), temp.begin());
	random_shuffle(temp.begin(), temp.end());
	copy(temp.begin(), temp.end(), mStates.begin());
}

/************************************************************//**
*	\return 先頭のｱｸｼｮﾝｽﾃｰﾄ
****************************************************************/
ActionState* ActionControllable::GetFirstState() 
{
	return (mStates.back());
}

/************************************************************//**
*	\return 現在のX座標
****************************************************************/
float ActionControllable::GetX()
{
	verify( !mStates.empty() );
	return mStates.back()->GetX();
}

/************************************************************//**
*	\return 現在のY座標
****************************************************************/
float ActionControllable::GetY()
{
	verify( !mStates.empty() );
	return mStates.back()->GetY();
}

/************************************************************//**
*	\return 現在の1ﾌﾚｰﾑの横幅
****************************************************************/
int ActionControllable::GetFrameSizeX() 
{
	verify( !mStates.empty() );
	return mStates.back()->GetFrameSizeX();
}

/************************************************************//**
*	\return 現在の1ﾌﾚｰﾑの縦幅
****************************************************************/
int ActionControllable::GetFrameSizeY() 
{
	verify( !mStates.empty() );
	return mStates.back()->GetFrameSizeY();
}

/************************************************************//**
*	\return 現在の向き
****************************************************************/
bool ActionControllable::GetMuki()
{
	verify( !mStates.empty() );
	return mStates.back()->GetMuki();
}

/************************************************************//**
*	当たり判定応答は現ｱｸｼｮﾝに任せておく
****************************************************************/
void ActionControllable::CollisionResponse(ICollidable* rCollObject, 
										   int rThisGroupID, int rOpGroupID) 
{
	// ｱｸｼｮﾝがあったら
	if( !mStates.empty() ){
			mStates.back()->CollisionResponse(rCollObject, rThisGroupID, rOpGroupID);
	}
}

/************************************************************//**
*	\param newThread 新しいｽﾚｯﾄﾞ
****************************************************************/
void ActionControllable::AddThread(IActionThread* newThread) 
{
	mThreads.push_back(newThread);
}

/************************************************************//**
*	\param newThread 古いｽﾚｯﾄﾞ
****************************************************************/
void ActionControllable::RemoveThread(IActionThread* oldThread) 
{
	mThreads.remove(oldThread);
}

