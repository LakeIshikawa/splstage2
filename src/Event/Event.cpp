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
	���Ԃ��o�߂��āA�f�B���C�𒴂�����Ƃ�����[�Ă�
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
	�f�B���C���Z�b�g����
*/
void Event::SetDelay(float rDelay)
{
	mDelay = rDelay;
}