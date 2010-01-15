#pragma once

#include <list>
#include "Event.h"

using namespace std;

/*
	�C�x���g���Ǘ�����N���X�ł�
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