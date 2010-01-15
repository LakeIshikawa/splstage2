#pragma once

class Action;

/*
	自機のステータス。

	STATUSがACTIONの場合は、CurrentActionに
	現在自機が行っているアクションへのポインタが入ります。
	それ以外の場合は中身が未定です。
*/
class JikiStatus
{
public:

	enum STATUS
	{
		FUTSU,
		ACTION,
		KUCHU,
		DAMAGE
	};

	JikiStatus(void);
	~JikiStatus(void);

	STATUS	GetStatus();
	Action*	GetCurrentAction();

private:
	Action* mpCurrentAction;
	STATUS	mCurrentStatus;

};
