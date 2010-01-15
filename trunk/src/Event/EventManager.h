#pragma once

#include <list>
#include "Event.h"

using namespace std;

/*
	イベントを管理するクラスです
*/
class EventManager
{
public:
	EventManager();
	~EventManager();

	void Process();
	void Request(Event* rEvent);

protected:
	list<Event*> lstEvents;
	list<Event*> lstDelEvents;
};