#include "Event.h"
#include "..\\Management\\GameControl.h"

Event::Event()
{
	mDelay=0.0f;
	mTimer=0.0f;
}

Event::~Event()
{}

/*
	時間が経過して、ディレイを超えたらとりっがー呼ぶ
*/
bool Event::ElapseTime()
{
	WAIT_TIMER(mTimer, mDelay)
		Trigger();
		return true;
	WAIT_END

	return false;
}

/*
	ディレイをセットする
*/
void Event::SetDelay(float rDelay)
{
	mDelay = rDelay;
}