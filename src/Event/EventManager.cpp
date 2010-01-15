#include "EventManager.h"

EventManager::EventManager()
{}

EventManager::~EventManager()
{}

/*
	リストにはいっているイベントを全部
	実行し、その後リストを空にします

	イベントが消去されます
*/
void EventManager::Process()
{
	for each (Event* ev in lstEvents){
		if( ev->ElapseTime() ){
			lstDelEvents.push_back( ev );
		}
	}

	// 不要になったイベントを削除
	for each (Event* rev in lstDelEvents){
		lstEvents.remove( rev );
		delete rev;
	}

	lstDelEvents.clear();
}

/*
	リクエスト：　イベントをリストに入れます
*/
void EventManager::Request(Event *rEvent)
{
	lstEvents.push_back( rEvent );
}
