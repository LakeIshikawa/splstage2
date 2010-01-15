#pragma once

/*
	イベント(基本クラス)
*/
class Event
{
public:
	Event();
	virtual ~Event();

	virtual void Trigger() = 0;

	bool ElapseTime();
	void SetDelay(float rDelay);

protected:
	float mDelay;
	float mTimer;
};
